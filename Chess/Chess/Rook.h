#pragma once

#include "ChessPiece.h"

#define ROOK_DIFFERENCE 1

class Rook : public ChessPiece
{
public:
	// Constructors:
	Rook(const char pieceType);
	
	// Destructors:
	~Rook();

	// Virtual Functions:
	virtual bool move(const BoardPosition& srcPos, const BoardPosition& destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], const bool isWhite);
};