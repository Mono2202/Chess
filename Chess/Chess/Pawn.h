#pragma once

#include "ChessPiece.h"

#define PAWN_DIFFERENCE 1

#define STARTING_PAWN_MOVE 2
#define DEFAULT_PAWN_MOVE 1

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