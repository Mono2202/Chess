#pragma once

#include <iostream>
#include <vector>

#include "ChessPiece.h"
#include "BoardPosition.h"

using std::string;

#define BOARD_SIZE 8

#define EMPTY_SPACE '#'
#define STARTING_PLAYER '0'

class ChessPiece;

class ChessBoard
{
public:
	// Constructors:
	ChessBoard(string startingBoard);

	// Deconstructors:
	~ChessBoard();
	
	// General Methods:
	string toString() const;
	void printBoard();

	// Chess Methods:
	void updateBoard(int srcRow, int srcCol, int destRow, int destCol);

private:
	// Fields:
	ChessPiece* _board[BOARD_SIZE][BOARD_SIZE];

	// Helper Methods:
	void addPiece(char pieceType, int row, int column);
	BoardPosition getKingPosition(bool isWhite);
};