#include "App.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainWindow* w = new MainWindow("Hello", wxPoint(40, 40), wxSize(600, 400));
	w->Show();
	return true;
}