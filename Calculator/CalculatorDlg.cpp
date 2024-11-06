
// CalculatorDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"
#include "MemoryDlg.h"
#include <math.h>

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
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CCalculatorDlg 대화 상자



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, m_work_text_view(_T("0"))
	, m_log_text_view(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WORK, m_work_text_view);
	DDX_Text(pDX, IDC_EDIT_LOG, m_log_text_view);
	DDX_Control(pDX, IDC_BUTTON_EQUAL, m_button_equal);
	DDX_Control(pDX, IDC_BUTTON_PERCENT, m_button_percent);
	DDX_Control(pDX, IDC_BUTTON_CE, m_button_ce);
	DDX_Control(pDX, IDC_BUTTON_C, m_button_c);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_button_back);
	DDX_Control(pDX, IDC_BUTTON_RECIPROCAL, m_button_reciprocal);
	DDX_Control(pDX, IDC_BUTTON_POW, m_button_pow);
	DDX_Control(pDX, IDC_BUTTON_SQRT, m_button_sqrt);
	DDX_Control(pDX, IDC_BUTTON_DIV, m_button_div);
	DDX_Control(pDX, IDC_BUTTON_MULTIPLE, m_button_multiple);
	DDX_Control(pDX, IDC_BUTTON_SUB, m_button_sub);
	DDX_Control(pDX, IDC_BUTTON_PLUS, m_button_plus);
	DDX_Control(pDX, IDC_BUTTON_DOT, m_button_dot);
	DDX_Control(pDX, IDC_BUTTON_NEGATIVE, m_button_negative);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MC, &CCalculatorDlg::OnBnClickedButtonMc)
	ON_BN_CLICKED(IDC_BUTTON_MR, &CCalculatorDlg::OnBnClickedButtonMr)
	ON_BN_CLICKED(IDC_BUTTON_M_ADD, &CCalculatorDlg::OnBnClickedButtonMAdd)
	ON_BN_CLICKED(IDC_BUTTON_M_SUB, &CCalculatorDlg::OnBnClickedButtonMSub)
	ON_BN_CLICKED(IDC_BUTTON_MS, &CCalculatorDlg::OnBnClickedButtonMs)
	ON_BN_CLICKED(IDC_BUTTON_M, &CCalculatorDlg::OnBnClickedButtonM)
	ON_BN_CLICKED(IDC_BUTTON_PERCENT, &CCalculatorDlg::OnBnClickedButtonPercent)
	ON_BN_CLICKED(IDC_BUTTON_CE, &CCalculatorDlg::OnBnClickedButtonCe)
	ON_BN_CLICKED(IDC_BUTTON_C, &CCalculatorDlg::OnBnClickedButtonC)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CCalculatorDlg::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_RECIPROCAL, &CCalculatorDlg::OnBnClickedButtonReciprocal)
	ON_BN_CLICKED(IDC_BUTTON_POW, &CCalculatorDlg::OnBnClickedButtonPow)
	ON_BN_CLICKED(IDC_BUTTON_SQRT, &CCalculatorDlg::OnBnClickedButtonSqrt)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CCalculatorDlg::OnBnClickedButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_7, &CCalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CCalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CCalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_MULTIPLE, &CCalculatorDlg::OnBnClickedButtonMultiple)
	ON_BN_CLICKED(IDC_BUTTON_4, &CCalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CCalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CCalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &CCalculatorDlg::OnBnClickedButtonSub)
	ON_BN_CLICKED(IDC_BUTTON_1, &CCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CCalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CCalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CCalculatorDlg::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_NEGATIVE, &CCalculatorDlg::OnBnClickedButtonNegative)
	ON_BN_CLICKED(IDC_BUTTON_0, &CCalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_DOT, &CCalculatorDlg::OnBnClickedButtonDot)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, &CCalculatorDlg::OnBnClickedButtonEqual)
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CCalculatorDlg 메시지 처리기
BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	GetClientRect(&m_rcMinimumDialog);
	CalcWindowRect(m_rcMinimumDialog);
	ResizeControls();
	
	//폰트 설정
	CFont font;
	font.CreatePointFont(400, _T("Arial"));
	GetDlgItem(IDC_EDIT_WORK)->SetFont(&font);
	font.Detach();

	//버튼색깔 변경
	Change_Buttons_Color();

	// 초기 실행 시 disable시킬 버튼들
	GetDlgItem(IDC_BUTTON_MC)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_MR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_M)->EnableWindow(FALSE);

	m_dialog_init_complete = true;
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCalculatorDlg::ResizeControls() {
	CRect clientRect;
	GetClientRect(&clientRect);

	// 화면상 edit컨트롤 위치, 크기 정렬
	CWnd* edit_log = GetDlgItem(IDC_EDIT_LOG);
	CWnd* edit_work = GetDlgItem(IDC_EDIT_WORK);
	edit_log->SetWindowPos(nullptr, 15, 15, clientRect.Width() - 30, (int)(clientRect.Height() * 0.05), SWP_NOZORDER);
	CRect edit_log_rect;
	edit_log->GetWindowRect(&edit_log_rect);
	edit_work->SetWindowPos(nullptr, 15, 15 + edit_log_rect.Height(), clientRect.Width() - 30, (int)(clientRect.Height() * 0.25), SWP_NOZORDER);

	

	// 화면상 버튼들 객체 다 가져옴. 위치, 크기 정렬
	CWnd* row0_buttons[] = {
		GetDlgItem(IDC_BUTTON_MC),
		GetDlgItem(IDC_BUTTON_MR),
		GetDlgItem(IDC_BUTTON_M_ADD),
		GetDlgItem(IDC_BUTTON_M_SUB),
		GetDlgItem(IDC_BUTTON_MS),
		GetDlgItem(IDC_BUTTON_M)
	};
	CWnd* row1_buttons[] = {
		GetDlgItem(IDC_BUTTON_PERCENT),
		GetDlgItem(IDC_BUTTON_CE),
		GetDlgItem(IDC_BUTTON_C),
		GetDlgItem(IDC_BUTTON_BACK)
	};
	CWnd* row2_buttons[] = {
		GetDlgItem(IDC_BUTTON_RECIPROCAL),
		GetDlgItem(IDC_BUTTON_POW),
		GetDlgItem(IDC_BUTTON_SQRT),
		GetDlgItem(IDC_BUTTON_DIV),
	};
	CWnd* row3_buttons[] = {
		GetDlgItem(IDC_BUTTON_7),
		GetDlgItem(IDC_BUTTON_8),
		GetDlgItem(IDC_BUTTON_9),
		GetDlgItem(IDC_BUTTON_MULTIPLE),
	};
	CWnd* row4_buttons[] = {
		GetDlgItem(IDC_BUTTON_4),
		GetDlgItem(IDC_BUTTON_5),
		GetDlgItem(IDC_BUTTON_6),
		GetDlgItem(IDC_BUTTON_SUB),
	};
	CWnd* row5_buttons[] = {
		GetDlgItem(IDC_BUTTON_1),
		GetDlgItem(IDC_BUTTON_2),
		GetDlgItem(IDC_BUTTON_3),
		GetDlgItem(IDC_BUTTON_PLUS),
	};
	CWnd* row6_buttons[] = {
		GetDlgItem(IDC_BUTTON_NEGATIVE),
		GetDlgItem(IDC_BUTTON_0),
		GetDlgItem(IDC_BUTTON_DOT),
		GetDlgItem(IDC_BUTTON_EQUAL),
	};

	int row0_buttonCount = sizeof(row0_buttons) / sizeof(row0_buttons[0]);
	int row1_buttonCount = sizeof(row1_buttons) / sizeof(row1_buttons[0]);
	int col_buttonCount = 7; //한 열에 7개 버튼있슴

	
	int button_totalWidth = clientRect.Width() - 60; // 윈도우에서 양옆 마진 30씩 주기 위한 -60
	int button_totalHeight = clientRect.Height() - (int)(clientRect.Height() * 0.30);
	int row0_buttonWidth = (int)(button_totalWidth / row0_buttonCount);
	int row0_buttonHeight = (int)(button_totalHeight / col_buttonCount / 2); // 메모리관련 버튼은 조금 작게
	int row1_buttonWidth = (int)(button_totalWidth / row1_buttonCount);
	int row1_buttonHeight = (int)(button_totalHeight / col_buttonCount);
	int buttonSpacing = 0;

	// 첫번째 row의 버튼 정렬
	for (int i = 0; i < row0_buttonCount; ++i)
	{
		int xPos = 30 + (row0_buttonWidth + buttonSpacing) * i;  // 시작 여백 + (버튼 너비 + 간격) * 인덱스
		row0_buttons[i]->SetWindowPos(nullptr, xPos, clientRect.Height() * 0.30 + row0_buttonHeight, row0_buttonWidth, row0_buttonHeight, SWP_NOZORDER);
	}
	// 두번째 row부터의 버튼 정렬
	for (int i = 0; i < col_buttonCount-1; ++i) {
		for (int j = 0; j < row1_buttonCount; ++j)
		{
			int xPos = 30 + (row1_buttonWidth + buttonSpacing) * j;  // 시작 여백 + (버튼 너비 + 간격) * 인덱스
			if(i==0)
				row1_buttons[j]->SetWindowPos(nullptr, xPos, clientRect.Height() * 0.30 + row1_buttonHeight, row1_buttonWidth, row1_buttonHeight, SWP_NOZORDER);
			else if (i == 1)
				row2_buttons[j]->SetWindowPos(nullptr, xPos, clientRect.Height() * 0.30 + row1_buttonHeight * 2, row1_buttonWidth, row1_buttonHeight, SWP_NOZORDER);
			else if (i == 2)
				row3_buttons[j]->SetWindowPos(nullptr, xPos, clientRect.Height() * 0.30 + row1_buttonHeight * 3, row1_buttonWidth, row1_buttonHeight, SWP_NOZORDER);
			else if (i == 3)
				row4_buttons[j]->SetWindowPos(nullptr, xPos, clientRect.Height() * 0.30 + row1_buttonHeight * 4, row1_buttonWidth, row1_buttonHeight, SWP_NOZORDER);
			else if (i == 4)
				row5_buttons[j]->SetWindowPos(nullptr, xPos, clientRect.Height() * 0.30 + row1_buttonHeight * 5, row1_buttonWidth, row1_buttonHeight, SWP_NOZORDER);
			else if (i == 5)
				row6_buttons[j]->SetWindowPos(nullptr, xPos, clientRect.Height() * 0.30 + row1_buttonHeight * 6, row1_buttonWidth, row1_buttonHeight, SWP_NOZORDER);
		}
	}
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalculatorDlg::OnPaint()
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
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// Memory Clear
void CCalculatorDlg::OnBnClickedButtonMc()
{
	 CCalculatorApp::calculator_memory.clear();
	GetDlgItem(IDC_BUTTON_MC)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_MR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_M)->EnableWindow(FALSE);
}

// Memory Read
void CCalculatorDlg::OnBnClickedButtonMr()
{
	UpdateData(TRUE);
	CString memory_var = CCalculatorApp::calculator_memory.back();
	m_work_text_view = memory_var;
	UpdateData(FALSE);
}
// Memory Add
void CCalculatorDlg::OnBnClickedButtonMAdd()
{
	UpdateData(TRUE);
	if (CCalculatorApp::calculator_memory.empty()) return;
	CString &memory_var = CCalculatorApp::calculator_memory.back();
	double num1 = _ttof(memory_var);
	double num2 = _ttof(m_work_text_view);
	memory_var.Format(L"%.15g", num1 + num2);
	UpdateData(FALSE);
}

// Memory Sub
void CCalculatorDlg::OnBnClickedButtonMSub()
{
	UpdateData(TRUE);
	if (CCalculatorApp::calculator_memory.empty()) return;
	CString &memory_var = CCalculatorApp::calculator_memory.back();
	double num1 = _ttof(memory_var);
	double num2 = _ttof(m_work_text_view);
	memory_var.Format(L"%.15g", num1 - num2);
	UpdateData(FALSE);
}
// Memory Save
void CCalculatorDlg::OnBnClickedButtonMs()
{
	CCalculatorApp::calculator_memory.push_back(m_work_text_view);

	GetDlgItem(IDC_BUTTON_MC)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_M)->EnableWindow(TRUE);
	m_clear_work_text = true;
}
// Show Memory
void CCalculatorDlg::OnBnClickedButtonM()
{
	MemoryDlg dlg;
	dlg.DoModal();
	if (CCalculatorApp::calculator_memory.empty()) {
		GetDlgItem(IDC_BUTTON_MC)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_MR)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_M)->EnableWindow(FALSE);
	}
}
void CCalculatorDlg::OnBnClickedButtonCe()
{
	UpdateData(TRUE);
	if (m_clear_work_text == true) {
		m_clear_work_text = false;
	}
	m_work_text_view = "0";
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButtonC()
{
	UpdateData(TRUE);
	if (m_clear_work_text == true) {
		m_clear_work_text = false;
	}

	m_work_text_view = "0";
	m_log_text_view.Empty();
	m_operation.Empty();
	m_first_num.Empty();
	m_second_num.Empty();
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButtonBack()
{
	UpdateData(TRUE);
	if(m_work_text_view.GetLength() > 0)
		m_work_text_view.Delete(m_work_text_view.GetLength() - 1, 1);
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButtonReciprocal()
{
	UpdateData(TRUE);
	double num = _ttof(m_work_text_view);
	if (num != 0) {
		double result = 1.0 / num;
		m_log_text_view += L"1/(" + m_work_text_view + L")";
		m_work_text_view.Format(L"%.15g", result);
	}
	else {
		m_work_text_view = L"Error";  // 0으로 나누기 방지
	}
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButtonPercent()
{
	UpdateData(TRUE);
	
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButtonPow()
{
	UpdateData(TRUE);
	double root = 0.0;
	root = pow(_ttof(m_work_text_view), 2);
	if (!m_operation.IsEmpty()) {
		m_second_num.Format(L"%.15g", root);
		m_log_text_view += L"sqr(" + m_work_text_view + L")";
		Calculate(m_first_num, m_second_num, m_operation);
	}
	else {
		m_first_num.Format(L"%.15g", root);
		m_log_text_view = L"sqr(" + m_work_text_view + L")";
	}
	m_work_text_view.Format(L"%.15g", root);
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButtonSqrt()
{
	UpdateData(TRUE);
	double squareRoot = 0.0;
	// 음수일 경우 제곱근을 계산할 수 없으므로 예외 처리
	if (_ttof(m_work_text_view) < 0) {
		m_work_text_view.Format(_T("ERROR"));
		UpdateData(FALSE);
		return;
	}
	squareRoot = sqrt(_ttof(m_work_text_view));
	if (!m_operation.IsEmpty()) {
		m_second_num.Format(L"%.15g", squareRoot);
		m_log_text_view += L"√(" + m_work_text_view + L")";
		Calculate(m_first_num, m_second_num, m_operation);
	}
	else {
		m_first_num.Format(L"%.15g", squareRoot);
		m_log_text_view = L"√(" + m_work_text_view + L")";
	}
	m_work_text_view.Format(L"%.15g", squareRoot);
	UpdateData(FALSE);
}

void CCalculatorDlg::OnBnClickedButton0()
{
	UpdateData(TRUE);
	if (m_clear_work_text == true) {
		m_work_text_view.Empty();
		m_clear_work_text = false;
	}
	if (m_work_text_view == "0")
		m_work_text_view = L"";
	m_work_text_view += CString(L"0");
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	if (m_clear_work_text == true) {
		m_work_text_view.Empty();
		m_clear_work_text = false;
	}
	if (m_work_text_view == "0")
		m_work_text_view = L"";
	m_work_text_view += CString("1");
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	if (m_clear_work_text == true) {
		m_work_text_view.Empty();
		m_clear_work_text = false;
	}
	if (m_work_text_view == "0")
		m_work_text_view = L"";
	m_work_text_view += CString("2");
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButton3()
{
	UpdateData(TRUE);
	if (m_clear_work_text == true) {
		m_work_text_view.Empty();
		m_clear_work_text = false;
	}
	if (m_work_text_view == "0")
		m_work_text_view = L"";
	m_work_text_view += CString("3");
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButton4()
{
	UpdateData(TRUE);
	if (m_clear_work_text == true) {
		m_work_text_view.Empty();
		m_clear_work_text = false;
	}
	if (m_work_text_view == "0")
		m_work_text_view = L"";
	m_work_text_view += CString("4");
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButton5()
{
	UpdateData(TRUE);
	if (m_clear_work_text == true) {
		m_work_text_view.Empty();
		m_clear_work_text = false;
	}
	if (m_work_text_view == "0")
		m_work_text_view = L"";
	m_work_text_view += CString("5");
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButton6()
{
	UpdateData(TRUE);

	if (m_clear_work_text == true) {
		m_work_text_view.Empty();
		m_clear_work_text = false;
	}
	if (m_work_text_view == "0")
		m_work_text_view = L"";
	m_work_text_view += CString("6");
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButton7()
{
	UpdateData(TRUE);
	if (m_clear_work_text == true) {
		m_work_text_view.Empty();
		m_clear_work_text = false;
	}
	if (m_work_text_view == "0")
		m_work_text_view = L"";
	m_work_text_view += CString("7");
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButton8()
{
	UpdateData(TRUE);
	if (m_clear_work_text == true) {
		m_work_text_view.Empty();
		m_clear_work_text = false;
	}
	if (m_work_text_view == "0")
		m_work_text_view = L"";
	m_work_text_view += CString("8");
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButton9()
{
	UpdateData(TRUE);
	if (m_clear_work_text == true) {
		m_work_text_view.Empty();
		m_clear_work_text = false;
	}
	if (m_work_text_view == "0")
		m_work_text_view = L"";
	m_work_text_view += CString("9");
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButtonPlus()
{
	UpdateData(TRUE);
	if (!m_operation.IsEmpty()) {
		Calculate(m_first_num, m_work_text_view, m_operation);
	}
	m_first_num = m_work_text_view;
	
	m_operation = L"+";
	m_log_text_view = m_first_num + L"+";
	m_clear_work_text = true;
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButtonSub()
{
	UpdateData(TRUE);
	if (!m_operation.IsEmpty()) {
		Calculate(m_first_num, m_work_text_view, m_operation);
	}
	m_first_num = m_work_text_view;
	m_operation = L"-";
	m_log_text_view = m_first_num + L"-";
	m_clear_work_text = true;
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButtonDiv()
{
	UpdateData(TRUE);
	if (!m_operation.IsEmpty()) {
		Calculate(m_first_num, m_work_text_view, m_operation);
	}
	m_first_num = m_work_text_view;
	m_operation = L"/";
	m_log_text_view = m_first_num + L"/";
	m_clear_work_text = true;
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButtonMultiple()
{
	UpdateData(TRUE);
	if (!m_operation.IsEmpty()) {
		Calculate(m_first_num, m_work_text_view, m_operation);
	}
	m_first_num = m_work_text_view;

	m_operation = L"x";
	m_log_text_view = m_first_num + L"x";
	m_clear_work_text = true;
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButtonNegative()
{
	UpdateData(TRUE);
	// 문자열이 비어있는 경우 처리
	if (m_work_text_view.IsEmpty() || m_work_text_view == "0") {
		return;
	}

	// 첫 번째 문자가 '-'이면 제거
	if (m_work_text_view[0] == '-') {
		m_work_text_view.Delete(0); // 첫 번째 문자 삭제
	}
	else {
		// 첫 번째 문자가 '-'가 아니라면 앞에 '-' 추가
		m_work_text_view.Insert(0, '-'); // 앞에 '-' 추가
	}
	if (m_clear_work_text == true) {
		m_log_text_view += m_work_text_view;
		m_clear_work_text = false;
	}
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButtonDot()
{
	UpdateData(TRUE);
	m_work_text_view += CString(".");
	UpdateData(FALSE);
}
void CCalculatorDlg::OnBnClickedButtonEqual()
{
	UpdateData(TRUE);
	m_second_num = m_work_text_view;  // 두 번째 숫자 저장
	if (!m_operation.IsEmpty()) {
		Calculate(m_first_num, m_work_text_view, m_operation);
	}
	m_log_text_view = m_first_num + m_operation + m_second_num + L"=";
	
	m_operation.Empty();
	m_clear_work_text = true;
	UpdateData(FALSE);
}


void CCalculatorDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	lpMMI->ptMinTrackSize.x = m_rcMinimumDialog.Width();
	lpMMI->ptMinTrackSize.y = m_rcMinimumDialog.Height();
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CCalculatorDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if(m_dialog_init_complete == true)
		ResizeControls();
}

void CCalculatorDlg::Change_Buttons_Color() {
	const COLORREF color_background_btn = RGB(180, 180, 180);
	m_button_equal.EnableWindowsTheming(FALSE);
	m_button_percent.EnableWindowsTheming(FALSE);
	m_button_ce.EnableWindowsTheming(FALSE);
	m_button_c.EnableWindowsTheming(FALSE);
	m_button_back.EnableWindowsTheming(FALSE);
	m_button_reciprocal.EnableWindowsTheming(FALSE);
	m_button_pow.EnableWindowsTheming(FALSE);
	m_button_sqrt.EnableWindowsTheming(FALSE);
	m_button_div.EnableWindowsTheming(FALSE);
	m_button_multiple.EnableWindowsTheming(FALSE);
	m_button_sub.EnableWindowsTheming(FALSE);
	m_button_plus.EnableWindowsTheming(FALSE);
	m_button_dot.EnableWindowsTheming(FALSE);
	m_button_negative.EnableWindowsTheming(FALSE);

	m_button_equal.SetFaceColor(color_background_btn);
	m_button_percent.SetFaceColor(color_background_btn);
	m_button_ce.SetFaceColor(color_background_btn);
	m_button_c.SetFaceColor(color_background_btn);
	m_button_back.SetFaceColor(color_background_btn);
	m_button_reciprocal.SetFaceColor(color_background_btn);
	m_button_pow.SetFaceColor(color_background_btn);
	m_button_sqrt.SetFaceColor(color_background_btn);
	m_button_div.SetFaceColor(color_background_btn);
	m_button_multiple.SetFaceColor(color_background_btn);
	m_button_sub.SetFaceColor(color_background_btn);
	m_button_plus.SetFaceColor(color_background_btn);
	m_button_dot.SetFaceColor(color_background_btn);
	m_button_negative.SetFaceColor(color_background_btn);
}

void CCalculatorDlg::Set_Work_Text(CString text)
{
	UpdateData(TRUE);
	m_work_text_view = text;
	m_clear_work_text = true;
	UpdateData(FALSE);
}

void CCalculatorDlg::Calculate(CString first_num, CString second_num, CString op) {
	double num1 = _ttof(first_num);
	double num2 = _ttof(second_num);
	double result = 0.0;
	if (op == "+")
		result = num1 + num2;
	else if (op == "-")
		result = num1 - num2;
	else if (op == "x")
		result = num1 * num2;
	else if (op == "/")
		result = (num2 != 0) ? num1 / num2 : 0;  // 0으로 나누기 방지
	m_work_text_view.Format(L"%.15g", result);
}