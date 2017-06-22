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
	void SetWidth(int nWidth)
	{ m_nWidth = (nWidth >= 3) ? nWidth : 3; }
	int GetHeight(void) const { return m_nHeight; }
	void Setheight(int nHeight)
	{ m_nHeight = (nHeight >= 3) ? nHeight : 3; }
	int GetColumns(void) const { return m_nColumns; }
	void SetColumns(int nColumns)
	{ m_nColumns = (nColumns >= 5) ? nColumns : 5; }
	int GetRows(void) const { return m_nRows; }
	void SetRows(int nRows)
	{ m_nRows = (nRows >= 5) ? nRows : 5; }
	/*  Function to delete the board and free memory */
	void DeleteBoard(void);

	/* Number of Colors */
	int m_nColors;

	/*  Is the game over? */
	bool CColorMatchBoard::IsGameOver(void) const
	{
		//  Go column by column, left to right
		for (int col = 0; col < m_nColumns; col++)
		{
			//  Row by row, bottom to top
			for (int row = m_nRows - 1; row >= 0; row--)
			{
				int nColor = m_arrBoard[row][col];
				//  Once we hit background, this column is done
				if (nColor == 0)
					break;
				else
				{
					//  Check above and right
					if (row - 1 >= 0 &&
						m_arrBoard[row - 1][col] == nColor)
						return false;
					else if (col + 1 < m_nColumns &&
						m_arrBoard[row][col + 1] == nColor)
						return false;
				}
			}
		}
		//  No two found adjacent
		return true;
	}

	/*  Get the number of blocks remaining */
	int GetRemainingCount(void) const { return m_nRemaining; }
	/*  Function to delete all adjacent blocks */
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

	/*  Functions to get and set the number of colors */
	int GetNumColors(void) { return m_nColors; }
	void SetNumColors(int nColors)
	{
		m_nColors = (nColors >= 3 && nColors <= 7) ? nColors : m_nColors;
	}

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
	int CColorMatchBoard::DeleteNeighborBlocks(int row, int col, int color,
		Direction direction)
	{
		//  Check if it is on the board
		if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
			return 0;
		//  Check if it has the same color
		if (m_arrBoard[row][col] != color)
			return 0;
		int nCount = 1;
		m_arrBoard[row][col] = 0;
		//  If we weren't told to not go back up, check up
		if (direction != DIRECTION_UP)
			nCount +=
			DeleteNeighborBlocks(row - 1, col, color, DIRECTION_DOWN);
		//  If we weren't told to not go back down, check down
		if (direction != DIRECTION_DOWN)
			nCount +=
			DeleteNeighborBlocks(row + 1, col, color, DIRECTION_UP);
		//  If we weren't told to not go back left, check left
		if (direction != DIRECTION_LEFT)
			nCount +=
			DeleteNeighborBlocks(row, col - 1, color, DIRECTION_RIGHT);
		//  If we weren't told to not go back right, check right
		if (direction != DIRECTION_RIGHT)
			nCount +=
			DeleteNeighborBlocks(row, col + 1, color, DIRECTION_LEFT);
		//  Return the total number of pieces deleted
		return nCount;
	}

	/*  Function to compact the board after blocks are eliminated */
	void CColorMatchBoard::CompactBoard(void)
	{
		//  First move everything down
		for (int col = 0; col < m_nColumns; col++)
		{
			int nNextEmptyRow = m_nRows - 1;
			int nNextOccupiedRow = nNextEmptyRow;
			while (nNextOccupiedRow >= 0 && nNextEmptyRow >= 0)
			{
				//  First find the next empty row
				while (nNextEmptyRow >= 0 &&
					m_arrBoard[nNextEmptyRow][col] != 0)
					nNextEmptyRow--;
				if (nNextEmptyRow >= 0)
				{
					//  Then find the next occupied row from the next empty row
					nNextOccupiedRow = nNextEmptyRow - 1;
					while (nNextOccupiedRow >= 0 &&
						m_arrBoard[nNextOccupiedRow][col] == 0)
						nNextOccupiedRow--;
					if (nNextOccupiedRow >= 0)
					{
						//  Now move the block from occupied to empty
						m_arrBoard[nNextEmptyRow][col] =
							m_arrBoard[nNextOccupiedRow][col];
						m_arrBoard[nNextOccupiedRow][col] = 0;
					}
				}
			}
		}
		//  Then move everything from right to left
		int nNextEmptyCol = 0;
		int nNextOccupiedCol = nNextEmptyCol;
		while (nNextEmptyCol < m_nColumns && nNextOccupiedCol < m_nColumns)
		{
			//  First find the next empty column
			while (nNextEmptyCol < m_nColumns &&
				m_arrBoard[m_nRows - 1][nNextEmptyCol] != 0)
				nNextEmptyCol++;
			if (nNextEmptyCol < m_nColumns)
			{
				//  Then find the next column with something in it
				nNextOccupiedCol = nNextEmptyCol + 1;
				while (nNextOccupiedCol < m_nColumns &&
					m_arrBoard[m_nRows - 1][nNextOccupiedCol] == 0)
					nNextOccupiedCol++;
				if (nNextOccupiedCol < m_nColumns)
				{
					//  Move entire column to the left
					for (int row = 0; row < m_nRows; row++)
					{
						m_arrBoard[row][nNextEmptyCol] =
							m_arrBoard[row][nNextOccupiedCol];
						m_arrBoard[row][nNextOccupiedCol] = 0;
					}
				}
			}
		}
	}

	/*  2D array pointer */
	int** m_arrBoard;
	/*  List of colors, 0 is background and 1-7 are piece colors */
	COLORREF m_arrColors[8];
	/*  Board size information */
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;
	/*  Number of blocks remaining */
	int m_nRemaining;
};