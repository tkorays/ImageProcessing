#pragma once
#include "inc.h"
class MainWindow : public wxFrame {
public:
	MainWindow(const wxString& title, const wxPoint& pos, wxSize& size);
	~MainWindow();
private:
	// some methods
	wxDECLARE_EVENT_TABLE();
};

