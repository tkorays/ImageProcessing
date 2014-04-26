#include "MainWindow.h"
#include "id_all.h"
#include "evthandler.h"

wxBEGIN_EVENT_TABLE(MainWindow,wxFrame)
EVT_MENU(ID_MENU_EXIT,EvtHandler::OnExit)
EVT_MENU(wxID_ABOUT,EvtHandler::OnAbout)
wxEND_EVENT_TABLE()

MainWindow::MainWindow(const wxString& title, const wxPoint& pos, wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size) {
	wxInitAllImageHandlers();
	designer = new Designer(this);
	designer->run_design();
	bind_event();
}
// 动态事件绑定
void MainWindow::bind_event() {
	Connect(ID_PEOPLE_LIST, wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(EvtHandler::OnSelectPeople));
}

MainWindow::~MainWindow() {
}

