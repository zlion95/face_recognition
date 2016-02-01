#pragma once


// NEEDMOREMESSAGE dialog

class NEEDMOREMESSAGE : public CDialogEx
{
	DECLARE_DYNAMIC(NEEDMOREMESSAGE)

public:
	NEEDMOREMESSAGE(CWnd* pParent = NULL);   // standard constructor
	virtual ~NEEDMOREMESSAGE();

// Dialog Data
	enum { IDD = IDD_NEEDMORE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
