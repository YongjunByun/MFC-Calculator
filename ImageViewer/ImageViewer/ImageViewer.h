#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


class CImageViewerApp : public CWinApp
{
public:
	CImageViewerApp();
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CImageViewerApp theApp;