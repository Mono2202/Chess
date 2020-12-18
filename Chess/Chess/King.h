#pragma once

#include "ChessPiece.h"

class King : public ChessPiece
{
public:
	// Constructors:
	King(char pieceType, int position);
	
	// Deconstructors:
	~King();

	// Virtual Functions:
	virtual string move(string directions, std::vector<ChessPiece*> board, bool isWhite);
};