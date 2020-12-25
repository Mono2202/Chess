#pragma once

#include "ChessPiece.h"

#define QUEEN_DIFFERENCE 1

class Queen : public ChessPiece
{
public:
	// Constructors:
	Queen(const char pieceType);
	
	// Destructors:
	~Queen();

	// Virtual Functions:
	virtual bool move(const BoardPosition& srcPos, const BoardPosition& destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], const bool isWhite);
};