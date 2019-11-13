#include "StdAfx.h"
#include "IconList.h"

CIconList::CIconList(void):
m_bInit(FALSE)
{
}

CIconList::~CIconList(void)
{
}


BOOL CIconList::AddIcon(int id, CRect rect, wstring text)
{
	m_bInit = TRUE;
	__ICONINFO info;
	HANDLE htemp;
	htemp = ::LoadImage(::AfxGetApp()->m_hInstance,MAKEINTRESOURCE(id),IMAGE_ICON,0,0,LR_SHARED);

	if(htemp == NULL)
		return FALSE;

	info.icon = (HICON)htemp;
	info.rect = rect;
	info.text.assign(text);

	m_listIcon.push_back(info);

	return TRUE;
}
BOOL CIconList::AddIcon(LPCTSTR path)
{
	return FALSE;
}
void CIconList::DrawIcon(HDC hdc)
{
	LISTICON::iterator it = m_listIcon.begin();
	CRect textRect(0,0,0,0);

	FontFamily  fontFamily(L"Á¥Êé"); 
	Font        font(&fontFamily, 25, FontStyleRegular, UnitPixel); 
	PointF      pointF(30.0f, 10.0f); 
	SolidBrush  solidBrush(Color(255, 255, 255, 255)); 
	RectF       rectF;
	Graphics gra(hdc);

	while(it!=m_listIcon.end())
	{
		::DrawIconEx(hdc, it->rect.left, it->rect.top, it->icon, 
						it->rect.Width(),it->rect.Height(),0, NULL, DI_NORMAL);
		if(it->text.length()!=0)
		{
			//::SetTextColor(hdc, RGB(255,255,255));
			::DrawText(hdc, it->text.c_str(),-1,textRect,DT_LEFT|DT_CALCRECT);
			//textRect.MoveToXY(it->rect.left+(it->rect.Width()-textRect.Width())/2,it->rect.bottom+2);
			//::DrawText(hdc, it->text.c_str(),-1,textRect,DT_LEFT);
			pointF.X = it->rect.left+(it->rect.Width()-textRect.Width())/2-15;
			pointF.Y = it->rect.bottom+2;
			gra.MeasureString(it->text.c_str(), -1, &font, pointF, &rectF);
			//gra.DrawString(it->text.c_str(), -1, &font, pointF, &solidBrush); 
			gra.DrawString(it->text.c_str(), -1, &font, rectF, NULL, &solidBrush);
		}
		it++;
	}
}