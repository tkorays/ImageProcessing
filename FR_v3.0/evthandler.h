#pragma once
#include "inc.h"


/*
	EventHandler 自身不处理任何事件，通过其他事件表调用
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