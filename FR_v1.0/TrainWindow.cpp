#include "TrainWindow.h"
#include "MainWindow.h"

enum {
	ID_WINDOW_TRAIN = 15
};
wxBEGIN_EVENT_TABLE(TrainWindow, wxFrame)
EVT_CLOSE(TrainWindow::OnExit)
wxEND_EVENT_TABLE()

TrainWindow::TrainWindow(wxWindow *p, const wxString& title, const wxPoint& pos, wxSize& size) \
: wxFrame(p, ID_WINDOW_TRAIN, title, pos, size, wxDEFAULT_FRAME_STYLE & ~wxMAXIMIZE_BOX & ~wxRESIZE_BORDER){
	parent = p;
}


TrainWindow::~TrainWindow() {
}
void TrainWindow::OnExit(wxCloseEvent& event) {
	//((MainWindow*)parent)->m_timer.Start(100);
	delete this;
}