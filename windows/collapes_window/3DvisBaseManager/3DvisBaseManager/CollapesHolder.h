#pragma once
#include "BaseInner.h"
#include <list>
#include <map>
struct STATUS
{
	int id;
	int pos;
	BOOL isActive;
	BOOL isAnimation;
	CRect currrect;
	CRect desRect;
	CWnd* wnd;
	int speed;
};

//typedef map<int,STATUS> MAPSTATUS;
//typedef map<int,CWnd*> MAPWND;

typedef list<STATUS>   LISTWND;

//#define LISTWND list<CWnd*>
#define SPEED 84
class CCollapesHolder
{
public:
	CCollapesHolder(void);
	virtual ~CCollapesHolder(void);

	int AddCollapesWnd(CWnd* wnd,CWnd* pParent);
	CWnd* FindWndByID(int);
	CWnd* GetActiveWnd();
	int GetActiveWndID();
	bool SetActiveWnd(int,BOOL bAnimation = FALSE);

	void SetCollapesRect(CRect rect);
	void OnLButtonDown(CWnd*);
protected:
	const int m_nHeadHeight;
	CRect m_rectCollapes;
	CRect m_rectActiveWndRect;
	const int m_nMaxWndNum;
	const int m_nBaseID;
	int m_nWndNum;	
	int m_nActiveWnd;
	int m_nWidth;
	int m_nHeigth;
	BOOL m_bShow;
	//MAPWND m_mapWnd;
	//MAPSTATUS m_mapStatus;
	LISTWND m_listWnd;
	void CalcWndRect();
	void Expand(int id,BOOL bSelect = TRUE,BOOL bAnimation = FALSE);
	int GetPosByWnd(CWnd*);
	void SetActiveWndID(int id,BOOL Active = TRUE);
	void InitWndRect();
	static DWORD WINAPI ThreadAnimation(PVOID pParam);
	HANDLE m_hThread;
	HANDLE m_hEvent[2];
	
};
