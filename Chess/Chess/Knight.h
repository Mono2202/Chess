#pragma once

#include "ChessPiece.h"

#define KNIGHT_DIFFERENCE_1 1
#define KNIGHT_DIFFERENCE_2 2

class Knight : public ChessPiece
{
public:
	// Constructors:
	Knight(char pieceType);
	
	// Destructors:
	~Knight();

	// Virtual Functions:
	virtual bool move(BoardPosition srcPos, BoardPosition destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], bool isWhite);
};