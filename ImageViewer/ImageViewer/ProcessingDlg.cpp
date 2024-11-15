#include "stdafx.h"
#include "ImageViewer.h"
#include "ProcessingDlg.h"
#include "afxdialogex.h"
#include "ImageViewerDlg.h"
#include "ImageDisplayDlg.h"

// ProcessingDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(ProcessingDlg, CDialogEx)

ProcessingDlg::ProcessingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PROCESSING_VIEW, pParent)
{

}

ProcessingDlg::~ProcessingDlg()
{
}

void ProcessingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit_threshold);
}

BEGIN_MESSAGE_MAP(ProcessingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ROTATE10, &ProcessingDlg::OnBnClickedButtonRotate10)
	ON_BN_CLICKED(IDC_BUTTON_N_ROTATE10, &ProcessingDlg::OnBnClickedButtonNRotate10)
	ON_BN_CLICKED(IDC_BUTTON_VERTICAL_FLIP, &ProcessingDlg::OnBnClickedButtonVerticalFlip)
	ON_BN_CLICKED(IDC_BUTTON_HORIZONTAL_FLIP, &ProcessingDlg::OnBnClickedButtonHorizontalFlip)
	ON_BN_CLICKED(IDC_BUTTON_SCALE_MINUS, &ProcessingDlg::OnBnClickedButtonScaleMinus)
	ON_BN_CLICKED(IDC_BUTTON_SCALE_PLUS, &ProcessingDlg::OnBnClickedButtonScalePlus)
	ON_BN_CLICKED(IDC_BUTTON_GAUSSIAN, &ProcessingDlg::OnBnClickedButtonGaussian)
	ON_BN_CLICKED(IDC_BUTTON_MEDIAN, &ProcessingDlg::OnBnClickedButtonMedian)
	ON_BN_CLICKED(IDC_BUTTON_INSPECTION, &ProcessingDlg::OnBnClickedButtonInspection)
	ON_WM_SIZE()
END_MESSAGE_MAP()

void ProcessingDlg::OnBnClickedButtonRotate10()
{
	auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
	auto* displayDlg = pParentDialog->GetImageDisplayDlg();
	Mat src = displayDlg->GetImage();
	Mat dst;
	if (!cv.RotateImage(src, dst, 10)) {
		AfxMessageBox(L"FAIL");
		return;
	}
	displayDlg->UpdateImage(dst);
}

void ProcessingDlg::OnBnClickedButtonNRotate10()
{
	auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
	auto* displayDlg = pParentDialog->GetImageDisplayDlg();
	Mat src = displayDlg->GetImage();
	Mat dst;
	if (!cv.RotateImage(src, dst, -10)) {
		AfxMessageBox(L"FAIL");
		return;
	}
	displayDlg->UpdateImage(dst);
}

void ProcessingDlg::OnBnClickedButtonVerticalFlip()
{
	auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
	auto* displayDlg = pParentDialog->GetImageDisplayDlg();
	Mat src = displayDlg->GetImage();
	Mat dst;
	if (!cv.FlipImage(src, dst, true)) {
		AfxMessageBox(L"FAIL");
		return;
	}
	displayDlg->UpdateImage(dst);
}

void ProcessingDlg::OnBnClickedButtonHorizontalFlip()
{
	auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
	auto* displayDlg = pParentDialog->GetImageDisplayDlg();
	Mat src = displayDlg->GetImage();
	Mat dst;
	if (!cv.FlipImage(src, dst, false)) {
		AfxMessageBox(L"FAIL");
		return;
	}
	displayDlg->UpdateImage(dst);
}

void ProcessingDlg::OnBnClickedButtonScaleMinus()
{
	auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
	auto* displayDlg = pParentDialog->GetImageDisplayDlg();
	Mat src = displayDlg->GetImage();
	Mat dst;
	if (!cv.ResizeImage(src, dst, 0.9)) {
		AfxMessageBox(L"FAIL");
		return;
	}
	displayDlg->UpdateImage(dst);
}

void ProcessingDlg::OnBnClickedButtonScalePlus()
{
	auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
	auto* displayDlg = pParentDialog->GetImageDisplayDlg();
	Mat src = displayDlg->GetImage();
	Mat dst;
	if (!cv.ResizeImage(src, dst, 1.1)) {
		AfxMessageBox(L"FAIL");
		return;
	}
	cv.ResizeImage(src, dst, 1.1);
	displayDlg->UpdateImage(dst);
}

void ProcessingDlg::OnBnClickedButtonGaussian()
{
	auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
	auto* displayDlg = pParentDialog->GetImageDisplayDlg();
	Mat src = displayDlg->GetImage();
	Mat dst;
	if (!cv.GaussianBlur(src, dst)) {
		AfxMessageBox(L"FAIL");
		return;
	}
	displayDlg->UpdateImage(dst);
}

void ProcessingDlg::OnBnClickedButtonMedian()
{
	auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
	auto* displayDlg = pParentDialog->GetImageDisplayDlg();
	Mat src = displayDlg->GetImage();
	Mat dst;
	if (!cv.MedianBlur(src, dst)){
		AfxMessageBox(L"FAIL");
		return;
	}
	displayDlg->UpdateImage(dst);
}

void ProcessingDlg::OnBnClickedButtonInspection()
{
	CString str;
	m_edit_threshold.GetWindowText(str);
	int threshold = _ttoi(str);

	auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
	auto* displayDlg = pParentDialog->GetImageDisplayDlg();
	Mat src = displayDlg->GetImage();
	Mat dst;
	if (!cv.Binarization(src, dst, threshold)) {
		AfxMessageBox(L"FAIL\nThreshold 범위를 확인하세요");
		return;
	}
	vector<vector<Point_>> contours;
	cv.Contours(dst, contours);
	//cv.DrawContours(dst, dst, contours);
	displayDlg->UpdateImage(dst, contours);
}

BOOL ProcessingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_isInitialized = true;
	return TRUE;
}

void ProcessingDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (m_isInitialized == false)
		return;
	ResizeControls();
}

void ProcessingDlg::ResizeControls() {
	CRect clientRect;
	GetClientRect(&clientRect);
	int buttonHeight = (int)(clientRect.Height() / 5) - 10; // 5행
	int buttonWidth = (int)(clientRect.Width() / 2) - 10; // 2열
	int margin = 10; // 버튼 간 마진
	CWnd* col0_Button[] = { GetDlgItem(IDC_BUTTON_ROTATE10),
		GetDlgItem(IDC_BUTTON_VERTICAL_FLIP),
		GetDlgItem(IDC_BUTTON_SCALE_MINUS),
		GetDlgItem(IDC_BUTTON_GAUSSIAN),};
	CWnd* col1_Button[] = { GetDlgItem(IDC_BUTTON_N_ROTATE10),
		GetDlgItem(IDC_BUTTON_HORIZONTAL_FLIP),
		GetDlgItem(IDC_BUTTON_SCALE_PLUS),
		GetDlgItem(IDC_BUTTON_MEDIAN),
		GetDlgItem(IDC_BUTTON_INSPECTION)
	};
	CWnd* col0_static_text = GetDlgItem(IDC_STATIC);
	CWnd* col0_edit_text = GetDlgItem(IDC_EDIT1);

	// 첫 번째 열의 버튼 위치 설정
	for (int i = 0; i < 4; ++i) // 맨 아래 버튼 제외
	{
		if (col0_Button[i] != nullptr)
		{
			col0_Button[i]->SetWindowPos(nullptr, margin, margin + i * (buttonHeight + margin), 
				buttonWidth,
				buttonHeight,
				SWP_NOZORDER);
		}

	}
	if (col0_static_text != nullptr)
	{
		col0_static_text->SetWindowPos(nullptr, margin, margin + 4 * (buttonHeight + margin),
			buttonWidth,          
			static_cast<int>(buttonHeight * 0.65 - margin / 2),
			SWP_NOZORDER);
	}
	if (col0_edit_text != nullptr)
	{
		// 하단에 edit text 배치
		col0_edit_text->SetWindowPos(nullptr, margin, margin + 4 * (buttonHeight + margin) + static_cast<int>(buttonHeight * 0.65 - margin / 2),
			buttonWidth,
			static_cast<int>(buttonHeight * 0.35), 
			SWP_NOZORDER);
	}
	// 두 번째 열의 버튼 위치 설정
	for (int i = 0; i < 5; ++i)
	{
		if (col1_Button[i] != nullptr)
		{
			col1_Button[i]->SetWindowPos(nullptr, margin * 2 + buttonWidth,	margin + i * (buttonHeight + margin),
				buttonWidth,
				buttonHeight,
				SWP_NOZORDER);
		}
	}

}