#pragma once
#include "afxwin.h"


// MemoryDlg 대화 상자입니다.

class MemoryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MemoryDlg)

public:
	MemoryDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~MemoryDlg();


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEMORY_DIALOG };
#endif
private:
	CFont custom_font;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listbox_memory;
	afx_msg void OnBnClickedButtonClear();
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnDblclkListMemory();
};
