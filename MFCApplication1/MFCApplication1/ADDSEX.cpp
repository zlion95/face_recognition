// ADDSEX.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ADDSEX.h"
#include "afxdialogex.h"


// ADDSEX 对话框

IMPLEMENT_DYNAMIC(ADDSEX, CDialogEx)

ADDSEX::ADDSEX(CWnd* pParent /*=NULL*/)
	: CDialogEx(ADDSEX::IDD, pParent)
{
	
}

ADDSEX::~ADDSEX()
{
	
}

void ADDSEX::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, COMBOADDSEX);
	
}


BEGIN_MESSAGE_MAP(ADDSEX, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &ADDSEX::OnCbnSelchangeCombo1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &ADDSEX::OnDropdownCombo1)
END_MESSAGE_MAP()


// ADDSEX 消息处理程序

void ADDSEX::OnDropdownCombo1()
{
	COMBOADDSEX.AddString(_T("请选择"));
	COMBOADDSEX.AddString(_T("男"));
	COMBOADDSEX.AddString(_T("女"));
	COMBOADDSEX.SetCurSel(0);
	SetDlgItemText(IDC_COMBO1, _T("请选择"));
	// TODO:  在此添加控件通知处理程序代码
}

void ADDSEX::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
}



