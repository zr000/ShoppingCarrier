#pragma once

#include "BaseInner.h"

// CSysWnd

class CSysWnd : public CWnd,CBaseInner
{
	DECLARE_DYNAMIC(CSysWnd)

public:
	CSysWnd();
	virtual ~CSysWnd();
	
protected:
	DECLARE_MESSAGE_MAP()
	CBaseInner CBaseInner;
	CIconList m_listIcon;
	BOOL InitSource();
public:
	afx_msg void OnPaint();
	
	virtual CWnd* GetCWnd(){return this;}
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNcDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


