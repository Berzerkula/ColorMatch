
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
	void setColorCount(int numColors);

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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	/* Functions to change the difficulty level */
	afx_msg void OnLevel3colors();
	afx_msg void OnLevel4colors();
	afx_msg void OnLevel5colors();
	afx_msg void OnLevel6colors();
	afx_msg void OnLevel7colors();

	/* Functions to update the menu options */
	afx_msg void OnUpdateLevel3colors(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLevel4colors(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLevel5colors(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLevel6colors(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLevel7colors(CCmdUI *pCmdUI);

	afx_msg void OnSetupBlockcount();
	afx_msg void OnSetupBlocksize();
};

#ifndef _DEBUG  // debug version in ColorMatchView.cpp
inline CColorMatchDoc* CColorMatchView::GetDocument() const
   { return reinterpret_cast<CColorMatchDoc*>(m_pDocument); }
#endif

