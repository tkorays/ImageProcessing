#include "evthandler.h"
#include "id_all.h"


wxBEGIN_EVENT_TABLE(EvtHandler, wxFrame)

wxEND_EVENT_TABLE()


void EvtHandler::OnExit(wxCommandEvent& event) {
	Close(true);
}

void EvtHandler::OnAbout(wxCommandEvent& event) {
	wxMessageBox("人脸识别程序！", "信息");
}