#pragma once

#include "ChessPiece.h"

class Pawn : public ChessPiece
{
public:
	// Constructors:
	Pawn(char pieceType);
	
	// Deconstructors:
	~Pawn();

	// Virtual Functions:
	virtual bool move(BoardPosition srcPos, BoardPosition destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], bool isWhite);

private:
	// Fields:
	bool _hasMoved;
};