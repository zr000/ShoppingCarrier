// CollapesWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "3DvisBaseManager.h"
#include "CollapesWnd.h"


// CCollapesWnd
CCollapesWnd::CCollapesWnd()
{

}

CCollapesWnd::~CCollapesWnd()
{
}
BOOL CCollapesWnd::InstallSkin(CWnd *wnd)
{
    //if(!wnd || !m_bInit) return FALSE;
    HookWindow( (HWND)NULL);
    int r = HookWindow( wnd );

    DWORD style = GetWindowLong(m_hWnd, GWL_STYLE);
    //m_sizable = style & WS_SIZEBOX;
   // m_minable = style & WS_MINIMIZEBOX;
    //m_maxable = style & WS_MAXIMIZEBOX;
    //m_sysmenu = style & WS_MAXIMIZEBOX;
    style &= ~(WS_MINIMIZEBOX);
    style &= ~WS_MAXIMIZEBOX;
    style &= ~WS_SYSMENU;
    SetWindowLong( m_hWnd, GWL_STYLE, style );

    return r;
}


LRESULT CCollapesWnd::WindowProc(UINT msg, WPARAM wp, LPARAM lp)
{
    if ( !IsWindow(m_hWnd) )
        return 0;
    /*if ( !m_bInit  ) 
        return Default();*/

	return Default();

    /*switch ( msg )
    {

        return Default();
    }*/
}