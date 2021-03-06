#pragma once
#include "inc.h"
#include "conf.h"
#include "Face.h"


class MainWindow : public wxFrame {
public:
	MainWindow(const wxString& title, const wxPoint& pos, wxSize& size);
	~MainWindow();

	wxMenuBar* mb;
	wxMenuItem* menuItemAbout;
	wxMenu* menuFile;
	wxToolBar* tb;
	wxMenuItem* menuItemExit;
	wxToolBarToolBase* tbItemStart;
	wxMenuItem* menuItemFopen;
	wxToolBarToolBase* tbItemRecog;
	wxToolBarToolBase* tbItemExit;
	wxToolBarToolBase* tbItemOpen;
	wxToolBarToolBase* tbItemSaveFrame;
	wxMenu* menuHelp;
	wxStatusBar* statusBar;
	wxToolBarToolBase* tbItemTrain;
	wxTextCtrl* peopleName;
	wxStaticText* resultName;

	wxTimer m_timer;
	CvCapture* capture;
	IplImage* bgr_frame;
	Face peopleFace;
	vector<Rect> faces;

	vector<Mat> testimg;
	vector<int> labels;

	unsigned int picCount;

protected:
	static const long ID_MENU_OPEN;
	static const long ID_STATUSBAR;
	static const long ID_TOOL_FOPEN;
	static const long ID_TOOL_START;
	static const long ID_TOOL_SAVEFRAME;
	static const long ID_TOOL_TRAIN;
	static const long ID_TOOL_RECOG;
	static const long ID_TOOL_EXIT;
	static const long ID_TOOLBAR;

private:
	
	// some methods
	void Design();

	void OnStart(wxCommandEvent& event);
	void OnSaveFrame(wxCommandEvent& event);
	void OnTrain(wxCommandEvent& event);
	void OnRecog(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnTimer(wxTimerEvent& event);
	void OnClose(wxCloseEvent& event);

	void DrawBitamp(wxObject* HBmp, wxBitmap& bmp);
	wxDECLARE_EVENT_TABLE();
};

