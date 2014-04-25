#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(MainWindow,wxFrame)

wxEND_EVENT_TABLE()

MainWindow::MainWindow(const wxString& title, const wxPoint& pos, wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size) {
	wxInitAllImageHandlers();
	designer = new Designer(this);
	designer->run_design();
}


MainWindow::~MainWindow() {
}
