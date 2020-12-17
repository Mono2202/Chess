#include "Rook.h"

/* Rook Class */

// Constructors:

Rook::Rook(char pieceType, int position) : ChessPiece(pieceType, position) { }


// Destructors:

Rook::~Rook() { }


// Virtual Functions:

string Rook::move(string directions, std::vector<ChessPiece*> board)
{
	// Inits:
	string srcPos = directions.substr(0, 2);  // TODO: #define
	string destPos = directions.substr(2, 2);
	string returnCode = "";

	// Checking general move validity: 
	returnCode = generalMoveCheck(srcPos, destPos, board);

	// Condition: specific Rook moves need to be checked
	if (!returnCode.compare("0"))
	{
		// TODO: Rook move check
	}

	return returnCode;
}