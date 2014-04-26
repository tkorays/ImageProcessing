#include "evthandler.h"
#include "db.h"
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
	int index = get_people_id(event.GetString());
	char s[10];
	_itoa(index, s, 10);
	wxMessageBox(_T("С�쵰�����")+event.GetString()+_T(",���,")+wxString(s), _T("��ʾ"));
	vector<wxString> piclist = get_pic_list(index);
	wxString allpic=wxEmptyString;
	for (size_t i = 0; i < piclist.size(); i++) {
		allpic += piclist[i];
		allpic += ",";
	}
	wxMessageBox(allpic);
}
