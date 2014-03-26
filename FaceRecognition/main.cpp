#include "config.h"
#include "MainFrame.h"
#include "TrainFrame.h"

class MainApp : public wxApp{
public:
	virtual bool OnInit();
};




wxIMPLEMENT_APP(MainApp);

bool MainApp::OnInit(){
	MainFrame* myWindow = new MainFrame("FaceRecognition",wxPoint(50,50),wxSize(500,400));
	myWindow->Show();
	SetTopWindow(myWindow);
	return true;
}