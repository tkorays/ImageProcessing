#pragma once
#include "inc.h"


/*
	EventHandler ���������κ��¼���ͨ�������¼������
*/
class EvtHandler:public wxFrame{
public:
	EvtHandler() {}

	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnSelectPeople(wxCommandEvent& event);

private:
	wxDECLARE_EVENT_TABLE();
	
};