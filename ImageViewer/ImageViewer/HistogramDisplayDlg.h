#pragma once
#include "afxwin.h"


// HistogramDisplayDlg ��ȭ �����Դϴ�.

class HistogramDisplayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HistogramDisplayDlg)

public:
	HistogramDisplayDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~HistogramDisplayDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTOGRAM_VIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
};
