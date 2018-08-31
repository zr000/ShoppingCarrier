// 3DvisBaseManagerDoc.cpp : CMy3DvisBaseManagerDoc 类的实现
//

#include "stdafx.h"
#include "3DvisBaseManager.h"

#include "3DvisBaseManagerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy3DvisBaseManagerDoc

IMPLEMENT_DYNCREATE(CMy3DvisBaseManagerDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy3DvisBaseManagerDoc, CDocument)
END_MESSAGE_MAP()


// CMy3DvisBaseManagerDoc 构造/析构

CMy3DvisBaseManagerDoc::CMy3DvisBaseManagerDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMy3DvisBaseManagerDoc::~CMy3DvisBaseManagerDoc()
{
}

BOOL CMy3DvisBaseManagerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMy3DvisBaseManagerDoc 序列化

void CMy3DvisBaseManagerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CMy3DvisBaseManagerDoc 诊断

#ifdef _DEBUG
void CMy3DvisBaseManagerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy3DvisBaseManagerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy3DvisBaseManagerDoc 命令
