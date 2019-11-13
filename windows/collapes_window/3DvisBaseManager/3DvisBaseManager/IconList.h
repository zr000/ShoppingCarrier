#pragma once
struct __ICONINFO
{
	HICON icon;
	CRect rect;
	wstring text;
};
typedef list<__ICONINFO> LISTICON;
class CIconList
{
public:
	CIconList(void);
	~CIconList(void);
	BOOL m_bInit;
	BOOL AddIcon(int id, CRect rect,wstring text = L"");
	BOOL AddIcon(LPCTSTR path);
	void DrawIcon(HDC);
protected:
	LISTICON m_listIcon;

	
};
