#pragma once
#include "atlimage.h"
class FileIODlg;
class HistogramDisplayDlg;
class ProcessingDlg;
class ImageDisplayDlg;

class CImageViewerDlg : public CDialogEx
{
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGEVIEWER_DIALOG };
#endif
	CImageViewerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	~CImageViewerDlg();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	ImageDisplayDlg* GetImageDisplayDlg();
	HistogramDisplayDlg* GetHistogramDisplayDlg();
	
	

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();// 생성된 메시지 맵 함수
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	FileIODlg* m_FileIODlg;
	HistogramDisplayDlg* m_HistogramDisplayDlg;
	ProcessingDlg* m_ProcessingDlg;
	ImageDisplayDlg* m_ImageDisplayDlg;
	bool m_isInitialized = false;
	CImage m_image_view;
	CRect m_rcMinimumDialog;
	void ResizeDlgs();
};
