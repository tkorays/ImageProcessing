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

	static const long ID_STATICTEXT1;
	static const long ID_STATICTEXT2;
	static const long ID_STATICTEXT3;
	static const long ID_STATICBITMAP1;

	void DesignMenu();
	void DesignToolBar();
	void DesignClient();
	void SetStatusBar(wxString st);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
};

