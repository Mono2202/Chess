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

string ChessPiece::generalMoveCheck(string srcPos, string destPos, std::vector<ChessPiece*> board, bool isWhite)
{
	// Inits:
	string returnCode = "0";
	int srcIndex = srcPos[0] - 'a' + (BOARD_SIZE - (srcPos[1] - '0')) * BOARD_SIZE;
	int destIndex = destPos[0] - 'a' + (BOARD_SIZE - (destPos[1] - '0')) * BOARD_SIZE;

	// TODO: #define
	// Condition: move index out of range (Move Code: 5)
	if ((srcPos[0] < 'a' || srcPos[0] > 'h') ||
		(srcPos[1] < '1' || srcPos[1] > '8') ||
		(destPos[0] < 'a' || destPos[0] > 'h') ||
		(destPos[1] < '1' || destPos[1] > '8'))
		returnCode = MoveCodes::ToString(MoveCodes::CODES::ERROR_INVALID_PIECE_INDEX);

	// Condition: srcPos equals to the destPos (Move Code: 7)
	else if (srcIndex == destIndex)
		returnCode = MoveCodes::ToString(MoveCodes::CODES::ERROR_SRC_IS_DEST);

	// Condition: no friendly piece in srcPos (Move Code: 2)
	else if (board[srcIndex] == NULL ||
			 isWhite != isupper(board[srcIndex]->getPieceType()) ||
			 islower(this->getPieceType()) != islower(board[srcIndex]->getPieceType()))
		returnCode = MoveCodes::ToString(MoveCodes::CODES::ERROR_NO_FRIENDLY_PIECE_IN_SRC);

	// Condition: friendly piece in destPos (Move Code: 3)
	else if (board[destIndex] != NULL &&
			 islower(this->getPieceType()) == islower(board[destIndex]->getPieceType()))
		returnCode = MoveCodes::ToString(MoveCodes::CODES::ERROR_FRIENDLY_PIECE_IN_DEST);

	// Condition: move will lead to check on the friendly King (Move Code: 4)
	else if (isChecked(srcIndex, destIndex, board, isWhite))
		returnCode = MoveCodes::ToString(MoveCodes::CODES::ERROR_FRIENDLY_CHECK);  // TODO: MOVE AFTER SPECIFIC MOVES CHECK

	return returnCode;
}


bool ChessPiece::isChecked(int srcIndex, int destIndex, std::vector<ChessPiece*> board, bool isWhite) // TODO: optimize? && ADD PAWN CHECK && split to functions
{
	// Inits:
	string possibleEnemyPieces = (isWhite) ? "qrbnp" : "QRBNP"; // TODO: #define indexes
	int kingPosition = ChessBoard::getKingPosition(board, isWhite);
	bool friendlyPieceFound = false;
	int i = 0;

	// Updating the board:
	board[destIndex] = board[srcIndex];
	board[srcIndex] = NULL;

	// Checking right to the King:
	for (i = kingPosition + 1; i / BOARD_SIZE == kingPosition / BOARD_SIZE && !friendlyPieceFound; i++)
	{
		// Condition: enemy piece found in King's path
		if (board[i] != NULL && board[i]->getPieceType() == possibleEnemyPieces[0] || board[i]->getPieceType() == possibleEnemyPieces[1])
			return true;
		
		// Condition: friendly piece found in King's path
		else if (board[i] != NULL && islower(board[i]->getPieceType()) != isWhite)
			friendlyPieceFound = true;
	}

	// Resetting the flag:
	friendlyPieceFound = false;

	// Checking left to the King:
	for (i = kingPosition - 1; i / BOARD_SIZE == kingPosition / BOARD_SIZE && !friendlyPieceFound; i--)
	{
		// Condition: enemy piece found in King's path
		if (board[i] != NULL && board[i]->getPieceType() == possibleEnemyPieces[0] || board[i]->getPieceType() == possibleEnemyPieces[1])
			return true;
		
		// Condition: friendly piece found in King's path
		else if (board[i] != NULL && islower(board[i]->getPieceType()) != isWhite)
			friendlyPieceFound = true;
	}

	// Resetting the flag:
	friendlyPieceFound = false;

	// Checking down to the King:
	for (i = kingPosition + BOARD_SIZE; i < BOARD_SIZE * BOARD_SIZE && !friendlyPieceFound; i += BOARD_SIZE)
	{
		// Condition: enemy piece found in King's path
		if (board[i] != NULL && board[i]->getPieceType() == possibleEnemyPieces[0] || board[i]->getPieceType() == possibleEnemyPieces[1])
			return true;
		
		// Condition: friendly piece found in King's path
		else if (board[i] != NULL && islower(board[i]->getPieceType()) != isWhite)
			friendlyPieceFound = true;
	}

	// Resetting the flag:
	friendlyPieceFound = false;

	// Checking up to the King:
	for (i = kingPosition - BOARD_SIZE; i >= 0 && !friendlyPieceFound; i -= BOARD_SIZE)
	{
		// Condition: enemy piece found in King's path
		if (board[i] != NULL && board[i]->getPieceType() == possibleEnemyPieces[0] || board[i]->getPieceType() == possibleEnemyPieces[1])
			return true;
		
		// Condition: friendly piece found in King's path
		else if (board[i] != NULL && islower(board[i]->getPieceType()) != isWhite)
			friendlyPieceFound = true;
	}

	// Resetting the flag:
	friendlyPieceFound = false;

	// Checking main diagonal (right) to the King:
	for (i = kingPosition + (BOARD_SIZE + 1); ((i - (BOARD_SIZE + 1)) % BOARD_SIZE != BOARD_SIZE - 1) && (i < BOARD_SIZE * BOARD_SIZE) && !friendlyPieceFound; i += (BOARD_SIZE + 1))
	{
		// Condition: enemy piece found in King's path
		if (board[i] != NULL && board[i]->getPieceType() == possibleEnemyPieces[0] || board[i]->getPieceType() == possibleEnemyPieces[2])
			return true;
		
		// Condition: friendly piece found in King's path
		else if (board[i] != NULL && islower(board[i]->getPieceType()) != isWhite)
			friendlyPieceFound = true;
	}

	// Resetting the flag:
	friendlyPieceFound = false;

	// Checking main diagonal (left) to the King:
	for (i = kingPosition - (BOARD_SIZE + 1);  ((i + (BOARD_SIZE + 1)) % BOARD_SIZE != 0) && (i >= 0) && !friendlyPieceFound; i -= (BOARD_SIZE + 1))
	{
		// Condition: enemy piece found in King's path
		if (board[i] != NULL && board[i]->getPieceType() == possibleEnemyPieces[0] || board[i]->getPieceType() == possibleEnemyPieces[2])
			return true;
		
		// Condition: friendly piece found in King's path
		else if (board[i] != NULL && islower(board[i]->getPieceType()) != isWhite)
			friendlyPieceFound = true;
	}

	// Resetting the flag:
	friendlyPieceFound = false;

	// Checking secondary diagonal (right) to the King:
	for (i = kingPosition - (BOARD_SIZE - 1); ((i + (BOARD_SIZE - 1)) % BOARD_SIZE != BOARD_SIZE - 1) && (i >= 0) && !friendlyPieceFound; i -= (BOARD_SIZE - 1))
	{
		// Condition: enemy piece found in King's path
		if (board[i] != NULL && board[i]->getPieceType() == possibleEnemyPieces[0] || board[i]->getPieceType() == possibleEnemyPieces[2])
			return true;
		
		// Condition: friendly piece found in King's path
		else if (board[i] != NULL && islower(board[i]->getPieceType()) != isWhite)
			friendlyPieceFound = true;
	}

	// Resetting the flag:
	friendlyPieceFound = false;

	// Checking secondary diagonal (left) to the King:
	for (i = kingPosition + (BOARD_SIZE - 1); ((i - (BOARD_SIZE - 1)) % BOARD_SIZE != 0) && (i < BOARD_SIZE * BOARD_SIZE) && !friendlyPieceFound; i += (BOARD_SIZE - 1))
	{
		// Condition: enemy piece found in King's path
		if (board[i] != NULL && board[i]->getPieceType() == possibleEnemyPieces[0] || board[i]->getPieceType() == possibleEnemyPieces[2])
			return true;
		
		// Condition: friendly piece found in King's path
		else if (board[i] != NULL && islower(board[i]->getPieceType()) != isWhite)
			friendlyPieceFound = true;
	}

	return false;

	// TODO: KNIGHT AND PAWN CHECK CHECK
}