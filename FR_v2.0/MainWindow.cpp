#include "MainWindow.h"
#include "helper.h"

const long MainWindow::ID_MENU_OPEN = wxNewId();
const long MainWindow::ID_STATUSBAR = wxNewId();
const long MainWindow::ID_TOOL_FOPEN = wxNewId();
const long MainWindow::ID_TOOL_START = wxNewId();
const long MainWindow::ID_TOOL_SAVEFRAME = wxNewId();
const long MainWindow::ID_TOOL_TRAIN = wxNewId();
const long MainWindow::ID_TOOL_RECOG = wxNewId();
const long MainWindow::ID_TOOL_EXIT = wxNewId();
const long MainWindow::ID_TOOLBAR = wxNewId();


wxBEGIN_EVENT_TABLE(MainWindow,wxFrame)
EVT_TOOL(MainWindow::ID_TOOL_EXIT,MainWindow::OnExit)
EVT_TOOL(MainWindow::ID_TOOL_START,MainWindow::OnStart)
EVT_TOOL(MainWindow::ID_TOOL_SAVEFRAME,MainWindow::OnSaveFrame)
EVT_TOOL(MainWindow::ID_TOOL_TRAIN,MainWindow::OnTrain)
EVT_TOOL(MainWindow::ID_TOOL_RECOG,MainWindow::OnRecog)
EVT_TIMER(wxID_ANY, MainWindow::OnTimer)
EVT_CLOSE(MainWindow::OnClose)
wxEND_EVENT_TABLE()

MainWindow::MainWindow(const wxString& title, const wxPoint& pos, wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size,\
	wxDEFAULT_FRAME_STYLE & ~wxMAXIMIZE_BOX & ~wxRESIZE_BORDER),\
	m_timer(this, 100) {
	Design();
	picCount = 0;
}


MainWindow::~MainWindow() {
}
void MainWindow::Design() {
	mb = new wxMenuBar();
	menuFile = new wxMenu();
	menuItemFopen = new wxMenuItem(menuFile, ID_MENU_OPEN, _T("打开\tCtrl+O"), wxEmptyString, wxITEM_NORMAL);
	menuFile->Append(menuItemFopen);
	menuItemExit = new wxMenuItem(menuFile, wxID_EXIT, _T("退出\tCtrl+E"), wxEmptyString, wxITEM_NORMAL);
	menuFile->Append(menuItemExit);
	menuHelp = new wxMenu();
	menuItemAbout = new wxMenuItem(menuHelp, wxID_ABOUT, _T("关于\tCTrl+A"), wxEmptyString, wxITEM_NORMAL);
	menuHelp->Append(menuItemAbout);
	mb->Append(menuFile,_T("文件"));
	mb->Append(menuHelp,_T("帮助"));
	SetMenuBar(mb);

	statusBar = new wxStatusBar(this, ID_STATUSBAR, 0, _T("ID_STATUSBAR"));
	int __wxStatusBarWidths_1[1] = { -10 };
	int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
	statusBar->SetFieldsCount(1, __wxStatusBarWidths_1);
	statusBar->SetStatusStyles(1, __wxStatusBarStyles_1);
	SetStatusBar(statusBar);
	SetStatusText(_T("就绪..."));

	tb = new wxToolBar(this, ID_TOOLBAR, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxNO_BORDER, _T("ID_TOOLBAR"));
	tbItemOpen = tb->AddTool(ID_TOOL_FOPEN, _T("打开"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_OPEN")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _T("打开文件"), _T("打开文件"));
	tbItemStart = tb->AddTool(ID_TOOL_START, _T("开始"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_FORWARD")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _T("开始"), _T("开始录制"));
	tbItemSaveFrame = tb->AddTool(ID_TOOL_SAVEFRAME, _T("保存该帧"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_ADD_BOOKMARK")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _T("保存该帧"), _T("保存当前帧"));
	tbItemTrain = tb->AddTool(ID_TOOL_TRAIN, _T("训练"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_TIP")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _T("训练数据"), _T("开始训练人脸识别"));
	tbItemRecog = tb->AddTool(ID_TOOL_RECOG, _T("识别"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FIND")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _T("识别人脸"), _T("识别人脸"));
	tbItemExit = tb->AddTool(ID_TOOL_EXIT, _T("退出"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_QUIT")), wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _T("退出程序"), _T("退出"));
	peopleName = new wxTextCtrl(tb, wxID_ANY, _T("PEOPLE_1"), wxDefaultPosition, wxDefaultSize, 0);
	tb->AddControl(new wxStaticText(tb, wxID_ANY, _T("姓名:  ")));
	tb->AddControl(peopleName);
	tb->AddControl(new wxStaticText(tb, wxID_ANY, _T("    检测结果:  ")));
	resultName = new wxStaticText(tb, wxID_ANY, _T("无"));
	tb->AddControl(resultName);
	tb->Realize();
	SetToolBar(tb);
}

void MainWindow::OnStart(wxCommandEvent& event) {
	// 成功打开摄像头且加载了文件
	if (!(capture = cvCreateCameraCapture(0)) || !peopleFace.LoadCascadeFile(face_cascade_file)) {
		if (!capture) {
			wxMessageBox(_T("打开默认摄像头错误！"), _T("错误"));
		}
		if ( !peopleFace.isOK ){
		} else {
			wxMessageBox(_T("文件加载错误！"), _T("错误"));
		}
		Close(true);
		exit(0);
	}
	m_timer.Start(100);
}
void MainWindow::OnSaveFrame(wxCommandEvent& event) {
	wxString name = peopleName->GetLineText(1).Trim();
	if (name.IsEmpty()) {
		wxMessageBox(_T("请填写人名"),_T("错误！"));
		return;
	}//else

	string tmp = "";
	FILE* f = fopen("./Data/peoplelist.txt", "a");
	wxString path = CURRENT_DIR + name + "/";
	if (!wxDirExists(path)) {
		fprintf_s(f, name.ToStdString().data());
		fprintf_s(f, "\n");
		picCount = 0;
		wxMkDir(path);
	}
	FILE* facelist = fopen(path.data() + "list.txt", "a");
	fclose(f);
	if (!(bgr_frame = cvQueryFrame(capture))) {
		wxMessageBox(_T("请点击开始，启动视频！"), _T("错误"));
		return;
	}
	string fullPath = path.ToStdString();
	stringstream ss;
	ss << fullPath << "/" << picCount << ".jpg";
	fullPath.clear();
	ss >> fullPath;
	cvSaveImage(fullPath.data(), bgr_frame);
	ss.clear();
	ss << picCount;
	ss >> tmp;
	fprintf_s(facelist, tmp.data());
	fprintf_s(facelist, ".jpg\n");
	picCount++;
	wxMessageBox(_T("ok"), _T("ok"));
	fclose(facelist);
}
void MainWindow::OnTrain(wxCommandEvent& event) {
	// 截图保存,存入该人的目录下的small目录
	
	FILE* f = fopen("./Data/peoplelist.txt", "r");
	FILE* facelist = 0;
	if (!f) {
		wxMessageBox(_T("列表文件不存在"), _T("提示"));
		return;
	}// 文件存在
	char s[256];
	int count=0;
	char c;
	string pname;
	string path = "";
	string tmp = "";
	ifstream fs;
	char face[20];
	Mat img,gray_img;
	vector<Rect> picfaces;
	string slash = "/";
	string small_pic;
	path += CURRENT_DIR;
	while (!feof(f)) {
		while ((c = fgetc(f)), c != '\n') {
			if (feof(f)) {
				break;
			}
			s[count++] = c;
		}
		s[count] = '\0';
		if (s[0] == '\0') {
			break;
		}
		count = 0;
		// 已经获取一行
		pname = s;
		if (wxFileExists(path + s + "/small")) {
			wxRmDir(path + s + "/small");
		}
		wxMkDir(path + s + "/small");
		// 存入小图片切片
		tmp = ""; tmp += path; tmp += s; tmp += "/list.txt";
		fs.open(tmp.data());
		tmp = ""; tmp += path; tmp += s; tmp += "/small/"; 
		// 从list文件中获取所有图片名称
		while (fs.getline(face, 20)) {
			img = cv::imread(path + s + slash + face);
			if (peopleFace.isOK) {} else {
				peopleFace.LoadCascadeFile(face_cascade_file);
			}
			picfaces = peopleFace.DetectFaces(img);
			small_pic = tmp + face;
			if (picfaces.size()>0) {
				peopleFace.SaveFace(img, Rect(picfaces[0].x, picfaces[0].y, 256, 256), small_pic.data());
				//peopleFace.SaveFace(img, Rect(picfaces[0].x + picfaces[0].width*0.5 - 128, picfaces[0].y + picfaces[0].height*0.5 - 128, 256, 256), small_pic.data());
			}
		}
		

		fs.close();
	}
	fclose(f);
	wxMessageBox(_T("训练成功！"), _T("提示"));
}
void MainWindow::OnRecog(wxCommandEvent& event) {

}
void MainWindow::OnExit(wxCommandEvent& event) {
	m_timer.IsRunning() ? m_timer.Stop() : 0;
	cvReleaseCapture(&capture);
	Close(true);
	exit(0);
}
void MainWindow::OnAbout(wxCommandEvent& event) {
	wxMessageBox(_T("人脸检测程序by tkorays."), _T("关于"));
}
void MainWindow::OnClose(wxCloseEvent& event) {
	m_timer.IsRunning() ? m_timer.Stop() : 0;
	cvReleaseCapture(&capture);
	exit(0);
}
void MainWindow::OnTimer(wxTimerEvent& event) {
	if (!(bgr_frame = cvQueryFrame(capture))) {
		wxMessageBox(_T("视频帧读取错误！"), _T("错误"));
		Close(true);
	}
	if (GetClientSize().GetWidth()<bgr_frame->width || GetClientSize().GetHeight()<bgr_frame->height) {
		SetSize(bgr_frame->width, bgr_frame->height);
	}
	Mat mat_frame(bgr_frame);
	faces = peopleFace.DetectFaces(mat_frame);
	peopleFace.HighLightFace(mat_frame, faces);
	IplImage result = mat_frame;
	wxBitmap b = wxBitmap(wx_from_cv(&result));
	this->DrawBitamp(this, b);
}

void MainWindow::DrawBitamp(wxObject* HBmp, wxBitmap& bmp) {
	wxClientDC dc((wxWindow*)HBmp);
	PrepareDC(dc);
	dc.DrawBitmap(bmp, 0, 0);
}