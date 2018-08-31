#pragma once

#include "DeviceWnd.h"
#include "SysWnd.h"
#include "History.h"

#include "CollapesHolder.h"
#include "helpwnd.h"
#include "AlarmWnd.h"
#include "BaseLine.h"


// CLeftView 视图

class CLeftView : public CView
{
	DECLARE_DYNCREATE(CLeftView)

protected:
	CLeftView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLeftView();
	CDeviceWnd* m_devWnd;
	CBaseLine*  m_baseLineWnd;
	CHistory*   m_histortyWnd;
	CSysWnd*     m_sysWnd;
	CAlarmWnd*  m_alarmWnd;
	CHelpWnd*  m_helpWnd;

	CCollapesHolder m_wndContain;
	BOOL m_bShow;

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnWndLButtonDown(WPARAM,LPARAM);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	afx_msg void OnDestroy();
};


