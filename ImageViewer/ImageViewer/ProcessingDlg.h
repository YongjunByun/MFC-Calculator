#pragma once
#include "ImageProcessing.h"
#include "afxwin.h"
#include "Mat.h"

class ProcessingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ProcessingDlg)

public:
	ProcessingDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ProcessingDlg();
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROCESSING_VIEW };
#endif
	afx_msg void OnBnClickedButtonRotate10();
	afx_msg void OnBnClickedButtonNRotate10();
	afx_msg void OnBnClickedButtonVerticalFlip();
	afx_msg void OnBnClickedButtonHorizontalFlip();
	afx_msg void OnBnClickedButtonScaleMinus();
	afx_msg void OnBnClickedButtonScalePlus();
	afx_msg void OnBnClickedButtonGaussian();
	afx_msg void OnBnClickedButtonMedian();
	afx_msg void OnBnClickedButtonInspection();

	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

private:
	void ResizeControls();

	bool m_isInitialized = false;
	ImageProcessing cv;
	CEdit m_edit_threshold;
};
