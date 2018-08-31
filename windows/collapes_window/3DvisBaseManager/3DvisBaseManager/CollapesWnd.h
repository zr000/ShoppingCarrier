#pragma once
#include "Subclass.h"

// CCollapesWnd

class CCollapesWnd : public CSubclassWnd
{
public:
	CCollapesWnd();
	virtual ~CCollapesWnd();

	BOOL InstallSkin(CWnd *wnd);
public:
	virtual LRESULT WindowProc(UINT msg, WPARAM wp, LPARAM lp);
};


