#include "MainWindow.h"

enum {
	ID_MENU_CAP = 1,
	ID_MENU_ADDPEOPLE =2,
	ID_MENU_TRAIN = 3,
	ID_TOOL_CAP = 4,
	ID_TOOL_TRAIN = 5,
	ID_TOOL_ADDPEOPLE =6
};

wxBEGIN_EVENT_TABLE(MainWindow,wxFrame)
EVT_MENU(wxID_EXIT,MainWindow::OnExit)
EVT_MENU(wxID_ABOUT,MainWindow::OnAbout)
wxEND_EVENT_TABLE()

MainWindow::MainWindow(const wxString& title, const wxPoint& pos, wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size) {
	this->DesignMenu();
	this->DesignToolBar();
	this->SetStatusBar("ready...");
	this->SetIcon(wxIcon(_T("opencv.ico"),wxBITMAP_TYPE_ICO));
}


MainWindow::~MainWindow() {
}

void MainWindow::DesignMenu() {
	if (!mb) {
		mb = new wxMenuBar;
	}
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(wxID_ANY, _T("打开"), _T("打开文件"));
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT,_T("退出"));

	wxMenu* menuCapture = new wxMenu;
	menuCapture->Append(ID_MENU_CAP,_T("开始捕获"),_T("从摄像头捕获人脸"));
	menuCapture->Append(ID_MENU_TRAIN, _T("训练样本"), _T("人工训练样本"));
	menuCapture->Append(ID_MENU_ADDPEOPLE, _T("信息补全"), _T("补全捕获的人脸信息"));

	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	mb->Append(menuFile, _T("文件 (&F)"));
	mb->Append(menuCapture,_T("高级 (&A)"));
	mb->Append(menuHelp, _T("帮助 (&H)"));

	SetMenuBar(mb);
}
void MainWindow::DesignToolBar() {
	if (!tb) {
		tb = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxNO_BORDER, _T("toolbar"));
	}
	tb->AddTool(wxID_ANY, _("打开文件"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_OPEN")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _T("打开文件"), _T("打开文件"));
	tb->AddTool(ID_TOOL_CAP, _("开始捕获"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_FORWARD")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _T("开始捕获"), _T("开始从摄像头捕获人脸"));
	tb->AddTool(ID_TOOL_TRAIN, _("训练样本"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_TIP")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _T("训练样本"), _T("训练样本"));
	tb->AddTool(ID_TOOL_ADDPEOPLE, _("添加信息"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_ADD_BOOKMARK")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _T("添加信息"), _T("添加信息"));
	tb->AddTool(wxID_ANY, _("退出"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_QUIT")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _T("退出"), _T("退出程序"));
	tb->Realize();
	SetToolBar(tb);
}
void MainWindow::SetStatusBar(wxString st) {
	if (!this->GetStatusBar()) {
		this->CreateStatusBar();
	}
	this->SetStatusText(st);
}


void MainWindow::OnExit(wxCommandEvent& event) {
	Close(true);
}
void MainWindow::OnAbout(wxCommandEvent& event) {
	wxMessageBox("content!", "title");
}