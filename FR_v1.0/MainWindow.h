#pragma once
#include "inc.h"
class MainWindow : public wxFrame {
public:
	MainWindow(const wxString& title, const wxPoint& pos, wxSize& size);
	~MainWindow();
private:
	// vars or methods
	wxMenuBar* mb;
	wxToolBar* tb;

	void DesignMenu();
	void DesignToolBar();
	void SetStatusBar(wxString st);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
};

