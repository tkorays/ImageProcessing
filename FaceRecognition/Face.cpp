#include "Face.h"



Face::Face() {
}


Face::~Face() {}
vector<Rect> Face::DetectFace(Mat RgbImg) {
	vector<Rect> faces; // Save Faces
	Mat GrayImg;
	cvtColor(RgbImg, GrayImg, CV_BGR2GRAY);
	equalizeHist(GrayImg, GrayImg);
	// Get Faces
	face_cascade.detectMultiScale(GrayImg, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE,Size(30,30));
	return faces;
}
void Face::LoadCascadeFile(string filePath) {
	if (!face_cascade.load(filePath)) {
		wxLogMessage("Can not found the file!");
		abort();
	}
}
