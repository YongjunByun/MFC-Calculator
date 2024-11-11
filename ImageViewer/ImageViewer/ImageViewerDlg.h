#pragma once
#include "atlimage.h"
class FileIODlg;
class HistogramDisplayDlg;
class ProcessingDlg;
class ImageDisplayDlg;

class CImageViewerDlg : public CDialogEx
{
private:
	FileIODlg* m_FileIODlg;
	HistogramDisplayDlg* m_HistogramDisplayDlg;
	ProcessingDlg* m_ProcessingDlg;
	ImageDisplayDlg* m_ImageDisplayDlg;
	bool m_isInitialized = false;
	void ResizeDlgs();

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();// ������ �޽��� �� �Լ�
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CImageViewerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	CImage m_image_view;
	ImageDisplayDlg* GetImageDisplayDlg();
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGEVIEWER_DIALOG };
#endif
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
};
