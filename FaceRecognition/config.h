#pragma once

#include <wx\wxprec.h>
#ifndef WX_PRECOMP
	#include <wx\wx.h>
#endif

#include <omp.h>

#include <iostream>
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;

static string face_cascade_file = "haarcascade_frontalface_alt.xml";

enum {
	ID_Capture = 1,
	ID_TRAIN = 2,
	ID_TRAIN_FRAME = 3
};
