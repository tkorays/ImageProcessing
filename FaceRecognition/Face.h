#pragma once
#include "config.h"

class Face {
public:
	Face();
	~Face();
	vector<Rect> DetectFace(Mat RgbImg);
	void LoadCascadeFile(string filepath);
private:
	CascadeClassifier face_cascade;
	
};

