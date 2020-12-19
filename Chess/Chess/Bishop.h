#pragma once

#include "ChessPiece.h"

class Bishop : public ChessPiece
{
public:
	// Constructors:
	Bishop(char pieceType);
	
	// Deconstructors:
	~Bishop();

	// Virtual Functions:
	virtual bool move(BoardPosition srcPos, BoardPosition destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], bool isWhite);
};