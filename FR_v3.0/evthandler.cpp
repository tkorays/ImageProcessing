#include "evthandler.h"
#include "id_all.h"


wxBEGIN_EVENT_TABLE(EvtHandler, wxFrame)

wxEND_EVENT_TABLE()


void EvtHandler::OnExit(wxCommandEvent& event) {
	Close(true);
}

void EvtHandler::OnAbout(wxCommandEvent& event) {
	wxMessageBox("����ʶ�����", "��Ϣ");
}

void EvtHandler::OnSelectPeople(wxCommandEvent& event) {
	wxMessageBox(_T("С�쵰�����")+event.GetString(), _T("��ʾ"));
}