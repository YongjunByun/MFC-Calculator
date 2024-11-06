// MemoryDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Calculator.h"
#include "MemoryDlg.h"
#include "afxdialogex.h"
#include "CalculatorDlg.h"


// MemoryDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(MemoryDlg, CDialogEx)

MemoryDlg::MemoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MEMORY_DIALOG, pParent)
{
	custom_font.CreatePointFont(220, _T("Arial"));
}

MemoryDlg::~MemoryDlg()
{
}
void MemoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MEMORY, m_listbox_memory);
}


BEGIN_MESSAGE_MAP(MemoryDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &MemoryDlg::OnBnClickedButtonClear)
	ON_WM_LBUTTONDBLCLK()
	ON_LBN_DBLCLK(IDC_LIST_MEMORY, &MemoryDlg::OnLbnDblclkListMemory)
END_MESSAGE_MAP()


// MemoryDlg 메시지 처리기입니다.


void MemoryDlg::OnBnClickedButtonClear()
{
	UpdateData(TRUE);
	m_listbox_memory.ResetContent();
	CCalculatorApp::calculator_memory.clear();
	UpdateData(FALSE);
}



BOOL MemoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_listbox_memory.SetFont(&custom_font);
	// 다이얼로그가 초기화된 후 리스트 박스에 문자열 추가
	if (!CCalculatorApp::calculator_memory.empty()) {
		for (int i = CCalculatorApp::calculator_memory.size() - 1; i >= 0; i--) {
			m_listbox_memory.AddString(CCalculatorApp::calculator_memory[i]);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void MemoryDlg::OnLbnDblclkListMemory()
{
	CPoint pt;
	GetCursorPos(&pt);
	m_listbox_memory.ScreenToClient(&pt);

	// 마우스 위치에서 아이템 인덱스를 가져온다
	BOOL bOutside = FALSE;
	int nIndex = m_listbox_memory.ItemFromPoint(pt, bOutside);
	if (nIndex != LB_ERR && bOutside == FALSE)
	{
		CString itemText;
		m_listbox_memory.GetText(nIndex, itemText);
		// 상위 다이얼로그의 포인터를 얻어서 텍스트를 전달
		CCalculatorDlg* pParentDialog = (CCalculatorDlg*)GetParent();
		if (pParentDialog)
		{
			pParentDialog->Set_Work_Text(itemText); 
		}
		EndDialog(IDOK);
	}

}