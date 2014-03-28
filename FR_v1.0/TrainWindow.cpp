#include "TrainWindow.h"

enum {
	ID_WINDOW_TRAIN = 15
};
wxBEGIN_EVENT_TABLE(TrainWindow, wxFrame)
EVT_CLOSE(TrainWindow::OnExit)
wxEND_EVENT_TABLE()

TrainWindow::TrainWindow(wxWindow *parent, const wxString& title, const wxPoint& pos, wxSize& size) \
: wxFrame(parent, ID_WINDOW_TRAIN, title, pos, size, wxDEFAULT_FRAME_STYLE & ~wxMAXIMIZE_BOX & ~wxRESIZE_BORDER){
	
}


TrainWindow::~TrainWindow() {
}
void TrainWindow::OnExit(wxCloseEvent& event) {
	delete this;
}