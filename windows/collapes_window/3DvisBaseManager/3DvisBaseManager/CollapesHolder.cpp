#include "StdAfx.h"
#include "CollapesHolder.h"

CCollapesHolder::CCollapesHolder(void):
m_nWndNum(0)
,m_nActiveWnd(-1)
,m_nWidth(0)
,m_nHeigth(0)
,m_nBaseID(1000)
,m_nMaxWndNum(10)
,m_nHeadHeight(HEADHEIGHT)
,m_bShow(FALSE)
{
	//m_nActiveWnd = m_nBaseID;
	CRect rect(0,0,0,0);
	m_rectCollapes = m_rectActiveWndRect = rect;
	m_hEvent[1] = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hEvent[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hThread = CreateThread(NULL, 0, ThreadAnimation, this, 0, 0);
	
}
DWORD CCollapesHolder::ThreadAnimation(PVOID pParam)
{
	CCollapesHolder* pThis = (CCollapesHolder*)pParam;
	DWORD dwRet = WAIT_OBJECT_0 + 1;
	while(dwRet == WAIT_OBJECT_0 + 1)
	{
		dwRet = ::WaitForMultipleObjects(2,pThis->m_hEvent,FALSE,INFINITE);

		
		if(dwRet == WAIT_OBJECT_0 + 1)
		{
			Sleep(30);
			BOOL bOver = TRUE;
			LISTWND::iterator it = pThis->m_listWnd.begin();
			int nspace = 0;
			
			while(it!=pThis->m_listWnd.end())
			{
				DWORD dwtype = SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER;
				nspace = it->desRect.top - it->currrect.top;
				
				if(nspace != 0)											//上下
				{
					if(abs(nspace) > it->speed)
					{
						bOver = FALSE;
						it->currrect.top += it->speed*(nspace > 0?1:-1);
						
						dwtype &= ~SWP_NOMOVE;
						
					}
					else
					{
						dwtype &= ~SWP_NOMOVE;
						dwtype &= ~SWP_NOSIZE;
						it->currrect.top = it->desRect.top;
					}
				}
				
				nspace = it->desRect.bottom - it->currrect.bottom;
				if(nspace !=0)											//大小			
				{
					if(abs(nspace) > it->speed)
					{
						dwtype &= ~SWP_NOSIZE;
						bOver = FALSE;
						it->currrect.bottom += it->speed*(nspace > 0?1:-1);
						
					}
					else
					{
						dwtype &= ~SWP_NOMOVE;
						dwtype &= ~SWP_NOSIZE;
						it->currrect.bottom = it->desRect.bottom;
					}
				}

				HDWP hwndp = BeginDeferWindowPos(1);
				HDWP hwndp1 = DeferWindowPos(hwndp, it->wnd->m_hWnd, HWND_TOP,it->currrect.left,it->currrect.top,
								it->currrect.Width(),it->currrect.Height(),SWP_NOZORDER);
				EndDeferWindowPos(hwndp);
				/*it->wnd->SetWindowPos(&CWnd::wndTop,it->currrect.left,it->currrect.top,
										it->currrect.Width(),it->currrect.Height(),dwtype);*/
	
				it++;
			}
			if(bOver)
			{
				it = pThis->m_listWnd.begin();
				while(it!=pThis->m_listWnd.end())
				{
					//it->wnd->SetWindowPos(&CWnd::wndTop,it->currrect.left,it->currrect.top,
					//	it->currrect.Width(),it->currrect.Height(),SWP_NOZORDER);
					//it->wnd->Invalidate(0);
					it->wnd->UpdateWindow();
					it++;
				}
				ResetEvent(pThis->m_hEvent[1]);
			}

			
		}

		
	}
	return 0;
}
CCollapesHolder::~CCollapesHolder(void)
{
	SetEvent(m_hEvent[0]);
	::WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hEvent[1]);
	CloseHandle(m_hEvent[0]);
	CloseHandle(m_hThread);
	
}
int CCollapesHolder::AddCollapesWnd(CWnd* wnd,CWnd* pParent)
{
	int nID = m_nBaseID + m_nWndNum;

	if(m_nWndNum>m_nMaxWndNum)
	{
		delete wnd;
		return -1;
	}

	if(!wnd->Create(NULL,L"",WS_CHILD|WS_VISIBLE,CRect(1,1,1,1),pParent,nID))
		return -1;

	ASSERT(::IsWindow(wnd->m_hWnd));

	STATUS status = {0};
	status.id = nID;
	status.isActive = FALSE;
	status.wnd = wnd;
	status.pos = nID - m_nBaseID;
	status.speed = SPEED;

	m_listWnd.push_back(status);

	//m_mapWnd[nID] = wnd;
	//m_mapStatus[nID] = status;

	m_nWndNum++;

	//计算大小
	CalcWndRect();

	//显示添加的窗口
	wnd->SetWindowPos(&CWnd::wndTop,0,(m_nWndNum-1)*m_nHeadHeight,m_rectCollapes.Width(),m_nHeadHeight,SWP_NOZORDER|SWP_SHOWWINDOW);

	return nID;
}
CWnd* CCollapesHolder::FindWndByID(int id)
{
	LISTWND::iterator it = m_listWnd.begin();
	while(it!=m_listWnd.end())
	{
		if(it->id == id && ::IsWindow(it->wnd->m_hWnd))
			return it->wnd;
		it++;
	}
	return NULL;
}
int CCollapesHolder::GetActiveWndID()
{
	LISTWND::iterator it = m_listWnd.begin();
	while(it!=m_listWnd.end())
	{
		if(it->isActive && ::IsWindow(it->wnd->m_hWnd))
			return it->id;
		it++;
	}
	return -1;
}
void CCollapesHolder::SetActiveWndID(int id,BOOL Active)
{
	LISTWND::iterator it = m_listWnd.begin();
	while(it!=m_listWnd.end())
	{
		if(it->id == id && ::IsWindow(it->wnd->m_hWnd))
		{
			it->isActive = Active;
			return;
		}
		it++;
	}
}
int CCollapesHolder::GetPosByWnd(CWnd* wnd)
{
	if(!::IsWindow(wnd->m_hWnd))
		return -1;

	LISTWND::iterator it = m_listWnd.begin();
	while(it!=m_listWnd.end())
	{
		if(it->wnd == wnd && ::IsWindow(it->wnd->m_hWnd))
		{
			return it->id-m_nBaseID;
		}
		it++;
	}

	return -1;
}
CWnd* CCollapesHolder::GetActiveWnd()
{
	return FindWndByID(m_nActiveWnd);
}

//pos从0开始
bool CCollapesHolder::SetActiveWnd(int pos,BOOL bAnimation)
{
	int selectid = m_nBaseID + pos;
	int nCurrActive = GetActiveWndID();
	if(selectid >= m_nBaseID && selectid < m_nBaseID+m_nWndNum)
	{
		
		if(selectid == nCurrActive)
			return TRUE;
		// 展开动画
		Expand(selectid,1,bAnimation);
		
		if(nCurrActive != -1)
		{
			SetActiveWndID(nCurrActive,FALSE);
		}
		SetActiveWndID(selectid);
	}
	else
		return FALSE;

	return TRUE;
}

void CCollapesHolder::SetCollapesRect(CRect rect)
{
	m_rectCollapes = rect;
	CalcWndRect();
	if(m_bShow)
		Expand(GetActiveWndID(),FALSE);
}
void CCollapesHolder::InitWndRect()
{
	return;
	LISTWND::iterator it = m_listWnd.begin();
	CRect rect;

	while(it!=m_listWnd.end())
	{
		it->wnd->GetClientRect(&rect);

		it->currrect = rect;
		it++;
	}
}
void CCollapesHolder::CalcWndRect()
{
	if(m_nWndNum == 0)
		return;

	int nallhead = (m_nWndNum - 1) * m_nHeadHeight;

	m_rectActiveWndRect.right = m_rectCollapes.Width();
	m_rectActiveWndRect.bottom = m_rectCollapes.Height() - nallhead;

	InitWndRect();
}

void CCollapesHolder::Expand(int id,BOOL bSelect,BOOL bAnimation)
{
	m_bShow = TRUE;
	CWnd* wnd = NULL;
	int nCurrActID = GetActiveWndID();
	int nPos = 0;
	//MAPWND::iterator it = m_mapWnd.begin();
	LISTWND::iterator it = m_listWnd.begin();
	CRect desrect;
	while(it!=m_listWnd.end())
	{
		desrect.SetRect(0,0,0,0);
		nPos = it->pos;
		wnd = it->wnd;
		if(it->id > id)
		{
			desrect.SetRect(0,m_rectCollapes.Height()-(m_nWndNum-nPos)*m_nHeadHeight,
				m_rectCollapes.Width(),m_rectCollapes.Height()-(m_nWndNum-nPos)*m_nHeadHeight+m_nHeadHeight);
		}
		else
		{
			desrect.SetRect(0,nPos*m_nHeadHeight,m_rectCollapes.Width(),nPos*m_nHeadHeight+m_nHeadHeight);

			if(it->id == id)
			{
				desrect.SetRect(0,nPos*m_nHeadHeight,
								m_rectCollapes.Width(),nPos*m_nHeadHeight+m_rectActiveWndRect.Height());
			}
			
		}
		if(it->id == nCurrActID && bSelect)			//关闭窗口
		{
			
			desrect.bottom = desrect.top+m_nHeadHeight;
			
		}
		it->desRect = desrect;
		if(!bAnimation)
		{
			wnd->SetWindowPos(&CWnd::wndTop,desrect.left,desrect.top,desrect.Width(),desrect.Height(),SWP_NOZORDER);
			it->currrect = desrect;
		}
		it++;
	}
	
	if(bAnimation)
	{
		SetEvent(m_hEvent[1]);
	}
}
void CCollapesHolder::OnLButtonDown(CWnd* wnd)
{
	int pos = GetPosByWnd(wnd);
	if(pos!=-1)
	{
		SetActiveWnd(pos,1);
	}

}
