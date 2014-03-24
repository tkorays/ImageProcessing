#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

string face_cascade_file = "haarcascade_frontalface_alt.xml";
string eyes_cascade_file = "haarcascade_eye_tree_eyeglasses.xml";


class MyApp :public wxApp{
public:
	virtual bool OnInit();
};

class MyFrame :public wxFrame{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	CvCapture *capture;
	IplImage* bgr_frame;
	wxTimer m_timer;
	CascadeClassifier face_cascade;
	CascadeClassifier eyes_cascade;
	void OnStart(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnTimer(wxTimerEvent& event);
	wxDECLARE_EVENT_TABLE();
};

enum{
	ID_StartCap = 1
};
// from internet
void copy_and_swap_rb(char *s, char *d, int size)
{
	// Copy image data source s to destination d, swapping R and B channels.
	// Assumes 8 bit depth, 3 interleaved channels, and width_step = width*3
	const int step = 3;
	char *end = s + size;
	while (s<end) {
		d[0] = s[2];
		d[1] = s[1];
		d[2] = s[0];
		d += step;
		s += step;
	}
}

void wx2cv(wxImage &wx, IplImage *ipl)
{
	// Copy image data from wxWidgets image to Ipl (opencv) image
	// Assumes ipl image has seq "GBR", depth 8, and 3 channels, and
	// has the same size as the wxImage, and width_step = width*3.
	copy_and_swap_rb((char*)wx.GetData(), ipl->imageData, ipl->imageSize);
}

void cv2wx(IplImage *ipl, wxImage &wx)
{
	// Copy image data from Ipl (opencv) image to wxImage
	// Assumes ipl image has seq "GBR", depth 8, and 3 channels, and
	// has the same size as the wxImage, and width_step = width*3.
	copy_and_swap_rb(ipl->imageData, (char*)wx.GetData(),
		wx.GetWidth()*wx.GetHeight() * 3);
}

IplImage *cv_from_wx(wxImage &wx)
{
	// Return a new IplImage copied from a wxImage.
	// Must be freed by user with cvReleaseImage().
	IplImage *ret = cvCreateImage(cvSize(wx.GetWidth(), wx.GetHeight()),
		IPL_DEPTH_8U, 3);
	wx2cv(wx, ret);
	return ret;
}

wxImage wx_from_cv(IplImage *cx)
{
	// Return new wxImage copied from a compatible IplImage.
	// Assumes ipl image has seq "GBR", depth 8, and 3 channels
	// Fear not. The copy on return is cheap; does not deep-copy the data.
	wxImage wx(cx->width, cx->height, (unsigned char*)malloc(cx->imageSize), false);
	cv2wx(cx, wx);
	return wx;
}

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(ID_StartCap, MyFrame::OnStart)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_PAINT(MyFrame::OnPaint)
EVT_TIMER(wxID_ANY, MyFrame::OnTimer)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit(){
	MyFrame* frame = new MyFrame("FaceDetection", wxPoint(100, 100), wxSize(450, 340));
	wxInitAllImageHandlers();
	frame->SetIcon(wxIcon("opencv-logo-white.png", wxBITMAP_TYPE_PNG, -1, -1));
	frame->Show();
	return true;
}
// 注意计时器以及其id设定
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) :wxFrame(NULL, wxID_ANY, title, pos, size), m_timer(this, 1000){
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(ID_StartCap, "Capture", "Open and detect.");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar(menuBar);

	CreateStatusBar();
	SetStatusText("Ready...");


}

void MyFrame::OnExit(wxCommandEvent& event){
	m_timer.Stop();
	cvReleaseCapture(&capture);
	Close(true);
}
void MyFrame::OnAbout(wxCommandEvent& event){
	wxMessageBox("Using the Camera to detect the face.", "Help", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnStart(wxCommandEvent& event){
	// 下句放上去会出错
	// capture = cvCaptureFromCAM(0);
	// 加载级联分类文件
	if (!face_cascade.load(face_cascade_file) || !eyes_cascade.load(eyes_cascade_file)){
		wxLogMessage("Can not found the file!");
		m_timer.Stop();
		cvReleaseCapture(&capture);
		Close(true);
	}
	capture = cvCreateCameraCapture(0);
	m_timer.Start(50);
}
void MyFrame::OnPaint(wxPaintEvent& event){


}
void MyFrame::OnTimer(wxTimerEvent& event){
	wxClientDC dc(this);
	PrepareDC(dc);
	dc.SetBackground(*wxWHITE_BRUSH);
	//dc.Clear(); 	 

	bgr_frame = cvQueryFrame(capture);
	if (bgr_frame){
		this->SetClientSize(bgr_frame->width, bgr_frame->height);
		// 代码有待优化

		vector<Rect> faces;
		Mat frame_gray;
		Mat frame_color(bgr_frame); // IplImage转Mat
		cvtColor(frame_color, frame_gray, CV_BGR2GRAY);
		equalizeHist(frame_gray, frame_gray);

		face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

		for (size_t i = 0; i < faces.size(); i++)
		{
			Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
			ellipse(frame_color, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
			Mat faceROI = frame_gray(faces[i]);
			std::vector<Rect> eyes;

			//-- 在每张人脸上检测双眼
			eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

			for (size_t j = 0; j < eyes.size(); j++)
			{
				Point center(faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5);
				int radius = cvRound((eyes[j].width + eyes[i].height)*0.25);
				circle(frame_color, center, radius, Scalar(255, 0, 0), 4, 8, 0);
			}
		}
		IplImage img = frame_color;

		wxImage wxImg = wx_from_cv(&img);
		wxBitmap wxBMP = wxBitmap(wxImg);
		dc.DrawBitmap(wxBMP, 0, 0);
	}
}