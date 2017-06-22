
// ColorMatchDoc.h : interface of the CColorMatchDoc class
//


#pragma once

#include "ColorMatchBoard.h"
#include <stack>

class CColorMatchDoc : public CDocument
{
protected: // create from serialization only
	CColorMatchDoc();
	DECLARE_DYNCREATE(CColorMatchDoc)

// Attributes
public:

// Operations
public:

	/*  Functions for accessing the game board */
	COLORREF GetBoardSpace(int row, int col)
	{ return m_board->GetBoardSpace(row, col); }
	void SetupBoard(void) { m_board.SetupBoard(); }
	int GetWidth(void) { return m_board.GetWidth(); }
	void SetWidth(int nWidth) { m_board.SetWidth(nWidth); }
	int GetHeight(void) { return m_board.GetHeight(); }
	void SetHeight(int nHeight) { m_board.Setheight(nHeight); }
	int GetColumns(void) { return m_board.GetColumns(); }
	void SetColumns(int nColumns) { m_board.SetColumns(nColumns); }
	int GetRows(void) { return m_board.GetRows(); }
	void SetRows(int nRows) { m_board.SetRows(nRows); }
	void DeleteBoard(void) { m_board.DeleteBoard(); }
	bool IsGameOver() { return m_board.IsGameOver(); }
	int DeleteBlocks(int row, int col);
	int GetRemainingCount()
	{ return m_board.GetRemainingCount(); }
	int GetNumColors() { return m_board.GetNumColors(); }
	void SetNumColors(int nColors);

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CColorMatchDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	/*  Functions to clear undo/redo stacks */
	void ClearUndo();
	void ClearRedo();
	/*  Instance of the game board */
	CColorMatchBoard m_board;
	/*  Undo stack */
	std::stack<CColorMatchBoard*> m_undo;
	/*  Redo stack */
	std::stack<CColorMatchBoard*> m_redo;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
