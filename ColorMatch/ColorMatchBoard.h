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
};