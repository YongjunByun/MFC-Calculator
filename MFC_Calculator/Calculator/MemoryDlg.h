#pragma once
#include "afxwin.h"


// MemoryDlg ��ȭ �����Դϴ�.

class MemoryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MemoryDlg)

public:
	MemoryDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~MemoryDlg();
	CListBox m_listbox_memory;
	afx_msg void OnBnClickedButtonClear();
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnDblclkListMemory();

	static std::vector<CString> calculator_memory;

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEMORY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()

private:
	CFont custom_font;
};
