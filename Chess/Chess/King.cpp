#include "King.h"

/* King Class */

// Constructors:

King::King(const char pieceType) : ChessPiece(pieceType) { }


// Destructors:

King::~King() { }


// Virtual Functions:

bool King::move(const BoardPosition& srcPos, const BoardPosition& destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], const bool isWhite)
{
	// Inits:
	int diffRow = 0, diffCol = 0;
	bool isValidMove = true;
	int row = 0, column = 0;

	// Condition: invalid King move (Move Code: 6)
	if (abs(srcPos.getRow() - destPos.getRow()) > KING_DIFFERENCE || abs(srcPos.getColumn() - destPos.getColumn()) > KING_DIFFERENCE)
		isValidMove = false;
	
	return isValidMove;
}