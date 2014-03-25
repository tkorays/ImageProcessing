#include "MainFrame.h"
#include "helper.h"
#include "TrainFrame.h"

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size),m_timer(this,100) {
	this->DesignMenu();

	CreateStatusBar();
	SetStatusText("Ready...");
	haveResized = false;
	count = 10;
}


MainFrame::~MainFrame()
{
}

void MainFrame::DesignMenu() {
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(ID_Capture, "Capture", "OpenFile");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu* menuTrain = new wxMenu;
	menuTrain->Append(ID_TRAIN, "Start Train", "To train the face data");
	//menuTrain->Append(ID_TRAIN);

	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuTrain, "&Train");
	menuBar->Append(menuHelp, "&Help");
	SetMenuBar(menuBar);
}
void MainFrame::OnExit(wxCommandEvent& event) {
	cvReleaseCapture(&capture);
	m_timer.Stop();
	Close(true);
	exit(0);
}
void MainFrame::OnAbout(wxCommandEvent& event) {
	wxMessageBox("Face Recognition,by tkorays", "FaceRecognition", wxOK | wxICON_INFORMATION);
}
void MainFrame::OnCapture(wxCommandEvent& event) {
	face.LoadCascadeFile(face_cascade_file);
	capture = cvCreateCameraCapture(0); // Start capture
	m_timer.Start(300); // do sth every 100 ms
}
void MainFrame::OnTimer(wxTimerEvent& event) {
	wxClientDC dc(this);
	PrepareDC(dc);
	bgr_frame = cvQueryFrame(capture);
	Mat client_frame(bgr_frame);
	stringstream ss;
	string s;
	IplImage sm;
	if (bgr_frame) {
		if (!haveResized) {
			this->SetClientSize(bgr_frame->width, bgr_frame->height);
		}
		
		faces = face.DetectFace(client_frame);
		for (int i = 0; i < faces.size(); i++) {
			Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
			rectangle(client_frame, Rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height), Scalar(255, 0, 255) , 3, 8, 0);
			if (this->count>0) {
				sm = client_frame(Rect(faces[i].x+3, faces[i].y+3, faces[i].width-6, faces[i].height-6));
				ss << "./Faces/face_";
				ss << this->count;
				ss >> s;
				s += ".jpg";
				cvSaveImage(s.data() , &sm);
				this->count--;
			} 
			SetStatusText("Get Faces OK!");
		}
		IplImage result_frame = client_frame;
		wxImage wxImg = wx_from_cv(&result_frame);
		wxBitmap wxbmp = wxBitmap(wxImg);
		dc.DrawBitmap(wxImg, 0, 0);

	} else {
		assert(0);
	}

}
void MainFrame::OnTrain(wxCommandEvent& event) {
	this->EnableCloseButton(false);
	m_timer.Stop();
	trainFrame = new TrainFrame(this,"Train",wxPoint(100,100),wxSize(400,300));
	trainFrame->SetId(ID_TRAIN_FRAME);
	trainFrame->Show();

}