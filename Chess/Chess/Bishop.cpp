#include "Bishop.h"

/* Bishop Class */

// Constructors:

Bishop::Bishop(char pieceType) : ChessPiece(pieceType) { }


// Destructors:

Bishop::~Bishop() { }


// Virtual Functions:

bool Bishop::move(BoardPosition srcPos, BoardPosition destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], bool isWhite)
{
	// Inits:
	int diffRow = 0, diffCol = 0;
	bool isValidMove = true;
	int row = 0, column = 0;

	// Condition: invalid Bishop move (Move Code: 6)
	if (abs(srcPos.getRow() - destPos.getRow()) != abs(srcPos.getColumn() - destPos.getColumn()))
		isValidMove = false;

	// Condition: diagonal move
	else
	{
		diffCol = (srcPos.getColumn() < destPos.getColumn()) ? 1 : -1;
		diffRow = (srcPos.getRow() < destPos.getRow()) ? 1 : -1;
	}

	// Checking for collisions:
	for (row = srcPos.getRow() + diffRow, column = srcPos.getColumn() + diffCol;
		(row != destPos.getRow() || column != destPos.getColumn()) && isValidMove;
		row += diffRow, column += diffCol)
	{
		// Condition: collision detected, invalid Bishop move (Move Code: 6)
		if (board[row][column] != NULL)
			isValidMove = false;
	}

	return isValidMove;
}