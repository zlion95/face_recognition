#pragma once
#include "Face_Catch.h"
#include "ConMySQL.h"
#include "CvvImage.h"

using namespace cv;
// DIANMING 对话框

class DIANMING : public CDialogEx
{
	DECLARE_DYNAMIC(DIANMING)

public:
	DIANMING(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DIANMING();

// 对话框数据
	enum { IDD = IDD_DIANMING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();

	void draw_Image(CDC* pDC, HDC hDC, Mat img, CRect rect);

	CString nameget;
	CString sexget;
	CString specialtyget;
	CString IDget;
	CString classroomget;
};
