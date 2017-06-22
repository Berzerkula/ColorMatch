
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
#include "OptionsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorMatchView

IMPLEMENT_DYNCREATE(CColorMatchView, CView)

BEGIN_MESSAGE_MAP(CColorMatchView, CView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_LEVEL_3COLORS, &CColorMatchView::OnLevel3colors)
	ON_COMMAND(ID_LEVEL_4COLORS, &CColorMatchView::OnLevel4colors)
	ON_COMMAND(ID_LEVEL_5COLORS, &CColorMatchView::OnLevel5colors)
	ON_COMMAND(ID_LEVEL_6COLORS, &CColorMatchView::OnLevel6colors)
	ON_COMMAND(ID_LEVEL_7COLORS, &CColorMatchView::OnLevel7colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_3COLORS, &CColorMatchView::OnUpdateLevel3colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_4COLORS, &CColorMatchView::OnUpdateLevel4colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_5COLORS, &CColorMatchView::OnUpdateLevel5colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_6COLORS, &CColorMatchView::OnUpdateLevel6colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_7COLORS, &CColorMatchView::OnUpdateLevel7colors)
	ON_COMMAND(ID_SETUP_BLOCKCOUNT, &CColorMatchView::OnSetupBlockcount)
	ON_COMMAND(ID_SETUP_BLOCKSIZE, &CColorMatchView::OnSetupBlocksize)
	ON_COMMAND(ID_EDIT_REDO, &CColorMatchView::OnEditRedo)
	ON_COMMAND(ID_EDIT_UNDO, &CColorMatchView::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CColorMatchView::OnUpdateEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CColorMatchView::OnUpdateEditUndo)
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

void CColorMatchView::OnDraw(CDC* pDC) // MFC will comment out the argument name by default; uncomment it
{
	//  First get a pointer to the document
	CColorMatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Save the current state of the device context
	int nDCSave = pDC->SaveDC();
	//  Get the client rectangle
	CRect rcClient;
	GetClientRect(&rcClient);
	//  Get the background color of the board
	COLORREF clr = pDoc->GetBoardSpace(-1, -1);
	//	Draw the background first
	pDC->FillSolidRect(&rcClient, clr);
	//  Create the brush for drawing
	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);
	//	Draw the squares
	for (int row = 0; row < pDoc->GetRows(); row++)
	{
		for (int col = 0; col < pDoc->GetColumns(); col++)
		{
			//  Get the color for this board space
			clr = pDoc->GetBoardSpace(row, col);
			//  Calculate the size and position of this space
			CRect rcBlock;
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();
			//  Fill in the block with the correct color
			pDC->FillSolidRect(&rcBlock, clr);
			//  Draw the block outline
			pDC->Rectangle(&rcBlock);
		}
	}
	//  Restore the device context settings
	pDC->RestoreDC(nDCSave);
	br.DeleteObject();
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


void CColorMatchView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	//  Resize the window
	ResizeWindow();
}

void CColorMatchView::ResizeWindow()
{
	//  First get a pointer to the document
	CColorMatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Get the size of the client area and the window
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	//  Calculate the difference
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();
	//  Change the window size based on the size of the game board
	rcWindow.right = rcWindow.left +
		pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top +
		pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;
	//  The MoveWindow function resizes the frame window
	GetParentFrame()->MoveWindow(&rcWindow);
}

void CColorMatchView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//  First get a pointer to the document
	CColorMatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Get the row and column of the block that was clicked on
	int row = point.y / pDoc->GetHeight();
	int col = point.x / pDoc->GetWidth();
	//  Delete the blocks from the document
	int count = pDoc->DeleteBlocks(row, col);
	//  Check if there were any blocks deleted
	if (count > 0)
	{
		//  Force the view to redraw
		Invalidate();
		UpdateWindow();
		//  Check if the game is over
		if (pDoc->IsGameOver())
		{
			//  Get the count remaining
			int remaining = pDoc->GetRemainingCount();
			CString message;
			message.Format(_T("No more moves left\nBlocks remaining: %d"),
				remaining);
			//  Display the results to the user
			MessageBox(message, _T("Game Over"), MB_OK | MB_ICONINFORMATION);
		}
	}
	//  Default OnLButtonDown
	CView::OnLButtonDown(nFlags, point);
}

void CColorMatchView::setColorCount(int numColors)
{
	//  First get a pointer to the document
	CColorMatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the number of colors
	pDoc->SetNumColors(numColors);
	//  Force the view to redraw
	Invalidate();
	UpdateWindow();
}

void CColorMatchView::OnLevel3colors()
{
	setColorCount(3);
}

void CColorMatchView::OnLevel4colors()
{
	setColorCount(4);
}

void CColorMatchView::OnLevel5colors()
{
	setColorCount(5);
}

void CColorMatchView::OnLevel6colors()
{
	setColorCount(6);
}

void CColorMatchView::OnLevel7colors()
{
	setColorCount(7);
}

void CColorMatchView::OnUpdateLevel3colors(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CColorMatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->GetNumColors() == 3);
}

void CColorMatchView::OnUpdateLevel4colors(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CColorMatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->GetNumColors() == 4);
}

void CColorMatchView::OnUpdateLevel5colors(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CColorMatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->GetNumColors() == 5);
}

void CColorMatchView::OnUpdateLevel6colors(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CColorMatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->GetNumColors() == 6);
}

void CColorMatchView::OnUpdateLevel7colors(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CColorMatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->GetNumColors() == 7);
}

void CColorMatchView::OnSetupBlockcount()
{
	//  First get a pointer to the document
	CColorMatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Create the options dialog
	COptionsDialog dlg(true, this);
	//  Set the row and column values
	dlg.m_nValue1 = pDoc->GetRows();
	dlg.m_nValue2 = pDoc->GetColumns();
	//  Display the dialog
	if (dlg.DoModal() == IDOK)
	{
		//  First delete the board
		pDoc->DeleteBoard();
		//  Get the user selected values
		pDoc->SetRows(dlg.m_nValue1);
		pDoc->SetColumns(dlg.m_nValue2);
		//  Update the board
		pDoc->SetupBoard();
		//  Resize the view
		ResizeWindow();
	}
}


void CColorMatchView::OnSetupBlocksize()
{
	//  First get a pointer to the document
	CColorMatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Create the options dialog
	COptionsDialog dlg(false, this);
	//  Set the width and height values
	dlg.m_nValue1 = pDoc->GetWidth();
	dlg.m_nValue2 = pDoc->GetHeight();
	//  Display the dialog
	if (dlg.DoModal() == IDOK)
	{
		//  First delete the board
		pDoc->DeleteBoard();
		//  Get the user selected values
		pDoc->SetWidth(dlg.m_nValue1);
		pDoc->SetHeight(dlg.m_nValue2);
		//  Update the board
		pDoc->SetupBoard();
		//  Resize the view
		ResizeWindow();
	}
}


void CColorMatchView::OnEditRedo()
{
	//  First get a pointer to the document
	CColorMatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Call redo on the document
	pDoc->RedoLast();
	//  Force the view to redraw
	Invalidate();
	UpdateWindow();
}

void CColorMatchView::OnEditUndo()
{
	//  First get a pointer to the document
	CColorMatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Call undo on the document
	pDoc->UndoLast();
	//  Force the view to redraw
	Invalidate();
	UpdateWindow();
}

void CColorMatchView::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CColorMatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Enable option if it is available
	pCmdUI->Enable(pDoc->CanRedo());
}

void CColorMatchView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CColorMatchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Enable option if it is available
	pCmdUI->Enable(pDoc->CanUndo());
}
