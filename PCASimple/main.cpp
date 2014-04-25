#include <iostream>
#include <fstream>
#include <sstream>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;

// 从文件中的列表中读取图像
static void read_imgList(const string& filename, vector<Mat>& images) {
	std::ifstream file(filename.c_str(), ifstream::in);
	if (!file) {
		string error_message = "No valid input file was given,please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line;
	while (getline(file,line)) {
		images.push_back(imread(line, 0)); // 读取灰度图像
	}
}

// 处理图像，便于PCA处理
static Mat formatImagesForPCA(const vector<Mat> & data) {
	// 生成N（图像个数）个行矩阵，串数据成行，PCA的机理所在
	Mat dst(static_cast<int>(data.size()), data[0].rows*data[0].cols, CV_32F);
	// 处理所有的图像
	for (unsigned int i = 0; i < data.size(); i++) {
		// 将图像串成行,reshap(1,1)：单通道，一行
		Mat image_row = data[i].clone().reshape(1, 1);
		Mat row_i = dst.row(i); // 保存了dst第i行的数据指针?
		// Mat::convertTo(Mat outputArr,int rtype)
		image_row.convertTo(row_i, CV_32F); //转化保存到row_i中
	}
	return dst;
}

// 转为单通道灰度模式
static Mat toGrayscale(InputArray _src) {
	Mat src = _src.getMat();
	// 只允许单通道数据
	if (src.channels()!=1) {
		CV_Error(CV_StsBadArg, "Only Matrices with one channel are supported!");
	}
	Mat dst;
	// 将输入数据规格化
	cv::normalize(_src, dst, NORM_MINMAX, CV_8UC1);
	return dst;
}

struct params {
	Mat data;
	int ch;
	int rows;
	PCA pca;
	string winName;
};

// PCA过程，欲知详情还的看论文
static void onTrackbar(int pos, void* ptr) {
	cout << "Retained variance = " << pos << "%    ";
	cout << "re-calculating PCA..." << std::flush;

	double var = pos / 100.0;
	
	struct params *p = (struct params*)ptr;

	// 创建pca对象，指定数据为行格式
	p->pca = PCA(p->data,cv::Mat(),CV_PCA_DATA_AS_ROW,var);

	// 投射到数据第一行上
	Mat point = p->pca.project(p->data.row(0));
	// 还原数据
	Mat reconstruction = p->pca.backProject(point);
	// 还原图片格式
	reconstruction = reconstruction.reshape(p->ch, p->rows);
	// 转灰度
	reconstruction = toGrayscale(reconstruction);
	// 显示转回的灰度图像
	imshow(p->winName, reconstruction);
	cout << "done!     # of principal components:" << p->pca.eigenvectors.rows << endl;
}

//////////////////////////
// main function
int main(int argc,char** argv) {
	string imgList = "./list.txt";
	vector<Mat> images;
	try {
		read_imgList(imgList, images);
	} catch (cv::Exception& e) {
		cerr << "Error opening file\"" << imgList << "\".Reason:" << e.msg << endl;
		exit(1);
	}

	if (images.size()<1) {
		CV_Error(CV_StsBadArg, "this demo need at least 2 images to work");
	}
	// 将图像转化为行矩阵形式
	Mat data = formatImagesForPCA(images);
	// pca,flag=0.95
	PCA pca(data, cv::Mat(), CV_PCA_DATA_AS_ROW, 0.95);
	Mat point = pca.project(data.row(0));
	Mat reconstruction = pca.backProject(point);
	reconstruction = reconstruction.reshape(images[0].channels(), images[0].rows);

	string winName = "Reconstruction| press q to quit";
	namedWindow(winName,WINDOW_NORMAL);
	params p;
	p.data = data;
	p.ch = images[0].channels();
	p.rows = images[0].rows;
	p.pca = pca;
	p.winName = winName;
	
	int pos = 95;
	createTrackbar("Retained variance (%)", winName, &pos, 100, onTrackbar, (void*)&p);

	imshow(winName, reconstruction);
	int key = 0;
	while (key!='q') {
		key = waitKey();
	}
	return 0;
}
