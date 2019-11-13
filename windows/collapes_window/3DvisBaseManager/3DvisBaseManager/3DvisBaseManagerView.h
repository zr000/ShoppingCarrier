// 3DvisBaseManagerView.h : CMy3DvisBaseManagerView 类的接口
//


#pragma once


class CMy3DvisBaseManagerView : public CView
{
protected: // 仅从序列化创建
	CMy3DvisBaseManagerView();
	DECLARE_DYNCREATE(CMy3DvisBaseManagerView)

// 属性
public:
	CMy3DvisBaseManagerDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy3DvisBaseManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 3DvisBaseManagerView.cpp 中的调试版本
inline CMy3DvisBaseManagerDoc* CMy3DvisBaseManagerView::GetDocument() const
   { return reinterpret_cast<CMy3DvisBaseManagerDoc*>(m_pDocument); }
#endif

