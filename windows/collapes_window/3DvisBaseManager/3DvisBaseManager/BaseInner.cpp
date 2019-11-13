#include "StdAfx.h"
#include "BaseInner.h"

CBaseInner::CBaseInner(void)
{
}

CBaseInner::~CBaseInner(void)
{
}


void CBaseInner::Paint(CPaintDC& dc,CRect& clientRect,CIconList* icon)
{
	CDC memdc;
	CBitmap membmp;
	
	memdc.CreateCompatibleDC(&dc);
	membmp.CreateCompatibleBitmap(&dc,clientRect.Width(),clientRect.Height());
	CBitmap* oldDC = memdc.SelectObject(&membmp);
	Graphics grph(memdc);
	RectF HeadRect(0,0,clientRect.right,HEADHEIGHT);
	CFont font;
    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT));
    lf.lfHeight = 14;
    wcscpy_s(lf.lfFaceName, L"ËÎÌו");
    VERIFY(font.CreateFontIndirect(&lf));
    CFont* oldFont = memdc.SelectObject(&font);
	
	CBrush brush(RGB(31,31,31));
	memdc.FillRect(clientRect,&brush);
	LinearGradientBrush myLinearGradientBrush( 
		HeadRect, 
		Color(255, 255, 255, 255), 
		Color(255, 150,150,150), 
		LinearGradientModeVertical); 
	grph.FillRectangle(&myLinearGradientBrush, HeadRect);  

	memdc.SetBkMode(TRANSPARENT);
	CRect textRect;
	memdc.DrawText(m_strTitle.c_str(),-1,textRect,DT_LEFT|DT_CALCRECT);
	CRect temp((clientRect.Width()-textRect.Width())/2,3,
		(clientRect.Width()-textRect.Width())/2+textRect.Width(),3+textRect.Height());
	memdc.DrawText(m_strTitle.c_str(),-1,temp,DT_LEFT);
	
	if(icon!=NULL)
		icon->DrawIcon(memdc.m_hDC);
	
	dc.BitBlt(0, 0, clientRect.Width(), clientRect.Height(), &memdc, 0, 0, SRCCOPY); 

	memdc.SelectObject(oldFont);
	memdc.SelectObject(oldDC);
}
void CBaseInner::SetWndTitle(LPCTSTR title)
{
	if(title!=NULL)
		m_strTitle.assign(title);
}