// 3DvisBaseManagerView.cpp : CMy3DvisBaseManagerView ���ʵ��
//

#include "stdafx.h"
#include "3DvisBaseManager.h"

#include "3DvisBaseManagerDoc.h"
#include "3DvisBaseManagerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy3DvisBaseManagerView

IMPLEMENT_DYNCREATE(CMy3DvisBaseManagerView, CView)

BEGIN_MESSAGE_MAP(CMy3DvisBaseManagerView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy3DvisBaseManagerView ����/����

CMy3DvisBaseManagerView::CMy3DvisBaseManagerView()
{
	// TODO: �ڴ˴���ӹ������

}

CMy3DvisBaseManagerView::~CMy3DvisBaseManagerView()
{
}

BOOL CMy3DvisBaseManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	
	return CView::PreCreateWindow(cs);
}

// CMy3DvisBaseManagerView ����

void CMy3DvisBaseManagerView::OnDraw(CDC* pDC)
{
	ShowWindow(SW_HIDE);
	CMy3DvisBaseManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMy3DvisBaseManagerView ��ӡ

BOOL CMy3DvisBaseManagerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy3DvisBaseManagerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy3DvisBaseManagerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMy3DvisBaseManagerView ���

#ifdef _DEBUG
void CMy3DvisBaseManagerView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3DvisBaseManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3DvisBaseManagerDoc* CMy3DvisBaseManagerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DvisBaseManagerDoc)));
	return (CMy3DvisBaseManagerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy3DvisBaseManagerView ��Ϣ�������
