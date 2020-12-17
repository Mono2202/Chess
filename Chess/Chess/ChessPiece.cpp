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


// Protected Methods:

string ChessPiece::generalMoveCheck(string srcPos, string destPos, std::vector<ChessPiece*> board)
{
	// Inits:
	string returnCode = "0";
	int srcIndex = srcPos[0] - 'a' + (BOARD_SIZE - srcPos[1]) * BOARD_SIZE;
	int destIndex = destPos[0] - 'a' + (BOARD_SIZE - destPos[1]) * BOARD_SIZE;

	// TODO: #define
	// Condition: move index out of range (Move Code: 5)
	if ((srcPos[0] < 'a' || srcPos[0] > 'h') ||
		(srcPos[1] < '1' || srcPos[1] > '8') ||
		(destPos[0] < 'a' || destPos[0] > 'h') ||
		(destPos[1] < '1' || destPos[1] > '8'))
	{
		returnCode = MoveCodes::ToString(MoveCodes::ERROR_INVALID_INDEX);
	}

	// Condition: srcPos equals to the destPos (Move Code: 7)
	else if (srcIndex == destIndex)
	{
		returnCode = MoveCodes::ToString(MoveCodes::ERROR_SRC_IS_DEST);
	}

	// Condition: no friendly piece in srcPos (Move Code: 2)
	else if (board[srcIndex] == NULL || 
			 islower(this->getPieceType()) != islower(board[srcIndex]->getPieceType()))
	{
		returnCode = MoveCodes::ToString(MoveCodes::ERROR_NO_FRIENDLY_PIECE_IN_SRC);
	}

	// Condition: friendly piece in destPos (Move Code: 3)
	else if (islower(this->getPieceType()) == islower(board[destIndex]->getPieceType()))
	{
		returnCode = MoveCodes::ToString(MoveCodes::ERROR_FRIENDLY_PIECE_IN_DEST);
	}

	// Condition: move will lead to check on the friendly King (Move Code: 4)
	else if (false)
	{
		// TODO: check check lol ;)
	}

	return returnCode;
}