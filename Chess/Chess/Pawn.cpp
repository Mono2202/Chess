#include "Pawn.h"

/* Pawn Class */

// Constructors:

Pawn::Pawn(char pieceType) : ChessPiece(pieceType) { this->_hasMoved = false; }


// Destructors:

Pawn::~Pawn() { this->_hasMoved = false; }


// Virtual Functions:

bool Pawn::move(BoardPosition srcPos, BoardPosition destPos, ChessPiece* board[BOARD_SIZE][BOARD_SIZE], bool isWhite)
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