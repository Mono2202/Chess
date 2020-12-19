#include "Rook.h"

/* Rook Class */

// Constructors:

Rook::Rook(char pieceType) : ChessPiece(pieceType) { }


// Destructors:

Rook::~Rook() { }


// Virtual Functions:

bool Rook::move(BoardPosition srcPos, BoardPosition destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], bool isWhite)
{
	// Inits:
	int diffRow = 0, diffCol = 0;
	bool isValidMove = true;
	int row = 0, column = 0;

	// Condition: move isn't horizontal and isn't vertical
	if (srcPos.getRow() != destPos.getRow() && srcPos.getColumn() != destPos.getColumn())
		isValidMove = false;
		
	// Condition: vertical move
	else if (srcPos.getRow() == destPos.getRow())
		diffCol = (destPos.getColumn() < destPos.getColumn()) ? 1 : -1;

	// Condition: horizontal move
	else
		diffRow = (srcPos.getRow() < destPos.getRow()) ? 1 : -1; // TODO: #define

	// Checking for collisions:
	for (row = srcPos.getRow() + diffRow, column = srcPos.getColumn() + diffCol;
		(row != destPos.getRow() || column != destPos.getColumn()) && isValidMove;
		row += diffRow, column += diffCol)
	{
		// Condition: collision detected, invalid Rook move (Move Code: 6)
		if (board[row][column] != NULL)
			isValidMove = false;
	}
	
	return isValidMove;
}