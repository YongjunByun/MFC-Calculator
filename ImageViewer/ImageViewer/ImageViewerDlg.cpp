
// ImageViewerDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ImageViewer.h"
#include "ImageViewerDlg.h"
#include "afxdialogex.h"
#include "FileIODlg.h"
#include "ImageDisplayDlg.h"
#include "HistogramDisplayDlg.h"
#include "ProcessingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageViewerDlg ��ȭ ����



CImageViewerDlg::CImageViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IMAGEVIEWER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_FileIODlg = new FileIODlg;
	m_HistogramDisplayDlg = new HistogramDisplayDlg;
	m_ProcessingDlg = new ProcessingDlg;
	m_ImageDisplayDlg = new ImageDisplayDlg;
}

CImageViewerDlg::~CImageViewerDlg()
{
	delete m_FileIODlg;
	delete m_HistogramDisplayDlg;
	delete m_ProcessingDlg;
	delete m_ImageDisplayDlg;
}

void CImageViewerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (m_isInitialized == false)
		return;
	ResizeDlgs();
}

ImageDisplayDlg* CImageViewerDlg::GetImageDisplayDlg()
{
	return m_ImageDisplayDlg;
}

HistogramDisplayDlg * CImageViewerDlg::GetHistogramDisplayDlg()
{
	return m_HistogramDisplayDlg;
}

void CImageViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_BUTTON1, m_image_view);
}

BEGIN_MESSAGE_MAP(CImageViewerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CImageViewerDlg �޽��� ó����

BOOL CImageViewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);

	int dialogWidth = 1280;
	int dialogHeight = 960;
	SetWindowPos(NULL, 0, 0, dialogWidth, dialogHeight, SWP_NOMOVE | SWP_NOZORDER);

	m_FileIODlg->Create(IDD_FILE_IO_VIEW, this);
	m_HistogramDisplayDlg->Create(IDD_HISTOGRAM_VIEW, this);
	m_ProcessingDlg->Create(IDD_PROCESSING_VIEW, this);
	m_ImageDisplayDlg->Create(IDD_IMAGEDISPLAY_VIEW, this);
	ResizeDlgs();
	m_isInitialized = true;
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CImageViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CImageViewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CImageViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CImageViewerDlg::ResizeDlgs() {
	CRect clientRect;
	GetClientRect(&clientRect);
	int col1Width = (int)(clientRect.Width() * 0.25);  // 1��: 25%
	int col2Width = (int)(clientRect.Width() * 0.75);  // 2��: 75%
	int row1Height = (int)(clientRect.Height() / 10 * 3); // 1�� 30%
	int row2Height = (int)(clientRect.Height() / 10 * 3); // 1�� 30%
	int row3Height = (int)(clientRect.Height() / 10 * 4); // 1�� 40%

	m_HistogramDisplayDlg->SetWindowPos(NULL, 0, 0, col1Width, row1Height, SWP_NOZORDER);
	m_FileIODlg->SetWindowPos(NULL, 0, row1Height, col1Width, row2Height, SWP_NOZORDER);
	m_ProcessingDlg->SetWindowPos(NULL, 0, row1Height + row2Height, col1Width, row3Height, SWP_NOZORDER);
	// 2��: m_ImageDisplayDlg�� �� ä�쵵�� ��ġ
	m_ImageDisplayDlg->SetWindowPos(NULL, col1Width, 0, col2Width, clientRect.Height(), SWP_NOZORDER);

	m_HistogramDisplayDlg->ShowWindow(SW_SHOW);
	m_FileIODlg->ShowWindow(SW_SHOW);
	m_ProcessingDlg->ShowWindow(SW_SHOW);
	m_ImageDisplayDlg->ShowWindow(SW_SHOW);
}