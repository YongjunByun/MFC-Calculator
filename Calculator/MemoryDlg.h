#pragma once
#include "afxwin.h"


// MemoryDlg ��ȭ �����Դϴ�.

class MemoryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MemoryDlg)

public:
	MemoryDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~MemoryDlg();


// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEMORY_DIALOG };
#endif
private:
	CFont custom_font;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listbox_memory;
	afx_msg void OnBnClickedButtonClear();
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnDblclkListMemory();
};
