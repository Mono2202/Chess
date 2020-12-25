#pragma once

#include "ChessPiece.h"

#define KING_DIFFERENCE 1

class King : public ChessPiece
{
public:
	// Constructors:
	King(const char pieceType);
	
	// Destructors:
	~King();

	// Virtual Functions:
	virtual bool move(const BoardPosition& srcPos, const BoardPosition& destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], const bool isWhite);
};