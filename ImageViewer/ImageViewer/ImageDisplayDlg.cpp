#include "stdafx.h"
#include "ImageViewer.h"
#include "ImageDisplayDlg.h"
#include "afxdialogex.h"
#include "ImageViewerDlg.h"
#include "HistogramDisplayDlg.h"
#include "ImageProcessing.h"

IMPLEMENT_DYNAMIC(ImageDisplayDlg, CDialogEx)

void ImageDisplayDlg::UpdateImage(Mat& img)
{
	if (!m_img_display.IsNull())  m_img_display.Destroy(); // 디스플레이되고 있는 CImage 초기화

	m_img_org = img;
	CRect picRect, dialogRect;
	m_image_control.GetWindowRect(picRect); // 픽쳐 컨트롤의 크기
	CDC* dc = m_image_control.GetDC(); //픽쳐 컨트롤의 DC를 얻는다
	GetClientRect(&dialogRect); // 다이얼로그의 크기

	auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
	auto* histogramDlg = pParentDialog->GetHistogramDisplayDlg();
	
	histogramDlg->DrawHistogram(m_img_org);
	ImageProcessing cv;
	cv.ResizeImage(m_img_org, m_img_resized, 0.65);
	m_img_resized.Convert_to_CImage(m_img_display);
	
	int imageWidth = m_img_display.GetWidth();
	int imageHeight = m_img_display.GetHeight();

	int xPos = static_cast<int>((dialogRect.Width() / 2) - (imageWidth / 2));
	int yPos = static_cast<int>((dialogRect.Height() / 2) - (imageHeight / 2));
	m_image_control.SetWindowPos(
		nullptr,        
		xPos, yPos,     
		imageWidth,     
		imageHeight,    
		SWP_NOZORDER | SWP_SHOWWINDOW
	);
	CWnd* pic_control = GetDlgItem(IDC_IMAGE);
	m_img_display.StretchBlt(dc->m_hDC, 0, 0, imageWidth, imageHeight, SRCCOPY);
	
	ReleaseDC(dc);//DC 해제
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



BOOL ImageDisplayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_isInitialized = true;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void ImageDisplayDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (m_isInitialized == false) 
		return;
	ResizeControls();
}

void ImageDisplayDlg::ResizeControls() {
	CRect picRect, dialogRect;
	m_image_control.GetWindowRect(picRect); // 픽쳐 컨트롤의 크기
	CDC* dc = m_image_control.GetDC(); //픽쳐 컨트롤의 DC를 얻는다
	GetClientRect(&dialogRect); // 다이얼로그의 크기

	int xPos = static_cast<int>((dialogRect.Width() / 2) - (picRect.Width() / 2));
	int yPos = static_cast<int>((dialogRect.Height() / 2) - (picRect.Height() / 2));
	m_image_control.SetWindowPos(
		nullptr,
		xPos, yPos,
		picRect.Width(),
		picRect.Height(),
		SWP_NOZORDER | SWP_SHOWWINDOW
	);
}
