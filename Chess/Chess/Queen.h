#pragma once

#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
	// Constructors:
	Queen(char pieceType);
	
	// Deconstructors:
	~Queen();

	// Virtual Functions:
	virtual bool move(BoardPosition srcPos, BoardPosition destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], bool isWhite);
};