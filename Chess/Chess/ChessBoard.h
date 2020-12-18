#pragma once

#include <iostream>
#include <vector>

#include "BoardPosition.h"
#include "ChessPiece.h"

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
	void setBoard(int srcIndex, int destIndex);
	
	// Methods:
	string toString() const;
	void printBoard();
	void updateBoard(string directions);
	
	// Static Functions:
	static int getKingPosition(std::vector<ChessPiece*> board, bool isWhite); // TODO: reference

private:
	// Fields:
	std::vector<ChessPiece*> _board;

	// Helper Methods:
	void addPiece(char pieceType, int position);
};