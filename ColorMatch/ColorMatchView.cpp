
// ColorMatchView.cpp : implementation of the CColorMatchView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ColorMatch.h"
#endif

#include "ColorMatchDoc.h"
#include "ColorMatchView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorMatchView

IMPLEMENT_DYNCREATE(CColorMatchView, CView)

BEGIN_MESSAGE_MAP(CColorMatchView, CView)
END_MESSAGE_MAP()

// CColorMatchView construction/destruction

CColorMatchView::CColorMatchView()
{
	// TODO: add construction code here

}

CColorMatchView::~CColorMatchView()
{
}

BOOL CColorMatchView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CColorMatchView drawing

void CColorMatchView::OnDraw(CDC* /*pDC*/)
{
	CColorMatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CColorMatchView diagnostics

#ifdef _DEBUG
void CColorMatchView::AssertValid() const
{
	CView::AssertValid();
}

void CColorMatchView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CColorMatchDoc* CColorMatchView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColorMatchDoc)));
	return (CColorMatchDoc*)m_pDocument;
}
#endif //_DEBUG


// CColorMatchView message handlers
