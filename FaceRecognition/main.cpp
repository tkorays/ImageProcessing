#include "config.h"
#include "MainFrame.h"
#include "TrainFrame.h"

class MainApp : public wxApp{
public:
	virtual bool OnInit();
};
wxBEGIN_EVENT_TABLE(MainFrame,wxFrame)
EVT_MENU(wxID_EXIT,MainFrame::OnExit)
EVT_MENU(wxID_ABOUT,MainFrame::OnAbout)
EVT_MENU(ID_Capture,MainFrame::OnCapture)
EVT_TIMER(wxID_ANY,MainFrame::OnTimer)
EVT_MENU(ID_TRAIN, MainFrame::OnTrain)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(TrainFrame, wxFrame)
EVT_CLOSE(TrainFrame::OnExit)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MainApp);

bool MainApp::OnInit(){
	MainFrame* myWindow = new MainFrame("FaceRecognition",wxPoint(50,50),wxSize(500,400));
	myWindow->Show();
	SetTopWindow(myWindow);
	return true;
}