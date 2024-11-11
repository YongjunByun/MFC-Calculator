// HistogramDisplayDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageViewer.h"
#include "HistogramDisplayDlg.h"
#include "afxdialogex.h"


// HistogramDisplayDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(HistogramDisplayDlg, CDialogEx)

HistogramDisplayDlg::HistogramDisplayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HISTOGRAM_VIEW, pParent)
{

}

HistogramDisplayDlg::~HistogramDisplayDlg()
{
}

void HistogramDisplayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HistogramDisplayDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// HistogramDisplayDlg 메시지 처리기입니다.

