// ProcessingDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageViewer.h"
#include "ProcessingDlg.h"
#include "afxdialogex.h"


// ProcessingDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(ProcessingDlg, CDialogEx)

ProcessingDlg::ProcessingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PROCESSING_VIEW, pParent)
	, m_edit_threshold(0)
{

}

ProcessingDlg::~ProcessingDlg()
{
}

void ProcessingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit_threshold);
	DDV_MinMaxInt(pDX, m_edit_threshold, 0, 255);
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ProcessingDlg::OnBnClickedButtonNRotate10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ProcessingDlg::OnBnClickedButtonVerticalFlip()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ProcessingDlg::OnBnClickedButtonHorizontalFlip()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ProcessingDlg::OnBnClickedButtonScaleMinus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ProcessingDlg::OnBnClickedButtonScalePlus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ProcessingDlg::OnBnClickedButtonGaussian()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ProcessingDlg::OnBnClickedButtonMedian()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ProcessingDlg::OnBnClickedButtonInspection()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


BOOL ProcessingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_isInitialized = true;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
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
			buttonHeight / 2 - margin / 2, 
			SWP_NOZORDER);
	}
	if (col0_edit_text != nullptr)
	{
		// 하단에 edit text 배치
		col0_edit_text->SetWindowPos(nullptr, margin, margin + 4 * (buttonHeight + margin) + (buttonHeight / 2 - margin / 2),
			buttonWidth,
			buttonHeight / 2 - margin / 2, 
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