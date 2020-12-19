#pragma once

#include "ChessPiece.h"

class King : public ChessPiece
{
public:
	// Constructors:
	King(char pieceType);
	
	// Deconstructors:
	~King();

	// Virtual Functions:
	virtual bool move(BoardPosition srcPos, BoardPosition destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], bool isWhite);
};