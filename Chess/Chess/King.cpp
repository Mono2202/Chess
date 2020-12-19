#include "King.h"

/* King Class */

// Constructors:

King::King(char pieceType) : ChessPiece(pieceType) { }


// Destructors:

King::~King() { }


// Virtual Functions:

bool King::move(BoardPosition srcPos, BoardPosition destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], bool isWhite)
{
	// Inits:
	int diffRow = 0, diffCol = 0;
	bool isValidMove = true;
	int row = 0, column = 0;

	// Condition: invalid King move (Move Code: 6)
	if (abs(srcPos.getRow() - destPos.getRow()) > 1 || abs(srcPos.getColumn() - destPos.getColumn()) > 1)
		isValidMove = false;
	
	return isValidMove;
}