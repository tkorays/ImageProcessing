#include "inc.h"
#include "designer.h"
#include "helper.h"
#include "id_all.h"
#include "db.h"



Designer::Designer(wxWindow* p) {
	parent = p;
	mbar = new wxMenuBar();
	tbar = new wxToolBar(parent, ID_TOOLBAR, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxNO_BORDER, _T("ID_TOOLBAR"));
	sbar = new wxStatusBar(parent, ID_STATUSBAR, 0, _T("ID_STATUSBAR"));
}
wxMenuBar* Designer::get_menubar() {
	return mbar;
}
wxToolBar* Designer::get_toolbar() {
	return tbar;
}
wxStatusBar* Designer::get_statusbar() {
	return sbar;
}
void Designer::run_design() {
	design_menubar();
	design_toolbar();
	design_statusbar();
	reset_window();
	design_client();
}
/* 下面是主要的设计部分 */
void Designer::design_menubar() {
	wxMenu* menuFile = new wxMenu();
	menuFile->Append(new wxMenuItem(menuFile, ID_MENU_FILE_OPEN, _T("打开\tCtrl+O"), _T("打开文件夹"), wxITEM_NORMAL));
	menuFile->Append(new wxMenuItem(menuFile, ID_MENU_EXIT, _T("退出\tCtrl+Q"), _T("退出程序"), wxITEM_NORMAL));

	wxMenu* menuHelp = new wxMenu();
	menuHelp->Append(new wxMenuItem(menuHelp, wxID_ABOUT, _T("关于\tCTrl+A"), _T("关于本程序"), wxITEM_NORMAL));

	mbar->Append(menuFile, _T("文件"));
	mbar->Append(menuHelp, _T("帮助"));
	((wxFrameBase*)parent)->SetMenuBar(mbar);
}
void Designer::design_toolbar() {
	int __wxStatusBarWidths_1[1] = { -10 };
	int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
	sbar->SetFieldsCount(1, __wxStatusBarWidths_1);
	sbar->SetStatusStyles(1, __wxStatusBarStyles_1);
	((wxFrameBase*)parent)->SetStatusBar(sbar);
	((wxFrameBase*)parent)->SetStatusText(_T("就绪..."));
}
void Designer::design_statusbar() {
	tbar->AddTool(ID_MENU_FILE_OPEN, _T("打开"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_OPEN")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _T("打开文件"), _T("打开文件"));
	tbar->Realize();
	((wxFrameBase*)parent)->SetToolBar(tbar);
}
void Designer::reset_window() {
	((wxFrameBase*)parent)->SetTitle(_T("人脸检测"));
	((wxFrameBase*)parent)->SetPosition(wxPoint(60, 30));
	//((wxFrameBase*)parent)->SetSize(wxSize(1100, 800));
	((wxFrameBase*)parent)->SetIcon(wxIcon(_T("logo.ico"), wxBITMAP_TYPE_ICO));
	((wxFrameBase*)parent)->SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~wxMAXIMIZE_BOX & ~wxRESIZE_BORDER);
	((wxFrameBase*)parent)->SetClientSize(wxSize(client_width, client_height));
	//Connect(wxID_ANY, wxEVT_CLOSE_WINDOW, (wxObjectEventFunction)& Designer::OnClose);
}

void Designer::design_client() {
	int left_width = 250;
	int right_width = client_width - left_width;
	long splitwin_style = wxSP_3DBORDER | wxSP_3DSASH | wxSP_NO_XP_THEME | wxNO_BORDER;
	wxSplitterWindow *spwin = new wxSplitterWindow(parent, wxID_ANY,  wxDefaultPosition, wxSize(client_width, client_height), splitwin_style);
	spwin->SetMinimumPaneSize(0);

	wxSplitterWindow* lwin = new wxSplitterWindow(spwin, wxID_ANY, wxDefaultPosition, wxSize(left_width, client_height), wxSP_NO_XP_THEME | wxNO_BORDER);
	wxSplitterWindow* rwin = new wxSplitterWindow(spwin, wxID_ANY, wxDefaultPosition, wxSize(right_width, client_height), wxSP_NO_XP_THEME | wxNO_BORDER);

	wxSplitterWindow* lwin_1 = new wxSplitterWindow(lwin, wxID_ANY, wxDefaultPosition, wxSize(left_width, 500), wxSP_NO_XP_THEME | wxNO_BORDER);
	wxSplitterWindow* lwin_2 = new wxSplitterWindow(lwin, wxID_ANY, wxDefaultPosition, wxSize(left_width, client_height-500), wxSP_NO_XP_THEME | wxNO_BORDER);

	// left window 1
	wxNotebook* notebook = new wxNotebook(lwin_1, wxID_ANY, wxDefaultPosition, wxSize(left_width-4,500), wxBK_DEFAULT | wxBK_TOP);

	wxPanel* samPanel = new wxPanel(notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL);
	samPanel->SetSizer(new wxBoxSizer(wxVERTICAL));
	wxArrayString* sampleList = new wxArrayString();
	wxListBox* sampleListBox = new wxListBox(samPanel, ID_PEOPLE_LIST, wxDefaultPosition, wxSize(client_width - 4, 300), *sampleList, wxLB_SINGLE | wxNO_BORDER);
	show_allpeople(sampleListBox); // 显示所有的人列表
	notebook->AddPage(samPanel, _T("所有样本"));
	

	wxPanel* managePanel = new wxPanel(notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize,  wxNO_BORDER | wxTAB_TRAVERSAL);
	managePanel->SetSizer(new wxBoxSizer(wxVERTICAL));
	notebook->AddPage(managePanel, _T("工具箱"));
	
	wxBitmap* bmp = new wxBitmap("./4.jpg", wxBITMAP_TYPE_JPEG);
	wxStaticBitmap* vedio = new wxStaticBitmap(lwin_2, wxID_ANY, *bmp, wxDefaultPosition, wxDefaultSize ,0);
	
	lwin->SplitHorizontally(lwin_1, lwin_2, 300);
	spwin->SplitVertically(lwin, rwin, 250);
}

void Designer::show_allpeople(wxListBox* sampleListBox) {
	vector<kvpair<int, wxString>> people_list = get_people_list();
	for (size_t i = 0; i < people_list.size(); i++) {
		sampleListBox->Append(people_list[i].value);
	}
}
