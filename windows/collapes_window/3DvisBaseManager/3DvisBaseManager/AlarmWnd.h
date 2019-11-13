#pragma once

#include "BaseInner.h"
// CAlarmWnd

class CAlarmWnd : public CWnd
{
	DECLARE_DYNAMIC(CAlarmWnd)

public:
	CAlarmWnd();
	virtual ~CAlarmWnd();
	
protected:
	DECLARE_MESSAGE_MAP()


	CBaseInner CBaseInner;
public:
	afx_msg void OnNcDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


