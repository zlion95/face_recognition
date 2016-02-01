#ifndef CCAMERA_H
#define CCAMERA_H

//#define WIN32_LEAN_AND_MEAN

//#include <windows.h>
//#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\face\facerec.hpp>
#include "Face_Catch.h"
#include "ConMySQL.h"
#include "resource.h"
#include "CvvImage.h"


using namespace cv;
using namespace std;

class CVEDIODS :public CDialog
{
public:
	CVEDIODS();
	virtual ~CVEDIODS();

	void openCamera(UINT ID,CDC* pDC, CRect &rect);
	void showImage(Mat &img, UINT ID, CDC* pDC, CRect &rect);

private:
	int Width;
	int Hight;
	
};


#endif