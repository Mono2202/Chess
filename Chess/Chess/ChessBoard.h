#pragma once

#include <iostream>
#include <vector>

#include "ChessPiece.h"
#include "BoardPosition.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

using std::string;

#define BOARD_SIZE 8

#define EMPTY_SPACE '#'
#define STARTING_PLAYER '0'

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
	string moveCheck(BoardPosition srcPos, BoardPosition destPos, bool isWhite);
	void updateBoard(BoardPosition srcPos, BoardPosition destPos);

private:
	// Fields:
	ChessPiece* _board[BOARD_SIZE][BOARD_SIZE];

	// Helper Methods:
	void addPiece(char pieceType, BoardPosition position);
	BoardPosition getKingPosition(bool isWhite);
	bool isChecked(BoardPosition srcPos, BoardPosition destPos, bool isWhite);

	// isChecked Helper Methods:
	bool rowCheck(BoardPosition kingPos, string possibleEnemyPieces, bool isWhite, int difference);
	bool columnCheck(BoardPosition kingPos, string possibleEnemyPieces, bool isWhite, int difference);
	bool mainDiagonalCheck(BoardPosition kingPos, string possibleEnemyPieces, bool isWhite, int difference);
	bool secondaryDiagonalCheck(BoardPosition kingPos, string possibleEnemyPieces, bool isWhite, int difference);
	bool knightCheck(BoardPosition kingPos, string possibleEnemyPieces);
	bool pawnCheck(BoardPosition kingPos, string possibleEnemyPieces, bool isWhite);
};

// TODO?: operator[]