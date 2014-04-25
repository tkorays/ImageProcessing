#include "App.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainWindow* w = new MainWindow("", wxPoint(60,30), wxSize(400,300));
	w->Show();
	return true;
}