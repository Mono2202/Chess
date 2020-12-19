#pragma once

#include <iostream>
#include <string>
#include <cmath>

#include "ChessBoard.h"
#include "MoveCodes.h"

#define BOARD_SIZE 8

using std::string;

class ChessBoard;

class ChessPiece
{
public:
	// Constructors:
	ChessPiece(char pieceType);

	// Destructors:
	~ChessPiece();

	// Getters:
	char getPieceType() const;

	// Pure Virtual Functions:
	virtual bool move(BoardPosition srcPos, BoardPosition destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], bool isWhite) = 0;

private:
	// Fields:
	char _pieceType;
};