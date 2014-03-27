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

MainWindow::MainWindow(const wxString& title, const wxPoint& pos, wxSize& size)\
	: wxFrame(NULL, wxID_ANY, title, pos, size, wxDEFAULT_FRAME_STYLE & ~wxMAXIMIZE_BOX & ~wxRESIZE_BORDER) {
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
const long MainWindow::ID_STATICTEXT1 = wxNewId();
const long MainWindow::ID_STATICTEXT2 = wxNewId();
const long MainWindow::ID_STATICTEXT3 = wxNewId();
const long MainWindow::ID_STATICBITMAP1 = wxNewId();

void MainWindow::DesignClient(){
	

	wxStaticText* StaticText2;
	wxStaticBitmap* StaticBitmap1;
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

	
	FlexGridSizer1 = new wxFlexGridSizer(1, 2, 0, 0);
	FlexGridSizer1->AddGrowableCol(1);
	FlexGridSizer1->AddGrowableRow(0);

	BoxSizer1 = new wxBoxSizer(wxVERTICAL);

	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("检测出人脸数:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer4->Add(StaticText1, 1, wxALL | wxALIGN_CENTER_HORIZONTAL , 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("2"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticText2->SetForegroundColour(wxColor("red"));
	BoxSizer4->Add(StaticText2, 1, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
	BoxSizer1->Add(BoxSizer4, 0, wxALL | wxALIGN_LEFT | wxALIGN_TOP, 5);

	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("人物显示："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	StaticText3->SetForegroundColour(wxColor("red"));
	BoxSizer3->Add(StaticText3, 1, wxALL | wxALIGN_LEFT , 5);
	BoxSizer1->Add(BoxSizer3, 0, wxALL | wxALIGN_LEFT | wxALIGN_TOP, 5);

	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	peopleL_1 = new wxStaticText(this, wxID_ANY, _("徐志博"), wxDefaultPosition, wxSize(50,30), 0, _T("wxID_ANY"));
	BoxSizer5->Add(peopleL_1, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	wxBitmap* pp_1 = new wxBitmap(_T("xzb.jpg"), wxBITMAP_TYPE_JPEG);
	peopleP_1 = new wxStaticBitmap(this, wxID_ANY | wxALIGN_CENTER_VERTICAL, *pp_1, wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	BoxSizer5->Add(peopleP_1, 1, wxALL | wxALIGN_LEFT, 5);
	BoxSizer1->Add(BoxSizer5, 0, wxALL | wxALIGN_LEFT | wxALIGN_TOP, 5);

	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	peopleL_2 = new wxStaticText(this, wxID_ANY, _("徐志博"), wxDefaultPosition, wxSize(50, 30), 0, _T("wxID_ANY"));
	BoxSizer6->Add(peopleL_2, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	wxBitmap* pp_2 = new wxBitmap(_T("xzb.jpg"), wxBITMAP_TYPE_JPEG);
	peopleP_2 = new wxStaticBitmap(this, wxID_ANY | wxALIGN_CENTER_VERTICAL, *pp_2, wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	BoxSizer6->Add(peopleP_2, 1, wxALL | wxALIGN_LEFT, 5);
	BoxSizer1->Add(BoxSizer6, 0, wxALL | wxALIGN_LEFT | wxALIGN_TOP, 5);



	FlexGridSizer1->Add(BoxSizer1, 1, wxALL | wxALIGN_TOP| wxALIGN_LEFT, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticBitmap1 = new wxStaticBitmap(this, ID_STATICBITMAP1, wxNullBitmap, wxDefaultPosition, bmp->GetSize() , 0, _T("ID_STATICBITMAP1"));
	StaticBitmap1->SetBitmap(*bmp);
	BoxSizer2->Add(StaticBitmap1, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer2, 1, wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	
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
	wxMessageBox(_T("人脸检测与识别"), _T("关于"));
}