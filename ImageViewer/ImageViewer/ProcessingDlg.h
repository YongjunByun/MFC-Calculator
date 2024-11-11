#pragma once


// ProcessingDlg ��ȭ �����Դϴ�.

class ProcessingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ProcessingDlg)

private:
	bool m_isInitialized = false;
	int m_edit_threshold;
	void ResizeControls();
public:
	ProcessingDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ProcessingDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROCESSING_VIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
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

};
