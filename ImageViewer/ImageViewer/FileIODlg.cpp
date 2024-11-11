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


// FileIODlg �޽��� ó�����Դϴ�.


void FileIODlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (m_isInitialized == false)
		return;
	ResizeControls();
	
}
void FileIODlg::ResizeControls() {
	CRect clientRect;
	GetClientRect(&clientRect);
	int row1Height = (int)(clientRect.Height() / 10 * 1); // 1�� 10%
	int row2Height = (int)(clientRect.Height() / 10 * 1); // 1�� 10%
	int row3Height = (int)(clientRect.Height() / 10 * 8); // 1�� 80%
	CWnd* pButtonSave = GetDlgItem(IDC_BUTTON_LOAD);
	CWnd* pButtonLoad = GetDlgItem(IDC_BUTTON_SAVE);
	CWnd* pListFile = GetDlgItem(IDC_LIST_FILE);
	pButtonSave->SetWindowPos(nullptr, 30, 0, clientRect.Width() - 60, row1Height, SWP_NOZORDER);
	pButtonLoad->SetWindowPos(nullptr, 30, row1Height, clientRect.Width() - 60, row2Height, SWP_NOZORDER);
	pListFile->SetWindowPos(nullptr, 30, row1Height + row2Height, clientRect.Width() - 60, row3Height, SWP_NOZORDER);
}

void FileIODlg::OnBnClickedButtonLoad()
{
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT,
		_T("BMP and RAW Files (*.bmp;*.raw)|*.bmp;*.raw|BMP Files (*.bmp)|*.bmp|RAW Files (*.raw)|*.raw||"),
		this);

	if (fileDlg.DoModal() == IDOK)
	{
		m_List_File.ResetContent();  // ���� ��� �ʱ�ȭ
		m_file_paths.clear();

		POSITION pos = fileDlg.GetStartPosition();
		while (pos != NULL)
		{
			CString filePath = fileDlg.GetNextPathName(pos); 
			m_file_paths.push_back(filePath);
			// ȭ�鿡 ���� ��θ��� ����η�
			int pos = filePath.ReverseFind(_T('\\')); 
			if (pos != -1)
			{
				filePath = filePath.Mid(pos + 1); 
			}
			m_List_File.AddString(filePath); 
			Mat mat(m_file_paths[0]);
			auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
			auto* displayDlg = pParentDialog->GetImageDisplayDlg();
			if (displayDlg != nullptr)
			{
				displayDlg->UpdateImage(mat); // UpdateImage �Լ� ȣ��
			}
		}
	}

}


void FileIODlg::OnBnClickedButtonSave()
{
	CString path = L"C:\\Users\\user\\Desktop";
	auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
	auto* displayDlg = pParentDialog->GetImageDisplayDlg();
	if (displayDlg != nullptr)
	{
		displayDlg->UpdateImage(mat); // UpdateImage �Լ� ȣ��
	}
}


BOOL FileIODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_isInitialized = true;
	return TRUE; 
}


void FileIODlg::OnLbnDblclkListFile()
{
	CPoint pt;
	GetCursorPos(&pt);
	m_List_File.ScreenToClient(&pt);
	// ���콺 ��ġ���� ������ �ε����� �����´�
	BOOL bOutside = FALSE;
	int nIndex = m_List_File.ItemFromPoint(pt, bOutside);
	if (nIndex != LB_ERR && bOutside == FALSE)
	{
		Mat mat(m_file_paths[nIndex]);
		auto* pParentDialog = dynamic_cast<CImageViewerDlg*>(GetParent());
		auto* displayDlg = pParentDialog->GetImageDisplayDlg();
		if (displayDlg != nullptr)
		{
			displayDlg->UpdateImage(mat); // UpdateImage �Լ� ȣ��
		}
	}
}
