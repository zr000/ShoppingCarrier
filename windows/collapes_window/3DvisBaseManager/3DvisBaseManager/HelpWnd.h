#pragma once

#include "BaseInner.h"
// CHelpWnd

class CHelpWnd : public CWnd
{
	DECLARE_DYNAMIC(CHelpWnd)

public:
	CHelpWnd();
	virtual ~CHelpWnd();

protected:
	DECLARE_MESSAGE_MAP()
	CBaseInner CBaseInner;
public:
	afx_msg void OnPaint();
	afx_msg void OnNcDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


