#pragma once
/*
	设计界面
*/
#include "inc.h"

class Designer{
private:
	wxWindow* parent;

	wxMenuBar* mbar;
	wxToolBar* tbar;
	wxStatusBar* sbar;

	int client_width = 1200;
	int client_height = 700;

	void design_menubar();
	void design_toolbar();
	void design_statusbar();
	void design_client();
	void reset_window();
	
	void show_allpeople(wxListBox* sampleListBox);

public:
	Designer(wxWindow* p);
	wxMenuBar* get_menubar();
	wxToolBar* get_toolbar();
	wxStatusBar* get_statusbar();
	void run_design();
	
};

