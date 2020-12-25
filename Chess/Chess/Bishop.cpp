#include "Bishop.h"

/* Bishop Class */

// Constructors:

Bishop::Bishop(const char pieceType) : ChessPiece(pieceType) { }


// Destructors:

Bishop::~Bishop() { }


// Virtual Functions:

/*
Checks Bishop movement validity

Input:
srcPos - the source position
destPos - the destination position
board - the chess board
isWhite - the current player

Output:
isValidMove - true - the move is valid
			  false - otherwise
*/
bool Bishop::move(const BoardPosition& srcPos, const BoardPosition& destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], const bool isWhite)
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
		diffCol = (srcPos.getColumn() < destPos.getColumn()) ? BISHOP_DIFFERENCE : -BISHOP_DIFFERENCE;
		diffRow = (srcPos.getRow() < destPos.getRow()) ? BISHOP_DIFFERENCE : -BISHOP_DIFFERENCE;
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