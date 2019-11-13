#pragma once

#include "BaseInner.h"
// CBaseLine

class CBaseLine : public CWnd
{
	DECLARE_DYNAMIC(CBaseLine)

public:
	CBaseLine();
	virtual ~CBaseLine();

protected:
	DECLARE_MESSAGE_MAP()
	CBaseInner CBaseInner;
public:
	afx_msg void OnNcDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


