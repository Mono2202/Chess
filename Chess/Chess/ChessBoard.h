#pragma once

#include <iostream>
#include <vector>

#include "BoardPosition.h"
#include "ChessPiece.h"
#include "Rook.h"

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

	// Getters:
	std::vector<ChessPiece*> getBoard() const;

	// Setters:
	void setBoard(BoardPosition src, BoardPosition dest);
	
	// Methods:
	string toString() const;

private:
	// Fields:
	std::vector<ChessPiece*> _board;

	// Helper Methods:
	void addPiece(char pieceType, int position);
};