#include "Pawn.h"

/* Pawn Class */

// Constructors:

Pawn::Pawn(const char pieceType) : ChessPiece(pieceType)
{
	this->_hasMoved = false;
	this->_isEnPassant = false;
}


// Getters:

bool Pawn::getIsEnPassant() const { return this->_isEnPassant; }


// Setters:

void Pawn::setIsEnPassant(bool flag) { this->_isEnPassant = flag; }


// Destructors:

Pawn::~Pawn() { this->_hasMoved = false; }


// Virtual Functions:

/*
Checks Pawn movement validity

Input:
srcPos - the source position
destPos - the destination position
board - the chess board
isWhite - the current player

Output:
isValidMove - true - the move is valid
			  false - otherwise
*/
bool Pawn::move(const BoardPosition& srcPos, const BoardPosition& destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], const bool isWhite)
{
	// Inits:
	int moveDirection = (isWhite) ? -PAWN_DIFFERENCE : PAWN_DIFFERENCE;
	bool isValidMove = false;
	int row = 0, column = 0;

	// Condition: first Pawn move
	if (!this->_hasMoved && (destPos.getRow() - srcPos.getRow()) * moveDirection <= STARTING_PAWN_MOVE &&
		srcPos.getColumn() == destPos.getColumn() &&
		board[destPos.getRow()][destPos.getColumn()] == NULL &&
		board[srcPos.getRow() + moveDirection][srcPos.getColumn()] == NULL)
	{
		isValidMove = true;
		this->_hasMoved = true;

		if ((destPos.getRow() - srcPos.getRow()) * moveDirection == STARTING_PAWN_MOVE)
			this->_isEnPassant = true;
	}
	
	// Condition: not first Pawn move
	else if (this->_hasMoved && (destPos.getRow() - srcPos.getRow()) * moveDirection == DEFAULT_PAWN_MOVE &&
		srcPos.getColumn() == destPos.getColumn() &&
		board[destPos.getRow()][destPos.getColumn()] == NULL)
		isValidMove = true;

	// Condition: Pawn is able to attack
	else if ((destPos.getRow() - srcPos.getRow()) * moveDirection == DEFAULT_PAWN_MOVE &&
		abs(destPos.getColumn() - srcPos.getColumn()) == 1 && 
		board[destPos.getRow()][destPos.getColumn()] != NULL)
	{
		isValidMove = true;
		this->_hasMoved = true;
	}

	return isValidMove;
}