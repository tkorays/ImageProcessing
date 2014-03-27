﻿#include "MainWindow.h"
#include "helper.h"

enum {
	ID_MENU_CAP = 1,
	ID_MENU_ADDPEOPLE =2,
	ID_MENU_TRAIN = 3,
	ID_TOOL_START = 4,
	ID_TOOL_TRAIN = 5,
	ID_TOOL_ADDPEOPLE =6,
	ID_TOOL_EXIT = 7
};

wxBEGIN_EVENT_TABLE(MainWindow,wxFrame)
EVT_MENU(wxID_EXIT,MainWindow::OnExit)
EVT_MENU(wxID_ABOUT,MainWindow::OnAbout)
EVT_TOOL(ID_TOOL_START,MainWindow::OnStart)
EVT_TOOL(ID_TOOL_EXIT, MainWindow::OnExit)
EVT_TIMER(wxID_ANY,MainWindow::OnTimer)
wxEND_EVENT_TABLE()

MainWindow::MainWindow(const wxString& title, const wxPoint& pos, wxSize& size)\
	: wxFrame(NULL, wxID_ANY, title, pos, size, wxDEFAULT_FRAME_STYLE & ~wxMAXIMIZE_BOX & ~wxRESIZE_BORDER),\
	m_timer(this,100){
	wxInitAllImageHandlers();
	this->DesignMenu();
	this->DesignToolBar();
	this->DesignClient();
	this->SetStatusBar(_T("就绪..."));
	this->SetIcon(wxIcon(_T("opencv.ico"),wxBITMAP_TYPE_ICO));
	
}


MainWindow::~MainWindow() {
}

void MainWindow::DesignMenu() {
	if (!mb) {
		mb = new wxMenuBar;
	}
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(wxID_ANY, _T("打开\tCtrl+O"), _T("打开文件"));
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT,_T("退出\tCtrl+E"));

	wxMenu* menuCapture = new wxMenu;
	menuCapture->Append(ID_MENU_CAP,_T("开始捕获\tCtrl+S"),_T("从摄像头捕获人脸"));
	menuCapture->Append(ID_MENU_TRAIN, _T("训练样本\tCtrl+T"), _T("人工训练样本"));
	menuCapture->Append(ID_MENU_ADDPEOPLE, _T("信息补全\tCtrl+C"), _T("补全捕获的人脸信息"));

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
	tb->AddTool(ID_TOOL_START, _("开始捕获"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_FORWARD")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _T("开始捕获"), _T("开始从摄像头捕获人脸"));
	tb->AddTool(ID_TOOL_TRAIN, _("训练样本"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_TIP")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _T("训练样本"), _T("训练样本"));
	tb->AddTool(ID_TOOL_ADDPEOPLE, _("添加信息"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_ADD_BOOKMARK")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _T("添加信息"), _T("添加信息"));
	tb->AddTool(ID_TOOL_EXIT, _("退出"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_QUIT")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _T("退出"), _T("退出程序"));
	tb->Realize();
	SetToolBar(tb);
}
const long MainWindow::ID_STATICTEXT1 = wxNewId();
const long MainWindow::ID_STATICTEXT2 = wxNewId();
const long MainWindow::ID_STATICTEXT3 = wxNewId();
const long MainWindow::ID_STATICBITMAP1 = wxNewId();

void MainWindow::DesignClient(){
	
	
	wxStaticText* StaticText2;
	wxStaticText* StaticText1;
	wxStaticText* StaticText3;

	wxStaticText* peopleL_1; wxStaticBitmap* peopleP_1;
	wxStaticText* peopleL_2; wxStaticBitmap* peopleP_2;

	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer6;

	wxBitmap* bmp = new wxBitmap(_T("./pic.jpg"), wxBITMAP_TYPE_JPEG);

	spWindow = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxSize(600,360), wxSP_3DBORDER | wxSP_3DSASH | wxSP_NO_XP_THEME | wxNO_BORDER);
	spWindow->SetMinimumPaneSize(0);
	leftPanel = new wxPanel(spWindow);
	rightPanel = new wxPanel(spWindow);
	wxBoxSizer* leftBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* rightBox = new wxBoxSizer(wxHORIZONTAL);

	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("检测出人脸数:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer4->Add(StaticText1, 0, wxALIGN_LEFT | wxALL, 5);

	leftBox->Add(BoxSizer4,wxALIGN_TOP|wxALIGN_BOTTOM|wxALIGN_LEFT|wxALIGN_RIGHT);

	
	leftPanel->SetSizer(leftBox);
	rightPanel->SetSizer(rightBox);

	spWindow->SplitVertically(leftPanel, rightPanel, 200);
	
}
void MainWindow::SetStatusBar(wxString st) {
	if (!this->GetStatusBar()) {
		this->CreateStatusBar();
	}
	this->SetStatusText(st);
}
// 绘制，参数默认为wxWindow以及其子类
void MainWindow::DrawBitamp(wxObject* HBmp, wxBitmap& bmp){
	wxClientDC dc((wxWindow*)HBmp);
	PrepareDC(dc);
	dc.DrawBitmap(bmp, 0, 0);
}

void MainWindow::OnExit(wxCommandEvent& event) {
	if (m_timer.IsRunning()){
		m_timer.Stop();
	}
	cvReleaseCapture(&capture);
	wxMessageBox(_T("正在退出..."), _T("提示"));
	Close(true);
	exit(0);
}
void MainWindow::OnAbout(wxCommandEvent& event) {
	wxMessageBox(_T("人脸检测与识别"), _T("关于"));
}
void MainWindow::OnStart(wxCommandEvent& event){
	if (!(capture = cvCreateCameraCapture(0)))
	{
		wxMessageBox(_T("打开默认摄像头错误！"), _T("错误"));
		Close(true);
		exit(0);
	}
	wxMessageBox(_T("正在捕捉..."), _T("提示"));
	m_timer.Start(100);
}
void MainWindow::OnTimer(wxTimerEvent& event){
	if (!(bgr_frame = cvQueryFrame(capture)))
	{
		wxMessageBox(_T("视频帧读取错误！"), _T("错误"));
		Close(true);
	}
	if (rightPanel->GetSize().GetWidth()<bgr_frame->width)
	{
		
		spWindow->SetSize(200 + bgr_frame->width, bgr_frame->height);
		rightPanel->SetSize(bgr_frame->width, bgr_frame->height);
		this->SetSize(200 + bgr_frame->width, bgr_frame->height + 120);
		Refresh();
	}
	
	wxBitmap b = wxBitmap(wx_from_cv(bgr_frame));
	this->DrawBitamp(rightPanel, b);
}