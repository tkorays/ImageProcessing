#pragma once
/*
	头文件包含，但不包含自己写的类等
*/

#include <wx\wxprec.h>
#ifndef WX_PRECOMP
#include <wx\wx.h>
#endif

#include <wx/intl.h>
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/splitter.h>
#include <wx/notebook.h>
#include <wx/image.h>
//#include <wx/listctrl.h>
#include <wx/event.h>
#include <wx/eventfilter.h>
//#include <wx/frame.h>

#include <wx/html/htmlwin.h>

#include <string>
#include <sstream>

#include <iostream>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

#include "sqlite3.h"