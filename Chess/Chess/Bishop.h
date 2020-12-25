#pragma once

#include "ChessPiece.h"

#define BISHOP_DIFFERENCE 1

class Bishop : public ChessPiece
{
public:
	// Constructors:
	Bishop(char pieceType);
	
	// Destructors:
	~Bishop();

	// Virtual Functions:
	virtual bool move(BoardPosition srcPos, BoardPosition destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], bool isWhite);
};