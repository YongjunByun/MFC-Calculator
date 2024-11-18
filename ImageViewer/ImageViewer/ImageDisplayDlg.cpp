#include "stdafx.h"
#include "afxdialogex.h"
#include "ImageViewer.h"
#include "ImageDisplayDlg.h"
#include "ImageViewerDlg.h"
#include "HistogramDisplayDlg.h"
#include "ImageProcessing.h"

IMPLEMENT_DYNAMIC(ImageDisplayDlg, CDialogEx)
ImageDisplayDlg::ImageDisplayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IMAGEDISPLAY_VIEW, pParent)
{
}

ImageDisplayDlg::~ImageDisplayDlg()
{

}

void ImageDisplayDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (m_isInitialized == false)
		return;
	ResizeControls();
	GetDlgItem(IDC_IMAGE)->Invalidate(FALSE);
}

BOOL ImageDisplayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_isInitialized = true;
	return TRUE;
}

void ImageDisplayDlg::UpdateImage(Mat& img)
{
	if (img.isEmpty()) {
		AfxMessageBox(L"이미지가 없습니다");
		return;
	}
	if (!m_img_display.IsNull())
		m_img_display.Destroy(); // 디스플레이되고 있는 CImage 초기화
	
	m_img_org = img;
	CRect picRect, dialogRect;
	m_image_control.GetWindowRect(picRect); // 픽쳐 컨트롤의 크기
	CDC* dc = m_image_control.GetDC(); //픽쳐 컨트롤의 DC를 얻는다
	GetClientRect(&dialogRect); // 다이얼로그의 크기

	auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
	auto* histogramDlg = pParentDialog->GetHistogramDisplayDlg();
	
	histogramDlg->DrawHistogram(m_img_org);
	ImageProcessing cv;
	cv.ResizeImage(m_img_org, m_img_resized, m_Resize_Ratio);
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

void ImageDisplayDlg::UpdateImage(Mat& img, std::vector<std::vector<Point_>>& contours)
{
	if (img.isEmpty()) {
		AfxMessageBox(L"이미지가 없습니다");
		return;
	}
	if (!m_img_display.IsNull())  
		m_img_display.Destroy(); // 디스플레이되고 있는 CImage 초기화

	m_img_org = img;
	CRect picRect, dialogRect;
	m_image_control.GetWindowRect(picRect); // 픽쳐 컨트롤의 크기
	CDC* dc = m_image_control.GetDC(); //픽쳐 컨트롤의 DC를 얻는다
	GetClientRect(&dialogRect); // 다이얼로그의 크기

	auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
	auto* histogramDlg = pParentDialog->GetHistogramDisplayDlg();

	histogramDlg->DrawHistogram(m_img_org);
	ImageProcessing cv;
	cv.ResizeImage(m_img_org, m_img_resized, m_Resize_Ratio);
	if(contours.size() > 0)
		cv.ResizeContours(contours, m_Resize_Ratio);
	m_img_resized.Convert_to_CImage(m_img_display);

	for (const auto& contour : contours) {
		int r = rand() % 256;
		int g = rand() % 256;
		int b = rand() % 256;
		for (const auto& point : contour) {
			if (point.x >= 0 && point.x < m_img_display.GetWidth() && point.y >= 0 && point.y < m_img_display.GetHeight()) {
				m_img_display.SetPixel(point.x, point.y, RGB(r,g,b)); // 각 컨투어 구분하기 위해 색깔 다르게
			}
		}
	}
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

void ImageDisplayDlg::Update_onlyCImage(Mat& img)
{
	if (img.isEmpty()) {
		AfxMessageBox(L"이미지가 없습니다");
		return;
	}
	if (!m_img_display.IsNull())
		m_img_display.Destroy(); // 디스플레이되고 있는 CImage 초기화

	CRect picRect, dialogRect;
	m_image_control.GetWindowRect(picRect); // 픽쳐 컨트롤의 크기
	CDC* dc = m_image_control.GetDC(); //픽쳐 컨트롤의 DC를 얻는다
	GetClientRect(&dialogRect); // 다이얼로그의 크기

	auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
	auto* histogramDlg = pParentDialog->GetHistogramDisplayDlg();

	ImageProcessing cv;
	cv.ResizeImage(img, m_img_resized, m_Resize_Ratio);
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

void ImageDisplayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE, m_image_control);
}

BEGIN_MESSAGE_MAP(ImageDisplayDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()



