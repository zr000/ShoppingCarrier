// 3DvisBaseManagerView.cpp : CMy3DvisBaseManagerView 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy3DvisBaseManagerView 构造/析构

CMy3DvisBaseManagerView::CMy3DvisBaseManagerView()
{
	// TODO: 在此处添加构造代码

}

CMy3DvisBaseManagerView::~CMy3DvisBaseManagerView()
{
}

BOOL CMy3DvisBaseManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	
	return CView::PreCreateWindow(cs);
}

// CMy3DvisBaseManagerView 绘制

void CMy3DvisBaseManagerView::OnDraw(CDC* pDC)
{
	ShowWindow(SW_HIDE);
	CMy3DvisBaseManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
}


// CMy3DvisBaseManagerView 打印

BOOL CMy3DvisBaseManagerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy3DvisBaseManagerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy3DvisBaseManagerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMy3DvisBaseManagerView 诊断

#ifdef _DEBUG
void CMy3DvisBaseManagerView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3DvisBaseManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3DvisBaseManagerDoc* CMy3DvisBaseManagerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DvisBaseManagerDoc)));
	return (CMy3DvisBaseManagerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy3DvisBaseManagerView 消息处理程序
