#include "Queen.h"

/* Queen Class */

// Constructors:

Queen::Queen(char pieceType) : ChessPiece(pieceType) { }


// Destructors:

Queen::~Queen() { }


// Virtual Functions:

bool Queen::move(BoardPosition srcPos, BoardPosition destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], bool isWhite)
{
	// Inits:
	int diffRow = 0, diffCol = 0;
	bool isValidMove = true;
	int row = 0, column = 0;

	// Condition: invalid King move (Move Code: 6)
	if ((srcPos.getRow() != destPos.getRow() && srcPos.getColumn() != destPos.getColumn()) &&
		abs(srcPos.getRow() - destPos.getRow()) != abs(srcPos.getColumn() - destPos.getColumn()))
		isValidMove = false;

	// Condition: vertical move
	else if (srcPos.getRow() == destPos.getRow())
		diffCol = (srcPos.getColumn() < destPos.getColumn()) ? 1 : -1;

	// Condition: horizontal move
	else if (srcPos.getColumn() == destPos.getColumn())
		diffRow = (srcPos.getRow() < destPos.getRow()) ? 1 : -1; // TODO: #define

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
		// Condition: collision detected, invalid Queen move (Move Code: 6)
		if (board[row][column] != NULL)
			isValidMove = false;
	}

	return isValidMove;
}