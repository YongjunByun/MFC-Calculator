// HistogramDisplayDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageViewer.h"
#include "HistogramDisplayDlg.h"
#include "afxdialogex.h"
#include "ImageViewerDlg.h"
#include "ImageProcessing.h"
#include "ImageDisplayDlg.h"


IMPLEMENT_DYNAMIC(HistogramDisplayDlg, CDialogEx)

HistogramDisplayDlg::HistogramDisplayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HISTOGRAM_VIEW, pParent)
{

}

HistogramDisplayDlg::~HistogramDisplayDlg()
{
}

void HistogramDisplayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MIN, m_minhistogram);
	DDX_Control(pDX, IDC_EDIT_MAX, m_maxhistogram);
}

BEGIN_MESSAGE_MAP(HistogramDisplayDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &HistogramDisplayDlg::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_STRETCH, &HistogramDisplayDlg::OnBnClickedButtonStretch)
	ON_WM_SIZE()
END_MESSAGE_MAP()

void HistogramDisplayDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);	
	if (m_isInitialized == false)
		return;
	ResizeControls();
}

BOOL HistogramDisplayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_isInitialized = true;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void HistogramDisplayDlg::ResizeControls() {
	CRect clientRect;
	GetClientRect(&clientRect);
	int margin = 10; // 버튼 간 마진

	CWnd* static_histogram = GetDlgItem(IDC_STATIC_HISTOGRAM);
	CWnd* static_min_histogram = GetDlgItem(IDC_STATIC_MIN_HIST);
	CWnd* static_max_histogram = GetDlgItem(IDC_STATIC_MAX_HIST);
	CWnd* btn_apply = GetDlgItem(IDC_BUTTON_APPLY);
	CWnd* btn_stretch = GetDlgItem(IDC_BUTTON_STRETCH);
	
	CWnd* static_min = GetDlgItem(IDC_STATIC_MIN);
	CWnd* static_max = GetDlgItem(IDC_STATIC_MAX);
	CWnd* edit_min = GetDlgItem(IDC_EDIT_MIN);
	CWnd* edit_max = GetDlgItem(IDC_EDIT_MAX);

	int row1_height = static_cast<int>(clientRect.Height() * 0.8);  // 첫 번째 행 80%
	int row2_height = static_cast<int>(clientRect.Height() * 0.06);  // 세 번째 행 6%
	int row3_height = static_cast<int>(clientRect.Height() * 0.07);  // 세 번째 행 7%
	int row4_height = static_cast<int>(clientRect.Height() * 0.07);  // 네 번째 행 7%
	int col_width = clientRect.Width() / 4;


	static_histogram->SetWindowPos(NULL, 5, 5, clientRect.Width() - margin, row1_height - margin, SWP_NOZORDER);
	static_min_histogram->SetWindowPos(NULL, 0, row1_height, col_width, row2_height, SWP_NOZORDER);
	static_max_histogram->SetWindowPos(NULL, col_width*3, row1_height, col_width, row2_height, SWP_NOZORDER);
	static_min->SetWindowPos(NULL, 0 , row1_height+row2_height, col_width, row4_height, SWP_NOZORDER);
	static_max->SetWindowPos(NULL, 0 , row1_height+row2_height+row3_height, col_width, row4_height, SWP_NOZORDER);
	edit_min->SetWindowPos(NULL, col_width, row1_height + row2_height, col_width - margin, row4_height, SWP_NOZORDER);
	edit_max->SetWindowPos(NULL, col_width, row1_height + row2_height + row3_height, col_width - margin, row4_height, SWP_NOZORDER);
	btn_apply->SetWindowPos(NULL, col_width * 2 + 5, row1_height + row2_height + 5, col_width - margin, row4_height * 2 - margin, SWP_NOZORDER);
	btn_stretch->SetWindowPos(NULL, col_width * 3 + 5, row1_height + row2_height + 5, col_width - margin, row4_height * 2 - margin, SWP_NOZORDER);
	UpdateWindow();  // 화면 갱신
}

void HistogramDisplayDlg::OnBnClickedButtonApply()
{
	
	int min = 0;
	int max = 255;
	CString str_min, str_max;
	m_minhistogram.GetWindowText(str_min);
	m_maxhistogram.GetWindowText(str_max);
	min = _ttoi(str_min);
	max = _ttoi(str_max);
	if (CheckEditRange(min, max, m_is16bit) == false)
		return;
	auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
	auto* displayDlg = pParentDialog->GetImageDisplayDlg();
	ImageProcessing cv;
	Mat mat, mat2;
	cv.Threshold(displayDlg->GetImage(), mat, min, max);
	cv.Normalize(mat, mat2, 0, 255);
	displayDlg->UpdateImage(mat2);
}

void HistogramDisplayDlg::OnBnClickedButtonStretch()
{
	int min = 0;
	int max = 255;
	CString str_min, str_max;
	m_minhistogram.GetWindowText(str_min);
	m_maxhistogram.GetWindowText(str_max);
	min = _ttoi(str_min);
	max = _ttoi(str_max);

	if (CheckEditRange(min, max, m_is16bit) == false)
		return;

	auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
	auto* displayDlg = pParentDialog->GetImageDisplayDlg();
	ImageProcessing cv;
	Mat mat;
	cv.Normalize(displayDlg->GetImage(), mat, min, max);
	displayDlg->UpdateImage(mat);

	CRect rect;
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC_HISTOGRAM);
	CDC* pDC = pStatic->GetDC();
	if (!pDC) {
		return;
	}
	pStatic->GetClientRect(&rect);
	int barHeight = rect.Height();
	int barWidth = 1;
	int x_offset = rect.Width() / 2 - 128;// 히스토그램을 컨트롤 중앙에 표시하기 위한 옵셋
	CRect barRectmin(min * barWidth + x_offset, rect.Height() - barHeight, (min + 1) * barWidth + x_offset, rect.Height());
	CRect barRectmax(max * barWidth + x_offset, rect.Height() - barHeight, (max + 1) * barWidth + x_offset, rect.Height());
	pDC->FillSolidRect(&barRectmin, RGB(255, 0, 0));
	pDC->FillSolidRect(&barRectmax, RGB(255, 0, 0));
}

void HistogramDisplayDlg::DrawHistogram(Mat& in_img) {
	std::vector<uint16_t>& histogramData = in_img.getData();
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC_HISTOGRAM);
	CDC* pDC = pStatic->GetDC();
	if (!pDC) {
		return;
	}

	CRect rect;
	pStatic->GetClientRect(&rect);
	pDC->FillSolidRect(&rect, RGB(255, 255, 255));

	int min = in_img.GetMinValue();
	int max = in_img.GetMaxValue();
	std::vector<int> histogram(256, 0); //결국 화면에 그릴 히스토그램은 0~255의 범위를 갖음
	if (in_img.GetbitDepth() == 8) {
		for (const auto& pixel : histogramData) {
			histogram[pixel]++;
		}
		m_is16bit = false;
	}
	else {
		for (const auto& pixel : histogramData) {
			int scaled_value = in_img.LinearScale_U16toU8(pixel, min, max);
			histogram[scaled_value]++;
		}
		m_is16bit = true;
	}
	
	CWnd* static_min_histogram = GetDlgItem(IDC_STATIC_MIN_HIST);
	CWnd* static_max_histogram = GetDlgItem(IDC_STATIC_MAX_HIST);
	CString minText, maxText;
	m_n_minhistogram = min;
	m_n_maxhistogram = max;
	minText.Format(L"%d", min);
	maxText.Format(L"%d", max);
	static_min_histogram->SetWindowTextW(minText);
	static_max_histogram->SetWindowTextW(maxText);
	GetDlgItem(IDC_EDIT_MIN)->SetWindowText(minText);
	GetDlgItem(IDC_EDIT_MAX)->SetWindowText(maxText);

	// 히스토그램 막대 너비는 그냥 1, 최대 높이는 계산
	std::vector<int> sortedHistogram = histogram; // 히스토그램의 복사본 생성
	std::sort(sortedHistogram.begin(), sortedHistogram.end()); 
	int maxVal = sortedHistogram[sortedHistogram.size()-1];
	int third_maxVal = sortedHistogram[sortedHistogram.size() - 3];
	if (third_maxVal == 0) third_maxVal = 1;
	int ratio = maxVal / third_maxVal;
	if (ratio > 2) {
		maxVal = maxVal / ratio;
	}


	//int maxVal = *std::max_element(histogram.begin(), histogram.end());
	//maxVal -= 1000;
	int barWidth = 1;
	int x_offset = rect.Width() / 2 - 128;// 히스토그램을 컨트롤 중앙에 표시하기 위한 옵셋
	for (int i = 0; i < 256; ++i) {
		int barHeight = static_cast<int>((static_cast<double>(histogram[i]) / maxVal) * rect.Height());
		if (barHeight > rect.Height()) barHeight = rect.Height();
		CRect barRect(i * barWidth + x_offset, rect.Height() - barHeight, (i + 1) * barWidth + x_offset, rect.Height());
		pDC->FillSolidRect(&barRect, RGB(0, 0, 255));
	}
	pStatic->ReleaseDC(pDC);
}



bool HistogramDisplayDlg::CheckEditRange(int mininput, int maxinput, bool is16bit) {
	if (!is16bit) {
		if (mininput < 0 || mininput > 255 ||
			maxinput < 0 || maxinput > 255)
		{
			CString message;
			message.Format(L"입력 범위 = 0 ~ 255");
			AfxMessageBox(message);
			return false;
		}
	}
	else {
		if (mininput < 0 || mininput > 65535 ||
			maxinput < 0 || maxinput > 65535)
		{
			CString message;
			message.Format(L"입력 범위 = 0 ~ 65535");
			AfxMessageBox(message);
			return false;
		}
	}
	
	return true;
}

int HistogramDisplayDlg::MaxHistBarHeight(int threshold_min, int threshold_max, std::vector<int> histogram) {
	int maxheight = 0;
	for (int i = threshold_min; i <= threshold_max; ++i) {
		int value = histogram[i];

		if (value > maxheight) {
			maxheight = value;
		}
	}
	return maxheight;
}