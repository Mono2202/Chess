#pragma once

#include <iostream>
#include <string>
#include <cmath>

#include "MoveCodes.h"
#include "BoardPosition.h"

#define BOARD_SIZE 8

using std::string;

class ChessPiece
{
public:
	// Constructors:
	ChessPiece(const char pieceType);

	// Destructors:
	~ChessPiece();

	// Getters:
	char getPieceType() const;

	// Pure Virtual Functions:
	virtual bool move(const BoardPosition& srcPos, const BoardPosition& destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], const bool isWhite) = 0;

private:
	// Fields:
	char _pieceType;
};