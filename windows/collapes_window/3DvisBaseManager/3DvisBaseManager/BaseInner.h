#pragma once
#include "IconList.h"
class CBaseInner
{
public:
	CBaseInner(void);
	virtual ~CBaseInner(void);
	
	void Paint(CPaintDC& dc,CRect& clientRect,CIconList* icon=NULL);
	void SetWndTitle(LPCTSTR title);

protected:
	wstring m_strTitle;
};
