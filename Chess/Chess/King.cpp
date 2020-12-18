#include "King.h"

/* King Class */

// Constructors:

King::King(char pieceType, int position) : ChessPiece(pieceType, position) { }


// Destructors:

King::~King() { }


// Virtual Functions:

string King::move(string directions, std::vector<ChessPiece*> board, bool isWhite)
{
	// Inits:
	string srcPos = directions.substr(0, 2);  // TODO: #define
	string destPos = directions.substr(2, 2);
	int srcIndex = srcPos[0] - 'a' + (BOARD_SIZE - (srcPos[1] - '0')) * BOARD_SIZE;
	int destIndex = destPos[0] - 'a' + (BOARD_SIZE - (destPos[1] - '0')) * BOARD_SIZE;
	int difference = 0;
	string returnCode = "";
	bool collisionFound = false;
	int i = 0;
	
	// Checking general move validity: 
	returnCode = generalMoveCheck(srcPos, destPos, board, isWhite);

	// Condition: invalid King move (Move Code: 6)
	if (abs(srcIndex % BOARD_SIZE - destIndex % BOARD_SIZE) > 1 || abs(srcIndex / BOARD_SIZE - destIndex / BOARD_SIZE) > 1)
		returnCode = MoveCodes::ToString(MoveCodes::CODES::ERROR_INVALID_MOVE);
	
	// Condition: move made check on enemy King (Move Code: 1)
	if (returnCode == "0" && this->isChecked(srcIndex, destIndex, board, !isWhite))
		returnCode = "1";

	return returnCode;
}


// TODO: CHANGE VECTOR TO 2D ARRAY