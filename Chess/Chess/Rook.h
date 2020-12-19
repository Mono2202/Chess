#pragma once

#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
	// Constructors:
	Rook(char pieceType);
	
	// Deconstructors:
	~Rook();

	// Virtual Functions:
	virtual string move(string directions, std::vector<ChessPiece*> board, bool isWhite);
};