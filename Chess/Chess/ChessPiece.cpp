#include "ChessPiece.h"

/* ChessPiece Class */

// Constructors:

ChessPiece::ChessPiece(char pieceType, int position)
{
	this->_pieceType = pieceType;
}


// Deconstructors:

ChessPiece::~ChessPiece() { }


// Getters:

char ChessPiece::getPieceType() const
{
	return this->_pieceType;
}