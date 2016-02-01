// PresentData.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "PresentData.h"
#include "afxdialogex.h"
#include "ConMySQL.h"
#include "Face_Catch.h"
#include "resource.h"



using namespace std;

// PresentData dialog

IMPLEMENT_DYNAMIC(PresentData, CDialogEx)

PresentData::PresentData(CWnd* pParent /*=NULL*/)
	: CDialogEx(PresentData::IDD, pParent)
{

}

PresentData::~PresentData()
{
}

void PresentData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PresentData, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &PresentData::OnBnClickedButton1)
END_MESSAGE_MAP()


// PresentData message handlers


void PresentData::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	ConMySQL mysqlcon;
	string outputData;
	mysqlcon.get_present_time_data(outputData);
	Face_Catch fc;

	if (fc.CheckDir(dir_path) == 0 || fc.CheckDir(dir_path) == 1)//检查文件夹是否存在
	{
		ofstream fout(data_path);//创建文件句柄
		if (fout)
		{
			vector<string> splitStr = fc.split(outputData,"\n");
			fout << "The student present data:" << endl;
			for (int i = 0; i < splitStr.size(); ++i)
			{
				fout << splitStr[i] << endl;
			}
			fout.close();
			GetDlgItem(IDC_TEXT1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TEXT2)->ShowWindow(SW_SHOW);
		}

	}
	else
	{
		//显示SW_SHOW
	//	GetDlgitem(id)->ShowWindow(SW_HiDE);//隐藏


	}
	
}


/*
//检查文件夹是否存在，不存在则创建之
//文件夹存在返回 0
//文件夹创建失败返回-1
//文件夹创建失败返回1
int PresentData::CheckDir(char* Dir)
{
	FILE *fp = NULL;
	char TempDir[200];
	memset(TempDir, '\0', sizeof(TempDir));
	sprintf_s(TempDir, Dir);
	strcat_s(TempDir, "\\");
	strcat_s(TempDir, ".temp.fortest");
	fopen_s(&fp, TempDir, "w");
	if (!fp)
	{
		if (_mkdir(Dir) == 0)
		{
			return 1;//文件夹创建成功
		}
		else
		{
			return -1;//can not make a dir;
		}
	}
	else
	{
		fclose(fp);
	}
	return 0;
}
*/