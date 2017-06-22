
// ColorMatchView.h : interface of the CColorMatchView class
//

#pragma once


class CColorMatchView : public CView
{
protected: // create from serialization only
	CColorMatchView();
	DECLARE_DYNCREATE(CColorMatchView)

// Attributes
public:
	CColorMatchDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:

	void ResizeWindow();

	virtual ~CColorMatchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in ColorMatchView.cpp
inline CColorMatchDoc* CColorMatchView::GetDocument() const
   { return reinterpret_cast<CColorMatchDoc*>(m_pDocument); }
#endif

