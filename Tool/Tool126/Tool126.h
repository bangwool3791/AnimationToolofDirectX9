
// Tool126.h : Tool126 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CTool126App:
// �� Ŭ������ ������ ���ؼ��� Tool126.cpp�� �����Ͻʽÿ�.
//

class CTool126App : public CWinAppEx
{
public:
	CTool126App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTool126App theApp;
