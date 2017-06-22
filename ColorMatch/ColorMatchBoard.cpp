#include "StdAfx.h"
#include "ColorMatchBoard.h"

CColorMatchBoard::CColorMatchBoard(void)
	: m_arrBoard(NULL),
	m_nColumns(15), m_nRows(15),
	m_nHeight(35), m_nWidth(35),
	m_nRemaining(0)
{
	m_arrColors[0] = RGB(0, 0, 0);
	m_arrColors[1] = RGB(255, 0, 0);
	m_arrColors[2] = RGB(255, 255, 64);
	m_arrColors[3] = RGB(0, 0, 255);
	m_arrColors[4] = RGB(0, 255, 0);
	m_arrColors[5] = RGB(0, 255, 255);
	m_arrColors[6] = RGB(255, 0, 128);
	m_arrColors[7] = RGB(0, 64, 0);
}

CColorMatchBoard::CColorMatchBoard(const CColorMatchBoard& board)
{
	//  Copy all of the regular data members
	m_nColumns = board.m_nColumns;
	m_nRows = board.m_nRows;
	m_nHeight = board.m_nHeight;
	m_nWidth = board.m_nWidth;
	m_nRemaining = board.m_nRemaining;
	m_nColors = board.m_nColors;
	// Copy ove the colors for the board
	for (int i = 0; i < 8; i++)
		m_arrColors[i] = board.m_arrColors[i];
	m_arrBoard = NULL;

	//  Create a new game board of the same size
	CreateBoard();
	//  Copy the contents of the game board
	for (int row = 0; row < m_nRows; row++)
		for (int col = 0; col < m_nColumns; col++)
			m_arrBoard[row][col] = board.m_arrBoard[row][col];
}

CColorMatchBoard::~CColorMatchBoard(void)
{
	//  Simply delete the board
	DeleteBoard();
}

void CColorMatchBoard::SetupBoard(void)
{
	//  Create the board if needed
	if (m_arrBoard == NULL)
		CreateBoard();
	//  Randomly set each square to a color
	for (int row = 0; row < m_nRows; row++)
		for (int col = 0; col < m_nColumns; col++)
			m_arrBoard[row][col] = (rand() % m_nColors) + 1;
	//  Set the number of spaces remaining
	m_nRemaining = m_nRows * m_nColumns;
}

COLORREF CColorMatchBoard::GetBoardSpace(int row, int col)
{
	//  Check the bounds of the array
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
		return m_arrColors[0];
	return m_arrColors[m_arrBoard[row][col]];
}

void CColorMatchBoard::DeleteBoard(void)
{
	//  Don't delete a NULL board
	if (m_arrBoard != NULL)
	{
		for (int row = 0; row < m_nRows; row++)
		{
			if (m_arrBoard[row] != NULL)
			{
				//  Delete each row first
				delete[] m_arrBoard[row];
				m_arrBoard[row] = NULL;
			}
		}
		//  Finally delete the array of rows
		delete[] m_arrBoard;
		m_arrBoard = NULL;
	}
}

void CColorMatchBoard::CreateBoard(void)
{
	//  If there is already a board, delete it
	if (m_arrBoard != NULL)
		DeleteBoard();
	//  Create the array of rows
	m_arrBoard = new int*[m_nRows];
	//  Create each row
	for (int row = 0; row < m_nRows; row++)
	{
		m_arrBoard[row] = new int[m_nColumns];
		//  Set each square to be empty
		for (int col = 0; col < m_nColumns; col++)
			m_arrBoard[row][col] = 0;
	}
}