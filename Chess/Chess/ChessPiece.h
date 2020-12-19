#pragma once

#include <iostream>
#include <string>
#include <cmath>

#include "BoardPosition.h"
#include "ChessBoard.h"
#include "MoveCodes.h"

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
	virtual string move(string directions, std::vector<ChessPiece*> board, bool isWhite) = 0; // TODO: maybe refrence vector?
	
protected:
	// Protected Methods:
	string generalMoveCheck(string srcPos, string destPost, std::vector<ChessPiece*> board, bool isWhite);
	bool isChecked(int srcIndex, int destIndex, std::vector<ChessPiece*> board, bool isWhite);

private:
	// Fields:
	char _pieceType;
};