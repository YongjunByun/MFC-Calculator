// HistogramDisplayDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageViewer.h"
#include "HistogramDisplayDlg.h"
#include "afxdialogex.h"


// HistogramDisplayDlg ��ȭ �����Դϴ�.

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


// HistogramDisplayDlg �޽��� ó�����Դϴ�.

