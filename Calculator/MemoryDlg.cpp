// MemoryDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Calculator.h"
#include "MemoryDlg.h"
#include "afxdialogex.h"
#include "CalculatorDlg.h"


// MemoryDlg ��ȭ �����Դϴ�.

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


// MemoryDlg �޽��� ó�����Դϴ�.


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
	// ���̾�αװ� �ʱ�ȭ�� �� ����Ʈ �ڽ��� ���ڿ� �߰�
	if (!CCalculatorApp::calculator_memory.empty()) {
		for (int i = CCalculatorApp::calculator_memory.size() - 1; i >= 0; i--) {
			m_listbox_memory.AddString(CCalculatorApp::calculator_memory[i]);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void MemoryDlg::OnLbnDblclkListMemory()
{
	CPoint pt;
	GetCursorPos(&pt);
	m_listbox_memory.ScreenToClient(&pt);

	// ���콺 ��ġ���� ������ �ε����� �����´�
	BOOL bOutside = FALSE;
	int nIndex = m_listbox_memory.ItemFromPoint(pt, bOutside);
	if (nIndex != LB_ERR && bOutside == FALSE)
	{
		CString itemText;
		m_listbox_memory.GetText(nIndex, itemText);
		// ���� ���̾�α��� �����͸� �� �ؽ�Ʈ�� ����
		CCalculatorDlg* pParentDialog = (CCalculatorDlg*)GetParent();
		if (pParentDialog)
		{
			pParentDialog->Set_Work_Text(itemText); 
		}
		EndDialog(IDOK);
	}

}