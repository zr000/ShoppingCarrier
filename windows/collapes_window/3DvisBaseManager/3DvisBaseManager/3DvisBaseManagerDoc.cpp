// 3DvisBaseManagerDoc.cpp : CMy3DvisBaseManagerDoc ���ʵ��
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


// CMy3DvisBaseManagerDoc ����/����

CMy3DvisBaseManagerDoc::CMy3DvisBaseManagerDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CMy3DvisBaseManagerDoc::~CMy3DvisBaseManagerDoc()
{
}

BOOL CMy3DvisBaseManagerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMy3DvisBaseManagerDoc ���л�

void CMy3DvisBaseManagerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CMy3DvisBaseManagerDoc ���

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


// CMy3DvisBaseManagerDoc ����
