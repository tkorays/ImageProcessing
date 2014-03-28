#pragma once
#include "inc.h"
class Face
{
public:
	Face();
	~Face();
	bool LoadCascadeFile(string filePath);
	vector<Rect> DetectFaces(Mat rgbImg);
	bool isOK;
	void HighLightFace(Mat mat_frame,const vector<Rect> faces);
	bool SaveFace(Mat face_img,Rect r,const char* savePath);
	unsigned int face_count;
	unsigned int single_face_count;
private:
	CascadeClassifier face_cascade;
};

