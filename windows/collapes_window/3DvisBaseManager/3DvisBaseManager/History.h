#pragma once
#include "BaseInner.h"

// CHistory

class CHistory : public CWnd
{
	DECLARE_DYNAMIC(CHistory)

public:
	CHistory();
	virtual ~CHistory();

protected:
	DECLARE_MESSAGE_MAP()
	CBaseInner CBaseInner;
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNcDestroy();
};


