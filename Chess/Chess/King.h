#pragma once

#include "ChessPiece.h"

#define KING_DIFFERENCE 1

class King : public ChessPiece
{
public:
	// Constructors:
	King(char pieceType);
	
	// Destructors:
	~King();

	// Virtual Functions:
	virtual bool move(BoardPosition srcPos, BoardPosition destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], bool isWhite);
};