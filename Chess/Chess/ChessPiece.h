#pragma once

#include <iostream>

#include "BoardPosition.h"
#include "ChessBoard.h"

using std::string;

class ChessBoard;

class ChessPiece
{
public:
	// Constructors:
	ChessPiece(char pieceType, int position);

	// Destructors:
	~ChessPiece();

	// Getters:
	char getPieceType() const;

	// Pure Virtual Functions:
	virtual string move(string directions) = 0;
	
protected:
	// Protected Methods:
	void updateBoard(ChessBoard board, string directions);

private:
	// Fields:
	char _pieceType;
	int _position;
};