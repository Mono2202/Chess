#pragma once

#include "ChessPiece.h"

#define ROOK_DIFFERENCE 1

class Rook : public ChessPiece
{
public:
	// Constructors:
	Rook(char pieceType);
	
	// Deconstructors:
	~Rook();

	// Virtual Functions:
	virtual bool move(BoardPosition srcPos, BoardPosition destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], bool isWhite);
};