#pragma once
#include "config.h"
class TrainFrame : public wxFrame {
public:
	TrainFrame(wxFrame* p, const wxString& title, const wxPoint& pos, wxSize& size);
	~TrainFrame();
	
private:
	wxFrame* parent;
	void OnExit(wxCloseEvent& event);
	void OnClose(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
};

