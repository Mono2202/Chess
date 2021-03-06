#include "Queen.h"

/* Queen Class */

// Constructors:

Queen::Queen(const char pieceType) : ChessPiece(pieceType) { }


// Destructors:

Queen::~Queen() { }


// Virtual Functions:

/*
Checks Queen movement validity

Input:
srcPos - the source position
destPos - the destination position
board - the chess board
isWhite - the current player

Output:
isValidMove - true - the move is valid
			  false - otherwise
*/
bool Queen::move(const BoardPosition& srcPos, const BoardPosition& destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], const bool isWhite)
{
	// Inits:
	int diffRow = 0, diffCol = 0;
	bool isValidMove = true;
	int row = 0, column = 0;

	// Condition: invalid Queen move (Move Code: 6)
	if ((srcPos.getRow() != destPos.getRow() && srcPos.getColumn() != destPos.getColumn()) &&
		abs(srcPos.getRow() - destPos.getRow()) != abs(srcPos.getColumn() - destPos.getColumn()))
		isValidMove = false;

	// Condition: vertical move
	else if (srcPos.getRow() == destPos.getRow())
		diffCol = (srcPos.getColumn() < destPos.getColumn()) ? QUEEN_DIFFERENCE : -QUEEN_DIFFERENCE;

	// Condition: horizontal move
	else if (srcPos.getColumn() == destPos.getColumn())
		diffRow = (srcPos.getRow() < destPos.getRow()) ? QUEEN_DIFFERENCE : -QUEEN_DIFFERENCE;

	// Condition: diagonal move
	else
	{
		diffCol = (srcPos.getColumn() < destPos.getColumn()) ? QUEEN_DIFFERENCE : -QUEEN_DIFFERENCE;
		diffRow = (srcPos.getRow() < destPos.getRow()) ? QUEEN_DIFFERENCE : -QUEEN_DIFFERENCE;
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