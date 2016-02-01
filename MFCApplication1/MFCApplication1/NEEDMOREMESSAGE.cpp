// NEEDMOREMESSAGE.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "NEEDMOREMESSAGE.h"
#include "afxdialogex.h"


// NEEDMOREMESSAGE dialog

IMPLEMENT_DYNAMIC(NEEDMOREMESSAGE, CDialogEx)

NEEDMOREMESSAGE::NEEDMOREMESSAGE(CWnd* pParent /*=NULL*/)
	: CDialogEx(NEEDMOREMESSAGE::IDD, pParent)
{

}

NEEDMOREMESSAGE::~NEEDMOREMESSAGE()
{
}

void NEEDMOREMESSAGE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NEEDMOREMESSAGE, CDialogEx)
	ON_BN_CLICKED(IDOK, &NEEDMOREMESSAGE::OnBnClickedOk)
END_MESSAGE_MAP()


// NEEDMOREMESSAGE message handlers


void NEEDMOREMESSAGE::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
