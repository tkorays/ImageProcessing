#include "TrainFrame.h"


wxBEGIN_EVENT_TABLE(TrainFrame, wxFrame)
EVT_CLOSE(TrainFrame::OnExit)
wxEND_EVENT_TABLE()
TrainFrame::TrainFrame(wxFrame* p,const wxString& title, const wxPoint& pos, wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size),parent(p) {
	
}


TrainFrame::~TrainFrame() {
}
void TrainFrame::OnExit(wxCloseEvent& event) {
	this->Hide();
	parent->EnableCloseButton(true);
}
void TrainFrame::OnClose(wxCommandEvent& event) {
	parent->EnableCloseButton(true);
}