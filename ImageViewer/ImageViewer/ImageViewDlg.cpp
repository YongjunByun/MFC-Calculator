// ImageViewDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageViewer.h"
#include "ImageViewDlg.h"
#include "afxdialogex.h"


// ImageViewDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(ImageViewDlg, CDialogEx)

ImageViewDlg::ImageViewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IMAGE_VIEW, pParent)
{

}

ImageViewDlg::~ImageViewDlg()
{
}

void ImageViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ImageViewDlg, CDialogEx)
END_MESSAGE_MAP()


// ImageViewDlg 메시지 처리기입니다.
