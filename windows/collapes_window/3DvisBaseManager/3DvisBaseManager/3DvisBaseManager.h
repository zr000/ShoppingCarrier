// 3DvisBaseManager.h : 3DvisBaseManager Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy3DvisBaseManagerApp:
// �йش����ʵ�֣������ 3DvisBaseManager.cpp
//

class CMy3DvisBaseManagerApp : public CWinApp
{
public:
	CMy3DvisBaseManagerApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CMy3DvisBaseManagerApp theApp;