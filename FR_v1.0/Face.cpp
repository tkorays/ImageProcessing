#include "Face.h"


Face::Face()
{
	single_face_count = 0;
	face_count = 0;
}


Face::~Face()
{
}

bool Face::LoadCascadeFile(string filePath){
	if (!face_cascade.load(filePath)){
		isOK = false;
	}else{
		isOK = true;
	}
	return isOK;
}
vector<Rect> Face::DetectFaces(Mat rgbImg) {
	vector<Rect> faces;
	Mat grayImg;
	cvtColor(rgbImg, grayImg,CV_BGR2GRAY);
	equalizeHist(grayImg, grayImg);
	face_cascade.detectMultiScale(grayImg, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
	return faces;
}
void Face::HighLightFace(Mat mat_frame, const vector<Rect> faces) {
	for (size_t i = 0; i < faces.size(); i++) {
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		rectangle(mat_frame, Rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height), Scalar(255, 0, 255), 3, 8, 0);
	}
}
bool Face::SaveFace(Mat face_img, Rect r, const char* savePath) {
	IplImage p = face_img(r); // ½ØÈ¡Í¼Ïñ
	if (cvSaveImage(savePath, &p)) {
		single_face_count++;
		return true;
	}
	return false;
}