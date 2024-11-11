#pragma once
#include "afxwin.h"
#include "Mat.h"

class ImageDisplayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ImageDisplayDlg)

private:
	CStatic m_image_control;
	CImage m_img_display;
	bool m_isInitialized = false;

public:
	ImageDisplayDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ImageDisplayDlg();
	void UpdateImage(Mat& img);
	int test;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGEDISPLAY_VIEW };

#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
