#pragma once

#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
	// Constructors:
	Knight(char pieceType);
	
	// Deconstructors:
	~Knight();

	// Virtual Functions:
	virtual bool move(BoardPosition srcPos, BoardPosition destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], bool isWhite);
};