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
	this->SetIcon(wxIcon(_T("opencv.ico"), wxBITMAP_TYPE_ICO));
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
	m_timer.Stop();
	ifstream pList("./Data/peoplelist.txt"); // 打开people列表文件
	ifstream imgList;
	char pLine[20]; // 人
	char iLine[20]; // 图片
	Mat orgImg, grayImg; // 原始图片，灰度图片
	vector<Rect> facesInPic;
	string sline,sline_1; // stringline char[]转string
	string tmp;
	Mat curImg,stdImg(cvSize(256,256),1);
	int lblInt=0;// 标签
	// 一个人一个人地来,两层循环
	while (!pList.eof()) {
		pList.getline(pLine,20); // 获取一个人放在line中
		sline = pLine; //放到string中便于操作 
		if (sline.empty()) {
			break;
		}
		// 设置小图片存放目录
		tmp = "./Data/" + sline + "/small/";
		if (!wxDirExists(tmp)) {
			wxMkDir(tmp); // 删除原有的small文件夹
		}
		//wxMkdir("./Data/" + sline + "/small/"); 
		// 创建新的文件夹
		// 读取含有人脸图片列表读取图片,得到小图
		imgList.open("./Data/" + sline + "/list.txt", ios::in); // 打开该人的目录读取图片列表
		while (!imgList.eof()) { // 循环读取所有图片
			imgList.getline(iLine, 20);
			sline_1 = iLine; // 得到一张图片名称
			if (sline_1.empty()) {
				break;
			}
			orgImg = imread("./Data/" + sline + "/" + sline_1); // 读取图片
			cvtColor(orgImg, grayImg, CV_BGR2GRAY);
			if (peopleFace.isOK) {} else { // 加载人脸检测文件
				peopleFace.LoadCascadeFile(face_cascade_file);
			}
			facesInPic.clear();
			facesInPic = peopleFace.DetectFaces(orgImg); // 得到图像中人脸坐标
			// 取第一个人脸，尽量保证训练时只有一个人脸
			if (facesInPic.size()>0) {
				curImg = grayImg(Rect(facesInPic[0].x, facesInPic[0].y, facesInPic[0].width, facesInPic[0].height));
				//cvResize(&curImg, &stdImg, CV_INTER_AREA);
				cv::resize(curImg,curImg,cvSize(256,256));
				tmp = "./Data/" + sline + "/small/" + sline_1; // 灰度小图保存路径
				peopleFace.SaveFace(curImg, Rect(0,0,256,256), tmp.data()); // 保存小图
				// 接下来时训练时刻，擦亮眼睛看吧
				testimg.push_back(curImg);
				labels.push_back(lblInt);
			}
		}
		imgList.close();
		lblInt++; // 按列表人名
		
	}
	peopleFace.model = createEigenFaceRecognizer(10);
	peopleFace.model->train(testimg, labels);

	wxMessageBox(_T("训练成功！"), _T("提示"));
	m_timer.Start(100);
}
void MainWindow::OnRecog(wxCommandEvent& event) {
	if (!(bgr_frame = cvQueryFrame(capture))) {
		wxMessageBox(_T("请点击开始，启动视频！"), _T("错误"));
		return;
	}//else
	if (peopleFace.model.empty()) {
		wxMessageBox(_T("数据尚未训练！"), _T("错误"));
		return;
	}
	m_timer.Stop();
	Mat theface = bgr_frame;
	// 得到人脸部分
	if (peopleFace.isOK) {} else { // 加载人脸检测文件
		peopleFace.LoadCascadeFile(face_cascade_file);
	}
	vector<Rect> fc = peopleFace.DetectFaces(theface);
	if (fc.size()<=0) {
		wxMessageBox(_T("镜头内没有任何人，或者识别不到！"), _T("提醒"));
		m_timer.Start(100);
		return;
	}//else
	int whoisu=0; string tmp;
	Mat thegray;// = theface(fc[0]);
	cvtColor(theface, theface, CV_BGR2GRAY);
	thegray = theface(Rect(fc[0].x, fc[0].y, fc[0].width, fc[0].height));
	cv::resize(thegray, thegray, cvSize(256, 256));
	whoisu = peopleFace.model->predict(thegray);


	ifstream fs("./Data/peoplelist.txt");
	int count=0;
	char line[20];
	string sline;
	while (!fs.eof()) {
		fs.getline(line, 20);
		sline = line;
		if (count == whoisu) {
			break;
		} // else
		if (sline.empty()) {
			wxMessageBox(_T("没有找到信息，你可能删掉了文件或者修改了？"),_T("提醒"));
			m_timer.Start(100);
			return;
		}
		count++;
	}
	
	stringstream ss;
	ss << "Detected! ----> ";
	ss << sline;
	ss >> tmp;
	tmp = "Detected! ----> " + sline;
	wxMessageBox(tmp, _T("识别结果："));
	m_timer.Start(100);
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