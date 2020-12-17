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
	int srcIndex = srcPos[0] - 'a' + (BOARD_SIZE - srcPos[1]) * BOARD_SIZE;
	int destIndex = destPos[0] - 'a' + (BOARD_SIZE - destPos[1]) * BOARD_SIZE;
	int difference = 0;
	string returnCode = "";
	bool collisionFound = false;
	int i = 0;
	
	// Checking general move validity: 
	returnCode = generalMoveCheck(srcPos, destPos, board);

	// Condition: specific Rook moves need to be checked
	if (!returnCode.compare("0"))
	{
		// Condition: move isn't horizontal and isn't vertical
		if (srcPos[0] != destPos[0] && srcPos[1] != destPos[1])
			returnCode = MoveCodes::ToString(MoveCodes::ERROR_INVALID_MOVE);
		
		// Condition: vertical move
		if (srcPos[0] == destPos[0])
			difference = (srcIndex < destIndex) ? BOARD_SIZE : -BOARD_SIZE;

		// Condition: horizontal move
		else
			difference = (srcIndex < destIndex) ? 1 : -1; // TODO: #define

		// Checking for collisions:
		for (i = srcIndex + difference; i < destIndex && !collisionFound; i += difference)
		{
			// Condition: collision detected (Move Code: 6)
			if (!board[i])
			{
				returnCode = MoveCodes::ToString(MoveCodes::ERROR_INVALID_MOVE);
				collisionFound = true;
			}
		}
	}

	return returnCode;
}