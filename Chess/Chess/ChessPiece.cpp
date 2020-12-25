#include "ChessPiece.h"

/* ChessPiece Class */

// Constructors:

ChessPiece::ChessPiece(const char pieceType) { this->_pieceType = pieceType; }


// Destructors:

ChessPiece::~ChessPiece() { this->_pieceType = 0; }


// Getters:

char ChessPiece::getPieceType() const { return this->_pieceType; }