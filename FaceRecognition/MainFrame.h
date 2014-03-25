#pragma once
#include "config.h"
#include "Face.h"
#include "TrainFrame.h"

class MainFrame :public wxFrame{
public:
	MainFrame(const wxString& title,const wxPoint& pos,wxSize& size);
	~MainFrame();
private:
	void DesignMenu();
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnCapture(wxCommandEvent& event);
	void OnTimer(wxTimerEvent& event);
	void OnTrain(wxCommandEvent& event);
	wxTimer m_timer;
	CvCapture* capture;
	IplImage* bgr_frame;
	bool haveResized;
	Face face;
	vector<Rect> faces;
	void saveFace(string path);
	unsigned int count;
	TrainFrame* trainFrame;
	wxDECLARE_EVENT_TABLE();
};

