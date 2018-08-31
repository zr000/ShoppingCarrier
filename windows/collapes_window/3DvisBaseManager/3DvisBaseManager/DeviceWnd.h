#pragma once
//#include "CollapesWnd.h"
#include "BaseInner.h"

// CDeviceWnd

class CDeviceWnd : public CWnd,CBaseInner
{
	DECLARE_DYNAMIC(CDeviceWnd)

public:
	CDeviceWnd();
	virtual ~CDeviceWnd();
	//CCollapesWnd m_cwnd;
protected:
	CBaseInner CBaseInner;
	CIconList m_listIcon;

	BOOL InitSource();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	virtual CWnd* GetCWnd(){return this;}
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNcDestroy();
	afx_msg void OnClose();
};


