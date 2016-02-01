// DIANMING.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DIANMING.h"
#include "afxdialogex.h"




// DIANMING 对话框

IMPLEMENT_DYNAMIC(DIANMING, CDialogEx)

DIANMING::DIANMING(CWnd* pParent /*=NULL*/)
	: CDialogEx(DIANMING::IDD, pParent)
	, nameget(_T(""))
	, sexget(_T(""))
	, specialtyget(_T(""))
	, IDget(_T(""))
	, classroomget(_T(""))
{

}

DIANMING::~DIANMING()
{
}

void DIANMING::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, nameget);
	DDX_Text(pDX, IDC_EDIT2, sexget);
	DDX_Text(pDX, IDC_EDIT3, specialtyget);
	DDX_Text(pDX, IDC_EDIT4, IDget);
	DDX_Text(pDX, IDC_EDIT6, classroomget);
}


BEGIN_MESSAGE_MAP(DIANMING, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &DIANMING::OnEnChangeEdit1)
	ON_BN_CLICKED(IDCANCEL, &DIANMING::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &DIANMING::OnBnClickedButton1)
END_MESSAGE_MAP()


// DIANMING 消息处理程序


void DIANMING::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void DIANMING::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here


	CDialogEx::OnCancel();
}


void DIANMING::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	CDC* pDC = GetDlgItem(IDC_PIC2)->GetDC();
	HDC hDC = pDC->GetSafeHdc();

	Mat img, face;
	CRect rect;
	GetDlgItem(IDC_PIC2)->GetClientRect(&rect);
	VideoCapture capture(0);
	CascadeClassifier cascade;
	cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml");
	Face_Catch fc;

	fc.get_Face_Frame(img, face, capture, cascade, 1.3);
	draw_Image(pDC, hDC, img, rect);

	ConMySQL mysql_server;
	stu_info stu[10];
	int stuNum = mysql_server.get_all_Info(stu);
	
	Ptr<FaceRecognizer> model = face::createLBPHFaceRecognizer();
	fc.standsize = imread(stu[0].path[0]).size();
	if (!fc.load_Reco_Data(model))
	{
		vector<Mat> trainFace;
		vector<int> trainlabel;
		for (int i = 0; i < stuNum; ++i)
		{
			trainFace.push_back(imread(stu[i].path[0], 0));
			trainFace.push_back(imread(stu[i].path[1], 0));
			trainFace.push_back(imread(stu[i].path[2], 0));
			trainFace.push_back(imread(stu[i].path[3], 0));
			for (int j = 0; j < 4;++j)
				trainlabel.push_back(i);
		}
		fc.face_Reco_Train(model, trainFace, trainlabel, fc.standsize);
	}
	try{
		face = fc.resize_norm(face, fc.standsize);
		int num = model->predict(face);
		if (num != -1)
		{
			nameget = stu[num].name.c_str();
			if (stu[num].sex)
				sexget = "男";
			else
				sexget = "女";
			specialtyget = stu[num].specialty.c_str();
			IDget = stu[num].id.c_str();
			classroomget = stu[num].classname.c_str();
		}

		//fc.face_Reco_Train
		GetDlgItem(IDC_EDIT1)->SetWindowText(nameget);
		GetDlgItem(IDC_EDIT2)->SetWindowText(sexget);
		GetDlgItem(IDC_EDIT3)->SetWindowText(specialtyget);
		GetDlgItem(IDC_EDIT4)->SetWindowText(IDget);
		GetDlgItem(IDC_EDIT6)->SetWindowText(classroomget);
		GetDlgItem(IDC_TEXT_ERROR)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TEXT_FINE)->ShowWindow(SW_SHOW);
	}
	catch (Exception e){
		GetDlgItem(IDC_TEXT_ERROR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TEXT_FINE)->ShowWindow(SW_HIDE);
	}
	


}


void DIANMING::draw_Image(CDC* pDC, HDC hDC, Mat img, CRect rect)
{
	int rw = rect.right - rect.left;// 求出图片控件的宽和高
	int rh = rect.bottom - rect.top;

	int iw = img.size().width;// 读取图片的宽和高
	int ih = img.size().height;
	if (rw > iw && rh > ih)
	{

	}
	else
	{
		CvSize size;
		size.height = rh;
		size.width = rw;
		resize(img, img, size);
		iw = rw;
		ih = rh;
	}
	int tx = (int)(rw - iw) / 2;// 使图片的显示位置正好在控件的正中
	int ty = (int)(rh - ih) / 2;

	SetRect(rect, tx, ty, tx + iw, ty + ih);
	CvvImage cimg;
	IplImage img1 = img;
	cimg.CopyOf(&img1);
	cimg.DrawToHDC(hDC, &rect);


}