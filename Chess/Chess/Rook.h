#pragma once

#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
	// Constructors:
	Rook(char pieceType, int position);
	
	// Deconstructors:
	~Rook();

	// Virtual Functions:
	virtual string move(string directions, std::vector<ChessPiece*> board, bool isWhite);
};