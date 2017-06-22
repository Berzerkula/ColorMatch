#pragma once

class CColorMatchBoard
{
public:
	/*  Default Constructor */
	CColorMatchBoard(void);
	/*  Destructor */
	~CColorMatchBoard(void);
	/*  Function to randomly setup the board */
	void SetupBoard(void);
	/*  Get the color at a particular location */
	COLORREF GetBoardSpace(int row, int col);
	/*  Accessor functions to get board size information */
	int GetWidth(void) const { return m_nWidth; }
	int GetHeight(void) const { return m_nHeight; }
	int GetColumns(void) const { return m_nColumns; }
	int GetRows(void) const { return m_nRows; }
	/*  Function to delete the board and free memory */
	void DeleteBoard(void);
	/*  Is the game over? */
	bool IsGameOver(void) const;
	/*  Get the number of blocks remaining */
	int GetRemainingCount(void) const { return m_nRemaining; }
	/*  Function to delete all adjacent blocks */
	int DeleteBlocks(int row, int col);

private:
	/*  Function to create the board and allocate memory */
	void CreateBoard(void);
	/*  Direction enumeration for deleting blocks */
	enum Direction
	{
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};
	/*  Recursive helper function for deleting blocks */
	int DeleteNeighborBlocks(int row, int col, int color,
		Direction direction);
	/*  Function to compact the board after blocks are eliminated */
	void CompactBoard(void);
	/*  2D array pointer */
	int** m_arrBoard;
	/*  List of colors, 0 is background and 1-3 are piece colors */
	COLORREF m_arrColors[4];
	/*  Board size information */
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;
	/*  Number of blocks remaining */
	int m_nRemaining;

	int CColorMatchBoard::DeleteBlocks(int row, int col)
	{
		//  Make sure that the row and column are valid
		if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
			return -1;
		//  Can't delete background blocks
		int nColor = m_arrBoard[row][col];
		if (nColor == 0)
			return -1;
		//	First check if there are any of the adjacent sides
		//  with the same color
		int nCount = -1;
		if ((row - 1 >= 0 && m_arrBoard[row - 1][col] == nColor) ||
			(row + 1 < m_nRows && m_arrBoard[row + 1][col] == nColor) ||
			(col - 1 >= 0 && m_arrBoard[row][col - 1] == nColor) ||
			(col + 1 < m_nColumns && m_arrBoard[row][col + 1] == nColor))
		{
			//  Then call the recursive function to eliminate all 
			//  other touching blocks with same color
			m_arrBoard[row][col] = 0;
			nCount = 1;
			//  Recursive call for up
			nCount +=
				DeleteNeighborBlocks(row - 1, col, nColor, DIRECTION_DOWN);
			//  Recursive call for down
			nCount +=
				DeleteNeighborBlocks(row + 1, col, nColor, DIRECTION_UP);
			//  Recursive call for left
			nCount +=
				DeleteNeighborBlocks(row, col - 1, nColor, DIRECTION_RIGHT);
			//  Recursive call for right
			nCount +=
				DeleteNeighborBlocks(row, col + 1, nColor, DIRECTION_LEFT);
			//  Finally compact the board
			CompactBoard();
			//  Remove the count from the number remaining
			m_nRemaining -= nCount;
		}
		//  Return the total number of pieces deleted
		return nCount;
	}
};