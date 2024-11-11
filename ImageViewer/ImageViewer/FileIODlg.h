#pragma once
#include <vector>
#include "Mat.h"
class ImageDisplayDlg;

class FileIODlg : public CDialogEx
{
	DECLARE_DYNAMIC(FileIODlg)


private: 
	CButton m_Button_Load;
	CButton m_Button_Save;
	CListBox m_List_File;
	std::vector<CString> m_file_paths;
	bool m_isInitialized = false;

public:
	FileIODlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~FileIODlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILE_IO_VIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	//void SetImageDisplayDlg(ImageDisplayDlg* pImageDisplayDlg) { m_pImageDisplayDlg = pImageDisplayDlg; }
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void ResizeControls();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonSave();
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnDblclkListFile();
};
