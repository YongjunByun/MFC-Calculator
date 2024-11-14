#pragma once
#include "afxwin.h"
#include "Mat.h"

class ImageDisplayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ImageDisplayDlg)

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGEDISPLAY_VIEW };
#endif
	ImageDisplayDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ImageDisplayDlg();
	void UpdateImage(Mat& img);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void ResizeControls();

	Mat GetImage() { return m_img_org; }
	void SetImage(Mat& img) { m_img_org = img; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()

private:
	CStatic m_image_control; // ���� ��Ʈ��
	CImage m_img_display;    // ���� ��Ʈ�ѿ� ��� �̹���
	Mat m_img_org;				 // ���� ������ ���� Mat���� ����� �׽� ������Ʈ����
	Mat m_img_resized;
	bool m_isInitialized = false;

};
