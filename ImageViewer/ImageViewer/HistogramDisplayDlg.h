#pragma once
#include "afxwin.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "Mat.h"

class HistogramDisplayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HistogramDisplayDlg)

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTOGRAM_VIEW };
#endif
	HistogramDisplayDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~HistogramDisplayDlg();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonStretch();
	// todo 어짜피 16비트를 히스토그램을 화면상에 표현할라면 다운샘플링 해야되는데 is16Bit가 의미있나
	void DrawHistogram(Mat& in_img);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

private:
	bool m_isInitialized = false;
	int m_n_minhistogram = 0;
	int m_n_maxhistogram = 65535;
	bool m_is16bit = false;
	void ResizeControls();
	CEdit m_minhistogram;
	CEdit m_maxhistogram;
	bool CheckEditRange(int mininput, int maxinput, bool is16bit);
	int MaxHistBarHeight(int threshold_min, int threshold_max, std::vector<int> histogram);

};
