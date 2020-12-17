#pragma once

#include <iostream>
#include <string>

#include "BoardPosition.h"
#include "ChessBoard.h"
#include "MoveCodes.h"

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
	virtual string move(string directions, std::vector<ChessPiece*> board) = 0;
	
protected:
	// Protected Methods:
	string generalMoveCheck(string srcPos, string destPost, std::vector<ChessPiece*> board);
	void updateBoard(ChessBoard board, string directions);

private:
	// Fields:
	char _pieceType;
	int _position;
};