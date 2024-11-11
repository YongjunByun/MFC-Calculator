// ProcessingDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageViewer.h"
#include "ProcessingDlg.h"
#include "afxdialogex.h"


// ProcessingDlg ��ȭ �����Դϴ�.

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ProcessingDlg::OnBnClickedButtonNRotate10()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ProcessingDlg::OnBnClickedButtonVerticalFlip()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ProcessingDlg::OnBnClickedButtonHorizontalFlip()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ProcessingDlg::OnBnClickedButtonScaleMinus()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ProcessingDlg::OnBnClickedButtonScalePlus()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ProcessingDlg::OnBnClickedButtonGaussian()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ProcessingDlg::OnBnClickedButtonMedian()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ProcessingDlg::OnBnClickedButtonInspection()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


BOOL ProcessingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_isInitialized = true;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
	int buttonHeight = (int)(clientRect.Height() / 5) - 10; // 5��
	int buttonWidth = (int)(clientRect.Width() / 2) - 10; // 2��
	int margin = 10; // ��ư �� ����
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

	// ù ��° ���� ��ư ��ġ ����
	for (int i = 0; i < 4; ++i) // �� �Ʒ� ��ư ����
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
		// �ϴܿ� edit text ��ġ
		col0_edit_text->SetWindowPos(nullptr, margin, margin + 4 * (buttonHeight + margin) + (buttonHeight / 2 - margin / 2),
			buttonWidth,
			buttonHeight / 2 - margin / 2, 
			SWP_NOZORDER);
	}
	// �� ��° ���� ��ư ��ġ ����
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