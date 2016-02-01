#pragma once

#include <iostream>
#include <fstream>
#include <direct.h>
#include <stdlib.h>
#include <memory> 
#include <string>
#include <sstream>
#include <vector>


// PresentData dialog

class PresentData : public CDialogEx
{
	DECLARE_DYNAMIC(PresentData)

public:
	PresentData(CWnd* pParent = NULL);   // standard constructor
	virtual ~PresentData();
	char* dir_path = "C:/Faces";
	char* data_path = "C:/Faces/output_data.txt";

// Dialog Data
	enum { IDD = IDD_DIALOG1 };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
