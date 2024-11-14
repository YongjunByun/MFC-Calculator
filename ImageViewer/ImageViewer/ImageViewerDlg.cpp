
// ImageViewerDlg.cpp : 구현 파일
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


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CImageViewerDlg 대화 상자



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


// CImageViewerDlg 메시지 처리기

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
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CImageViewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CImageViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CImageViewerDlg::ResizeDlgs() {
	CRect clientRect;
	GetClientRect(&clientRect);
	int col1Width = (int)(clientRect.Width() * 0.25);  // 1열: 25%
	int col2Width = (int)(clientRect.Width() * 0.75);  // 2열: 75%
	int row1Height = (int)(clientRect.Height() / 10 * 3); // 1행 30%
	int row2Height = (int)(clientRect.Height() / 10 * 3); // 1행 30%
	int row3Height = (int)(clientRect.Height() / 10 * 4); // 1행 40%

	m_HistogramDisplayDlg->SetWindowPos(NULL, 0, 0, col1Width, row1Height, SWP_NOZORDER);
	m_FileIODlg->SetWindowPos(NULL, 0, row1Height, col1Width, row2Height, SWP_NOZORDER);
	m_ProcessingDlg->SetWindowPos(NULL, 0, row1Height + row2Height, col1Width, row3Height, SWP_NOZORDER);
	// 2열: m_ImageDisplayDlg를 꽉 채우도록 배치
	m_ImageDisplayDlg->SetWindowPos(NULL, col1Width, 0, col2Width, clientRect.Height(), SWP_NOZORDER);

	m_HistogramDisplayDlg->ShowWindow(SW_SHOW);
	m_FileIODlg->ShowWindow(SW_SHOW);
	m_ProcessingDlg->ShowWindow(SW_SHOW);
	m_ImageDisplayDlg->ShowWindow(SW_SHOW);
}