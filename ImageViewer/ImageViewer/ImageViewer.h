
// ImageViewer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CImageViewerApp:
// �� Ŭ������ ������ ���ؼ��� ImageViewer.cpp�� �����Ͻʽÿ�.
//

class CImageViewerApp : public CWinApp
{
public:
	CImageViewerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CImageViewerApp theApp;