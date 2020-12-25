#pragma once

#include "ChessPiece.h"

#define BISHOP_DIFFERENCE 1

class Bishop : public ChessPiece
{
public:
	// Constructors:
	Bishop(const char pieceType);
	
	// Destructors:
	~Bishop();

	// Virtual Functions:
	virtual bool move(const BoardPosition& srcPos, const BoardPosition& destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], const bool isWhite);
};