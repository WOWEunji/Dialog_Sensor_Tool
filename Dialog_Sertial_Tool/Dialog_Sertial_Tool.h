
// Dialog_Sertial_Tool.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CDialog_Sertial_ToolApp:
// �� Ŭ������ ������ ���ؼ��� Dialog_Sertial_Tool.cpp�� �����Ͻʽÿ�.
//

class CDialog_Sertial_ToolApp : public CWinApp
{
public:
	CDialog_Sertial_ToolApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CDialog_Sertial_ToolApp theApp;