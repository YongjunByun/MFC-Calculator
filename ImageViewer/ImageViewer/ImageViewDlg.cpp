// ImageViewDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageViewer.h"
#include "ImageViewDlg.h"
#include "afxdialogex.h"


// ImageViewDlg ��ȭ �����Դϴ�.

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


// ImageViewDlg �޽��� ó�����Դϴ�.
