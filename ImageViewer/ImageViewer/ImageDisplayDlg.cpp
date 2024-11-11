// ImageDisplayDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageViewer.h"
#include "ImageDisplayDlg.h"
#include "afxdialogex.h"

// ImageDisplayDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(ImageDisplayDlg, CDialogEx)

void ImageDisplayDlg::UpdateImage(Mat& img)
{
	m_img_display.Destroy();
	CRect rect;
	m_image_control.GetWindowRect(rect);//GetWindowRect�� ����ؼ� ���� ��Ʈ���� ũ�⸦ �޴´�.
	CDC* dc; //���� ��Ʈ���� DC�� ������  CDC ������
	dc = m_image_control.GetDC(); //���� ��Ʈ���� DC�� ��´�.
	//CImage image;
	img.CvtColor(img, img, enum_COLOR::BGR2GRAY);
	img.Convert_to_CImage(m_img_display);
	
	//image.Load(_T("D:\\workspace\\Study\\ImageViewer\\images\\hihi.bmp"));//�̹��� �ε�
	int imageWidth = m_img_display.GetWidth();
	int imageHeight = m_img_display.GetHeight();
	CRect dialogRect;
	GetClientRect(&dialogRect);
	
	//todo ���� ��Ʈ���� ���̾�α� �߽ɿ�.
	int xPos = 0;
	int yPos = 0;
	
	// CStatic ��Ʈ���� �̹��� ũ��� �����ϰ� ���̾�α� �߽ɿ� ��ġ�մϴ�.
	m_image_control.SetWindowPos(
		nullptr,          // Z-order�� �������� ����
		xPos, yPos,       // ���ο� ��ġ (�߾� ��ġ)
		imageWidth,       // ���ο� �ʺ�
		imageHeight,      // ���ο� ����
		SWP_NOZORDER | SWP_SHOWWINDOW
	);
	m_img_display.StretchBlt(dc->m_hDC, 0, 0, imageWidth, imageHeight, SRCCOPY);

	ReleaseDC(dc);//DC ����
}

ImageDisplayDlg::ImageDisplayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IMAGEDISPLAY_VIEW, pParent)
{
}

ImageDisplayDlg::~ImageDisplayDlg()
{
}

void ImageDisplayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE, m_image_control);
}


BEGIN_MESSAGE_MAP(ImageDisplayDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// ImageDisplayDlg �޽��� ó�����Դϴ�.


BOOL ImageDisplayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_isInitialized = true;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void ImageDisplayDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (m_isInitialized == false)
		return;
	if (m_img_display.IsNull())
		return;
	//int imageWidth = m_img_display.GetWidth();
	//int imageHeight = m_img_display.GetHeight();

	//// ���̾�α� Ŭ���̾�Ʈ ������ ũ�⸦ �����ɴϴ�.
	//CRect dialogRect;
	//GetClientRect(&dialogRect);

	//// ���̾�α� �߽ɿ� ��ġ�ϵ��� �̹��� ��ġ�� ����մϴ�.
	//int xPos = (dialogRect.Width() - imageWidth) / 2;
	//int yPos = (dialogRect.Height() - imageHeight) / 2;

	//// CStatic ��Ʈ���� �̹��� ũ��� �����ϰ� ���̾�α� �߽ɿ� ��ġ�մϴ�.
	//m_image_control.SetWindowPos(
	//	nullptr,          // Z-order�� �������� ����
	//	xPos, yPos,       // ���ο� ��ġ (�߾� ��ġ)
	//	imageWidth,       // ���ο� �ʺ�
	//	imageHeight,      // ���ο� ����
	//	SWP_NOZORDER | SWP_SHOWWINDOW
	//);
}
