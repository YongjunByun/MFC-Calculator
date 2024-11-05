
// CalculatorDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxbutton.h"


// CCalculatorDlg 대화 상자
class CCalculatorDlg : public CDialogEx
{
// 생성입니다.
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
private:
	CRect m_rcMinimumDialog;

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	/// <summary>
	/// 텍스트블록이랑 버튼을 화면비에 맞게 변경할 함수
	/// </summary>
	void ResizeControls();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonMc();
	afx_msg void OnBnClickedButtonMr();
	afx_msg void OnBnClickedButtonMAdd();
	afx_msg void OnBnClickedButtonMSub();
	afx_msg void OnBnClickedButtonMs();
	afx_msg void OnBnClickedButtonM();
	afx_msg void OnBnClickedButtonPercent();
	afx_msg void OnBnClickedButtonCe();
	afx_msg void OnBnClickedButtonC();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonReciprocal();
	afx_msg void OnBnClickedButtonPow();
	afx_msg void OnBnClickedButtonSqrt();
	afx_msg void OnBnClickedButtonDiv();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButtonMultiple();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButtonSub();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonNegative();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButtonDot();
	afx_msg void OnBnClickedButtonEqual();
	CString m_work_text_view;// 화면상에 보이는 텍스트
	CString m_log_text_view;
	bool m_clear_work_text = false; // 다음 버튼입력에 화면을 초기화 할지 말지 결정할 변수
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	bool m_dialog_init_complete = false;

	void Change_Buttons_Color(); //버튼색깔 일괄변경 함수
	CMFCButton m_button_equal;
	CMFCButton m_button_percent;
	CMFCButton m_button_ce;
	CMFCButton m_button_c;
	CMFCButton m_button_back;
	CMFCButton m_button_reciprocal;
	CMFCButton m_button_pow;
	CMFCButton m_button_sqrt;
	CMFCButton m_button_div;
	CMFCButton m_button_multiple;
	CMFCButton m_button_sub;
	CMFCButton m_button_plus;
	CMFCButton m_button_dot;
	CMFCButton m_button_negative;
};
