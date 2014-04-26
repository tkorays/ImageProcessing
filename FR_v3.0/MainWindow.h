#pragma once
#include "inc.h"
#include "designer.h"

class MainWindow : public wxFrame {
public:
	Designer* designer;
	

	MainWindow(const wxString& title, const wxPoint& pos, wxSize& size);
	~MainWindow();
private:
	void bind_event();
	// some methods
	wxDECLARE_EVENT_TABLE();
};

