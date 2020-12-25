#include "Knight.h"

/* Knight Class */

// Constructors:

Knight::Knight(const char pieceType) : ChessPiece(pieceType) { }


// Destructors:

Knight::~Knight() { }


// Virtual Functions:

bool Knight::move(const BoardPosition& srcPos, const BoardPosition& destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], const bool isWhite)
{
	// Inits:
	int diffRow = abs(srcPos.getRow() - destPos.getRow()), diffCol = abs(srcPos.getColumn() - destPos.getColumn());
	bool isValidMove = true;

	// Condition: invalid Knight move (Move Code: 6)
	if (diffRow * diffCol != KNIGHT_DIFFERENCE_2)
		isValidMove = false;
	
	return isValidMove;
}