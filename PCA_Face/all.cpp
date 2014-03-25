#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyApp :public wxApp{
public:
	virtual bool OnInit();
};

class MyFrame :public wxFrame{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	void OnStart(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnPaint(wxPaintEvent& event);
	wxDECLARE_EVENT_TABLE();
};

enum{
	ID_StartCap = 1
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(ID_StartCap, MyFrame::OnStart)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_PAINT(MyFrame::OnPaint)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit(){
	MyFrame* frame = new MyFrame("FaceDetection", wxPoint(100, 100), wxSize(450, 340));
	wxInitAllImageHandlers();

	//frame->SetIcon(wxIcon("opencv-logo-white.png", wxBITMAP_TYPE_PNG, -1, -1));
	frame->Show();
	return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) :wxFrame(NULL, wxID_ANY, title, pos, size){
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
	
	wxPanel * topPanel = new wxPanel(this);
	wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
	topPanel->SetSizer(topSizer);

	wxPanel *upPanel = new wxPanel(topPanel);
	upPanel->SetBackgroundColour(*wxBLACK);//黑色背景
	wxPanel *centerPanel = new wxPanel(topPanel);
	centerPanel->SetBackgroundColour(*wxYELLOW);//白色背景
	wxPanel *bottomPanel = new wxPanel(topPanel);
	bottomPanel->SetBackgroundColour(*wxRED);//红色背景

	
	

	topSizer->Add(upPanel, 0, wxEXPAND);
	topSizer->Add(centerPanel, 1, wxEXPAND | wxALL);
	topSizer->Add(bottomPanel, 0, wxEXPAND);
	

}

void MyFrame::OnExit(wxCommandEvent& event){
	Close(true);
}
void MyFrame::OnAbout(wxCommandEvent& event){
	wxMessageBox("Using the Camera to detect the face.", "Help", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnStart(wxCommandEvent& event){
	
}
void MyFrame::OnPaint(wxPaintEvent& event){


}
