#include "stdafx.h"
#include "VEDIO.h"


CVEDIODS::CVEDIODS()
{
	Width = 0;
	Hight = 0;


}
CVEDIODS::~CVEDIODS()
{

}

void CVEDIODS::openCamera(UINT ID, CDC* pDC, CRect &rect)//括号内的函数在.h文件中先设置再添加
{
	//此处添加关于打开摄像头的相关函数
	if (1)
	{
		/*
		VideoCapture capture(0);
		CascadeClassifier cascade;
		cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml");
		Face_Catch fc;*/
		Mat face = imread("C:/boldt.jpg",1);
//		fc.get_Face_Frame(face, capture, cascade, 1.3);
		showImage(face, ID, pDC, rect);
	//	waitKey(1000);
	}
}

void CVEDIODS::showImage(Mat &img, UINT ID, CDC* pDC, CRect &rect)
{
	pDC->GetWindow()->GetWindowRect(&rect);
//	CDC* pDC = GetDlgItem(ID)->GetDC();// 获得显示控件的 DC
	HDC hDC = pDC->GetSafeHdc();// 获取 HDC(设备句柄) 来进行绘图操作

//	CRect rect;
//	GetDlgItem(ID)->GetClientRect(&rect);
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
	ReleaseDC(pDC);
}

