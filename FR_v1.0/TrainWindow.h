#pragma once
#include "inc.h"



class TrainWindow : public wxFrame {
public:
	TrainWindow(wxWindow *parent,const wxString& title, const wxPoint& pos, wxSize& size);
	~TrainWindow();
private:
	wxWindow* parent;
	void OnExit(wxCloseEvent& event);
	wxDECLARE_EVENT_TABLE();
};

