#include "stdafx.h"
#include "ImageViewer.h"
#include "FileIODlg.h"
#include "afxdialogex.h"
#include "ImageViewerDlg.h"
#include "ImageDisplayDlg.h"

IMPLEMENT_DYNAMIC(FileIODlg, CDialogEx)

FileIODlg::FileIODlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FILE_IO_VIEW, pParent)
{
}

FileIODlg::~FileIODlg()
{
}

void FileIODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON_LOAD, m_Button_Load);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_Button_Save);
	DDX_Control(pDX, IDC_LIST_FILE, m_List_File);
}


BEGIN_MESSAGE_MAP(FileIODlg, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &FileIODlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &FileIODlg::OnBnClickedButtonSave)
	ON_LBN_DBLCLK(IDC_LIST_FILE, &FileIODlg::OnLbnDblclkListFile)
END_MESSAGE_MAP()


// FileIODlg 메시지 처리기입니다.


void FileIODlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (m_isInitialized == false)
		return;
	ResizeControls();
	GetDlgItem(IDC_LIST_FILE)->Invalidate(FALSE); 
}

void FileIODlg::OnBnClickedButtonLoad()
{
	try {
		CFileDialog fileDlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT,
			_T("BMP and RAW Files (*.bmp;*.raw)|*.bmp;*.raw|BMP Files (*.bmp)|*.bmp|RAW Files (*.raw)|*.raw||"),
			this);
		
		const DWORD bufferSize = 1024 * 1024; 
		fileDlg.GetOFN().lpstrFile = new TCHAR[bufferSize];
		ZeroMemory(fileDlg.GetOFN().lpstrFile, bufferSize);
		fileDlg.GetOFN().nMaxFile = bufferSize;

		if (fileDlg.DoModal() == IDOK)
		{
			m_List_File.ResetContent();  // 기존 목록 초기화
			m_file_paths.clear();

			POSITION pos = fileDlg.GetStartPosition();
			while (pos != NULL)
			{
				CString filePath = fileDlg.GetNextPathName(pos);
				m_file_paths.push_back(filePath);
				// 화면에 보일 경로명은 상대경로로
				int pos = filePath.ReverseFind(_T('\\'));
				if (pos != -1)
				{
					filePath = filePath.Mid(pos + 1);
				}
				m_List_File.AddString(filePath);
		
			}
			Mat mat(m_file_paths[0]);
			auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
			auto* displayDlg = pParentDialog->GetImageDisplayDlg();
			if (displayDlg != nullptr)
			{
				displayDlg->UpdateImage(mat);
			}
		}
		delete[] fileDlg.GetOFN().lpstrFile;
	}
	catch (std::exception e) {
		AfxMessageBox(CString(e.what()));
	}

}

void FileIODlg::OnBnClickedButtonSave()
{
	auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
	auto* displayDlg = pParentDialog->GetImageDisplayDlg();
	if (displayDlg == nullptr)
		return;
	
	Mat src = displayDlg->GetImage();
	if (src.isEmpty()) {
		AfxMessageBox(L"이미지를 먼저 불러오세요");
		return;
	}
	CString filter = L"Bitmap Files (*.bmp)|*.bmp|RAW Files (*.raw)|*.raw||";
	CString fileName;
	fileName.Format(L"ImageSaved_%dx%d", src.GetWidth(), src.GetHeight());
	CFileDialog fileDlg(FALSE, NULL, fileName, OFN_OVERWRITEPROMPT, filter, this);

	if (fileDlg.DoModal() == IDOK) {
		CString path = fileDlg.GetPathName();
		CString selectedExt;
		int fileTypeIndex = fileDlg.GetOFN().nFilterIndex;

		if (fileTypeIndex == 1) {
			selectedExt = L".bmp";
		}
		else if (fileTypeIndex == 2) {
			selectedExt = L".raw";
		}

		if (path.Right(selectedExt.GetLength()).CompareNoCase(selectedExt) != 0) {
			path += selectedExt;
		}

		try {
			src.ImgSave(path, src);
		}
		catch (std::exception& e) {
			AfxMessageBox(CString(e.what()));
		}
	}
}


void FileIODlg::OnLbnDblclkListFile()
{
	try {
		CPoint pt;
		GetCursorPos(&pt);
		m_List_File.ScreenToClient(&pt);
		// 마우스 위치에서 아이템 인덱스를 가져온다
		BOOL bOutside = FALSE;
		int nIndex = m_List_File.ItemFromPoint(pt, bOutside);
		if (nIndex != LB_ERR && bOutside == FALSE)
		{
			Mat mat(m_file_paths[nIndex]);
			auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
			auto* displayDlg = pParentDialog->GetImageDisplayDlg();
			if (displayDlg != nullptr)
			{
				displayDlg->UpdateImage(mat);
			}
		}
	}
	catch (std::exception e) {
		AfxMessageBox(CString(e.what()));
	}
}

BOOL FileIODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ModifyStyle(0, WS_CLIPCHILDREN);
	m_isInitialized = true;
	return TRUE;
}

void FileIODlg::ResizeControls() {
	CRect clientRect;
	GetClientRect(&clientRect);
	int row1Height = (int)(clientRect.Height() / 10 * 1); // 1행 10%
	int row2Height = (int)(clientRect.Height() / 10 * 1); // 1행 10%
	int row3Height = (int)(clientRect.Height() / 10 * 8); // 1행 80%
	CWnd* pButtonSave = GetDlgItem(IDC_BUTTON_LOAD);
	CWnd* pButtonLoad = GetDlgItem(IDC_BUTTON_SAVE);
	CWnd* pListFile = GetDlgItem(IDC_LIST_FILE);
	pButtonSave->SetWindowPos(nullptr, 30, 0, clientRect.Width() - 60, row1Height, SWP_NOZORDER);
	pButtonLoad->SetWindowPos(nullptr, 30, row1Height, clientRect.Width() - 60, row2Height, SWP_NOZORDER);
	pListFile->SetWindowPos(nullptr, 30, row1Height + row2Height, clientRect.Width() - 60, row3Height, SWP_NOZORDER);

	/*HDWP hdwp = ::BeginDeferWindowPos(3);
	::DeferWindowPos(hdwp, pButtonSave->GetSafeHwnd(), HWND_TOP, 30, 0, clientRect.Width() - 60, row1Height, SWP_NOZORDER);
	::DeferWindowPos(hdwp, pButtonLoad->GetSafeHwnd(), HWND_TOP, 30, row1Height, clientRect.Width() - 60, row2Height, SWP_NOZORDER);
	::DeferWindowPos(hdwp, pListFile->GetSafeHwnd(), HWND_TOP, 30, row1Height + row2Height, clientRect.Width() - 60, row3Height, SWP_NOZORDER);
	::EndDeferWindowPos(hdwp);*/
}