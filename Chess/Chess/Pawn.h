#pragma once

#include "ChessPiece.h"

#define PAWN_DIFFERENCE 1

#define STARTING_PAWN_MOVE 2
#define DEFAULT_PAWN_MOVE 1

class Pawn : public ChessPiece
{
public:
	// Constructors:
	Pawn(const char pieceType);
	
	// Destructors:
	~Pawn();

	// Virtual Functions:
	virtual bool move(const BoardPosition& srcPos, const BoardPosition& destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], const bool isWhite);

private:
	// Fields:
	bool _hasMoved;
};