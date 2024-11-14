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
	ImageDisplayDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ImageDisplayDlg();
	void UpdateImage(Mat& img);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void ResizeControls();

	Mat GetImage() { return m_img_org; }
	void SetImage(Mat& img) { m_img_org = img; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

private:
	CStatic m_image_control; // 픽쳐 컨트롤
	CImage m_img_display;    // 픽쳐 컨트롤에 띄울 이미지
	Mat m_img_org;				 // 파일 저장을 위해 Mat형도 멤버로 항시 업데이트해줌
	Mat m_img_resized;
	bool m_isInitialized = false;

};
