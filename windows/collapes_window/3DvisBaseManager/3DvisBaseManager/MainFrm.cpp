// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "3DvisBaseManager.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC)/* ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME)*/)
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	// TODO: �������Ҫ��ͣ������������ɾ��������
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);
	ShowWindow(SW_HIDE);
	SetWindowPos(&CWnd::wndTop,0,0,1024,768-30,SWP_NOZORDER|SWP_NOMOVE);
	CenterWindow();
	ShowWindow(SW_SHOW);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;
	
	cs.hMenu = NULL;
	return TRUE;
}


// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame ��Ϣ�������




BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���

	if(!m_wndHead.CreateStatic(this,2,1))
		return FALSE;
	
	int nheight = 70;
	CRect rect;
	
	GetClientRect(&rect);
	m_wndHead.CreateView(0,0,RUNTIME_CLASS(CHeadView),CSize(rect.right,nheight),pContext);

	m_wndBody.CreateStatic(&m_wndHead,1,2,WS_CHILD|WS_VISIBLE,m_wndHead.IdFromRowCol(1,0));
	
	m_wndBody.CreateView(0,0,RUNTIME_CLASS(CLeftView),CSize(200,rect.bottom-nheight),pContext);
	m_wndBody.CreateView(0,1,RUNTIME_CLASS(CRightView),CSize(rect.right-200,rect.bottom-nheight),pContext);

	m_wndHead.SetActivePane(0,0);
	ShowWindow(SW_SHOW);

	

	return CFrameWnd::OnCreateClient(lpcs, pContext);
}
