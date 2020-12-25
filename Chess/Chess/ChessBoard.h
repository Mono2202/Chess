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

#define MOVE_DIFFERENCE 1

#define BLACK_PIECES "qrbnpk"
#define WHITE_PIECES "QRBNPK"

#define QUEEN_INDEX 0
#define ROOK_INDEX 1
#define BISHOP_INDEX 2
#define KNIGHT_INDEX 3
#define PAWN_INDEX 4
#define KING_INDEX 5

#define POSSIBLE_KNIGHT_THREATS_ARRAY_SIZE 4
#define POSSIBLE_PAWN_THREATS 2
#define POSSIBLE_KING_THREATS_ARRAY_SIZE 3

#define QUEEN_SIDE_CASTLE 2
#define KING_SIDE_CASTLE 3

class ChessBoard
{
public:
	// Constructors:
	ChessBoard(const string& startingBoard);

	// Destructors:
	~ChessBoard();

	// General Methods:
	void printBoard() const;

	// Chess Methods:
	string moveCheck(const BoardPosition& srcPos, const BoardPosition& destPos, const bool isWhite);
	void updateBoard(const BoardPosition& srcPos, const BoardPosition& destPos);

private:
	// Fields:
	ChessPiece* _board[BOARD_SIZE][BOARD_SIZE];

	// Helper Methods:
	void addPiece(const char pieceType, const BoardPosition& position);
	BoardPosition getKingPosition(const bool isWhite) const;
	bool isThreatened(const BoardPosition& srcPos, const string& possibleEnemyPieces, const bool isWhite);
	bool isChecked(const BoardPosition& srcPos, const BoardPosition& destPos, const bool isWhite);
	bool isCastle(const BoardPosition& srcPos, const BoardPosition& destPos, const bool isWhite);

	// isChecked Helper Methods:
	bool rowCheck(const BoardPosition& kingPos, const string& possibleEnemyPieces, const bool isWhite, const int difference);
	bool columnCheck(const BoardPosition& kingPos, const string& possibleEnemyPieces, const bool isWhite, const int difference);
	bool mainDiagonalCheck(const BoardPosition& kingPos, const string& possibleEnemyPieces, const bool isWhite, const int difference);
	bool secondaryDiagonalCheck(const BoardPosition& kingPos, const string& possibleEnemyPieces, const bool isWhite, const int difference);
	bool knightCheck(const BoardPosition& kingPos, const string& possibleEnemyPieces);
	bool pawnCheck(const BoardPosition& kingPos, const string& possibleEnemyPieces, const bool isWhite);
	bool kingCheck(const BoardPosition& kingPos, const string& possibleEnemyPieces);
};