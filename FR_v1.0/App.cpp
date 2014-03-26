#include "App.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainWindow* w = new MainWindow(_T("人脸识别"), wxPoint(40, 40), wxSize(600, 480));
	w->Show();
	return true;
}