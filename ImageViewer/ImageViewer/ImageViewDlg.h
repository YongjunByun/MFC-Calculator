#pragma once


// ImageViewDlg ��ȭ �����Դϴ�.

class ImageViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ImageViewDlg)

public:
	ImageViewDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ImageViewDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGE_VIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
