
// Calculator.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include <iostream>
#include <vector>

class CCalculatorApp : public CWinApp
{
public:
	CCalculatorApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	static std::vector<CString> calculator_memory;
	DECLARE_MESSAGE_MAP()
};

extern CCalculatorApp theApp;