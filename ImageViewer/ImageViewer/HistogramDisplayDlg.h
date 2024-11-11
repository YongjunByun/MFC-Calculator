#pragma once
#include "afxwin.h"


// HistogramDisplayDlg 대화 상자입니다.

class HistogramDisplayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HistogramDisplayDlg)

public:
	HistogramDisplayDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~HistogramDisplayDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTOGRAM_VIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
};
