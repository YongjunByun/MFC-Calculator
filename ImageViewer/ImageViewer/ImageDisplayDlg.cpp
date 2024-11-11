// ImageDisplayDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageViewer.h"
#include "ImageDisplayDlg.h"
#include "afxdialogex.h"

// ImageDisplayDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(ImageDisplayDlg, CDialogEx)

void ImageDisplayDlg::UpdateImage(Mat& img)
{
	m_img_display.Destroy();
	CRect rect;
	m_image_control.GetWindowRect(rect);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
	CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
	dc = m_image_control.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.
	//CImage image;
	img.CvtColor(img, img, enum_COLOR::BGR2GRAY);
	img.Convert_to_CImage(m_img_display);
	
	//image.Load(_T("D:\\workspace\\Study\\ImageViewer\\images\\hihi.bmp"));//이미지 로드
	int imageWidth = m_img_display.GetWidth();
	int imageHeight = m_img_display.GetHeight();
	CRect dialogRect;
	GetClientRect(&dialogRect);
	
	//todo 픽쳐 컨트롤이 다이얼로그 중심에.
	int xPos = 0;
	int yPos = 0;
	
	// CStatic 컨트롤을 이미지 크기로 조정하고 다이얼로그 중심에 배치합니다.
	m_image_control.SetWindowPos(
		nullptr,          // Z-order를 변경하지 않음
		xPos, yPos,       // 새로운 위치 (중앙 배치)
		imageWidth,       // 새로운 너비
		imageHeight,      // 새로운 높이
		SWP_NOZORDER | SWP_SHOWWINDOW
	);
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


// ImageDisplayDlg 메시지 처리기입니다.


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
	if (m_img_display.IsNull())
		return;
	//int imageWidth = m_img_display.GetWidth();
	//int imageHeight = m_img_display.GetHeight();

	//// 다이얼로그 클라이언트 영역의 크기를 가져옵니다.
	//CRect dialogRect;
	//GetClientRect(&dialogRect);

	//// 다이얼로그 중심에 위치하도록 이미지 위치를 계산합니다.
	//int xPos = (dialogRect.Width() - imageWidth) / 2;
	//int yPos = (dialogRect.Height() - imageHeight) / 2;

	//// CStatic 컨트롤을 이미지 크기로 조정하고 다이얼로그 중심에 배치합니다.
	//m_image_control.SetWindowPos(
	//	nullptr,          // Z-order를 변경하지 않음
	//	xPos, yPos,       // 새로운 위치 (중앙 배치)
	//	imageWidth,       // 새로운 너비
	//	imageHeight,      // 새로운 높이
	//	SWP_NOZORDER | SWP_SHOWWINDOW
	//);
}
