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
	ImageDisplayDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ImageDisplayDlg();
	void UpdateImage(Mat& img);
	int test;
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGEDISPLAY_VIEW };

#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
