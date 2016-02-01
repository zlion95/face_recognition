#pragma once
#include "afxwin.h"


// ADDSEX 对话框

class ADDSEX : public CDialogEx
{
	DECLARE_DYNAMIC(ADDSEX)

public:
	ADDSEX(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ADDSEX();

// 对话框数据
	enum { IDD = IDD_ADDMES1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	// 控件变量of ADDSEX
	CComboBox COMBOADDSEX;
	afx_msg void OnDropdownCombo1();
};
