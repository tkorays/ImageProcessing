#include "evthandler.h"
#include "db.h"
#include "id_all.h"


wxBEGIN_EVENT_TABLE(EvtHandler, wxFrame)

wxEND_EVENT_TABLE()


void EvtHandler::OnExit(wxCommandEvent& event) {
	Close(true);
}

void EvtHandler::OnAbout(wxCommandEvent& event) {
	wxMessageBox("人脸识别程序！", "信息");
}

void EvtHandler::OnSelectPeople(wxCommandEvent& event) {
	int index = get_people_id(event.GetString());
	char s[10];
	_itoa(index, s, 10);
	wxMessageBox(_T("小混蛋点击了")+event.GetString()+_T(",序号,")+wxString(s), _T("提示"));
	vector<wxString> piclist = get_pic_list(index);
	wxString allpic=wxEmptyString;
	for (size_t i = 0; i < piclist.size(); i++) {
		allpic += piclist[i];
		allpic += ",";
	}
	wxMessageBox(allpic);
}
