#include "ChessBoard.h"

/* ChessBoard Class */

// Constructors:

/*
Builds the ChessBoard object using the startingBoard string

Input:
startingBoard - the starting board string

Output:
None
*/
ChessBoard::ChessBoard(const string& startingBoard)
{
	// Inits:
	int row = 0, column = 0;

	// Initializing the board array:
	for (row = 0; row < BOARD_SIZE ; row++)
	{
		for (column = 0; column < BOARD_SIZE; column++)
		{
			// Condition: chess piece to create
			if (startingBoard[row * BOARD_SIZE + column] != EMPTY_SPACE)
			{
				this->addPiece(startingBoard[row * BOARD_SIZE + column], BoardPosition(row, column));
			}

			// Condition: empty spot
			else
			{
				this->_board[row][column] = NULL;
			}
		}
	}
}


// Destructors:

/*
Clearing the chess board from the ChessPiece objects

Input:
None

Output:
None
*/
ChessBoard::~ChessBoard()
{
	// Inits:
	int row = 0, column = 0;

	// Clearing the board:
	for (row = 0; row < BOARD_SIZE; row++)
	{
		for (column = 0; column < BOARD_SIZE; column++)
		{
			// Condition: deleting the current chess piece
			if (this->_board[row][column] != NULL)
			{
				delete this->_board[row][column];
			}
		}
	}
}


// General Methods:

/*
Prints the current chess board

Input:
None

Output:
None
*/
void ChessBoard::printBoard() const
{
	// Inits:
	int row = 0, column = 0;

	// Printing the board as a 2D-array:
	for (row = 0; row < BOARD_SIZE; row++)
	{
		for (column = 0; column < BOARD_SIZE; column++)
		{
			// Condition: chess piece
			if (this->_board[row][column] != NULL)
				std::cout << this->_board[row][column]->getPieceType() << " ";

			// Condition: empty spot
			else
				std::cout << "# ";
		}

		// New line:
		std::cout << std::endl;
	}
}


// Chess Methods:

/*
Checks general movement validity

Input:
srcPos - the source position
destPos - the destination position
isWhite - the current player

Output:
returnCode - according to the check results
*/
string ChessBoard::moveCheck(const BoardPosition& srcPos, const BoardPosition& destPos, const bool isWhite)
{
	// Inits:
	string returnCode = "0";

	// Condition: move index out of bounds (Move Code: 5)
	if (srcPos.isOutOfBounds() || destPos.isOutOfBounds())
		returnCode = MoveCodes::ToString(MoveCodes::CODES::ERROR_INVALID_PIECE_INDEX);

	// Condition: srcPos equals to the destPos (Move Code: 7)
	else if (srcPos == destPos)
		returnCode = MoveCodes::ToString(MoveCodes::CODES::ERROR_SRC_IS_DEST);

	// Condition: no friendly piece in srcPos (Move Code: 2)
	else if (this->_board[srcPos.getRow()][srcPos.getColumn()] == NULL ||
		isWhite != isupper(this->_board[srcPos.getRow()][srcPos.getColumn()]->getPieceType()))
		returnCode = MoveCodes::ToString(MoveCodes::CODES::ERROR_NO_FRIENDLY_PIECE_IN_SRC);

	// Condition: friendly piece in destPos (Move Code: 3)
	else if (this->_board[destPos.getRow()][destPos.getColumn()] != NULL &&
		isWhite == isupper(this->_board[destPos.getRow()][destPos.getColumn()]->getPieceType()))
		returnCode = MoveCodes::ToString(MoveCodes::CODES::ERROR_FRIENDLY_PIECE_IN_DEST);

	// Condition: invalid specific Chess Piece move (Move Code: 6)
	else if (!this->_board[srcPos.getRow()][srcPos.getColumn()]->move(srcPos, destPos, this->_board, isWhite))
		returnCode = MoveCodes::ToString(MoveCodes::CODES::ERROR_INVALID_MOVE);

	// Condition: move will lead to Check on the friendly King (Move Code: 4)
	else if (isChecked(srcPos, destPos, isWhite))
		returnCode = MoveCodes::ToString(MoveCodes::CODES::ERROR_FRIENDLY_CHECK);

	// Condition: valid move (Move Code: 0)
	if (returnCode == MoveCodes::ToString(MoveCodes::CODES::VALID_MOVE))

		// Condition: move made check on enemy King (Move Code: 1)
		returnCode = (isChecked(srcPos, destPos, !isWhite)) ? 
		MoveCodes::ToString(MoveCodes::CODES::VALID_CHECK) : 
		MoveCodes::ToString(MoveCodes::CODES::VALID_MOVE);

	return returnCode;
}

/*
Updates the chess board

Input:
srcPos - the source position
destPos - the destination position

Output:
None
*/
void ChessBoard::updateBoard(const BoardPosition& srcPos, const BoardPosition& destPos)
{
	// Condition: deleting the chess piece
	if (this->_board[destPos.getRow()][destPos.getColumn()] != NULL)
		delete this->_board[destPos.getRow()][destPos.getColumn()];

	// Switching both positions:
	this->_board[destPos.getRow()][destPos.getColumn()] = this->_board[srcPos.getRow()][srcPos.getColumn()];

	// Emptying the source position:
	this->_board[srcPos.getRow()][srcPos.getColumn()] = NULL;
}


// Helper Methods:

/*
Adds a ChessPiece object to the chess board
according to the proper chess piece type

Input:
pieceType - the chess piece type
position - chess piece's board position

Output:
None
*/
void ChessBoard::addPiece(const char pieceType, const BoardPosition& position)
{
	// Creating the proper chess piece:
	switch (toupper(pieceType))
	{
		case 'P': this->_board[position.getRow()][position.getColumn()] = new Pawn(pieceType); break;
		case 'N': this->_board[position.getRow()][position.getColumn()] = new Knight(pieceType); break;
		case 'B': this->_board[position.getRow()][position.getColumn()] = new Bishop(pieceType); break;
		case 'R': this->_board[position.getRow()][position.getColumn()] = new Rook(pieceType); break;
		case 'Q': this->_board[position.getRow()][position.getColumn()] = new Queen(pieceType); break;
		case 'K': this->_board[position.getRow()][position.getColumn()] = new King(pieceType); break;
	}
}

/*
Gets the King's current position

Input:
isWhite - the King to search for

Output:
kingPosition - the King's current postion
*/
BoardPosition ChessBoard::getKingPosition(const bool isWhite) const
{
	// Inits:
	BoardPosition kingPosition;
	char kingToFind = (isWhite) ? 'K' : 'k';
	bool found = false;
	int i = 0, j = 0;

	// Finds the wanted king's position:
	for (i = 0; i < BOARD_SIZE && !found; i++)
	{
		for (j = 0; j < BOARD_SIZE && !found; j++)
		{
			// Condition: position found
			if (this->_board[i][j] != NULL && this->_board[i][j]->getPieceType() == kingToFind)
			{
				kingPosition.setRow(i);
				kingPosition.setColumn(j);
				found = true;
			}
		}
	}

	return kingPosition;
}

/*
Checks whether the King is checked

Input:
srcPos - the source position
destPos - the destination position
isWhite - the King to check

Output:
checkFlag - true - the King is checked
			false - otherwise
*/
bool ChessBoard::isChecked(const BoardPosition& srcPos, const BoardPosition& destPos, const bool isWhite)
{
	// Inits:
	string possibleEnemyPieces = (isWhite) ? "qrbnpk" : "QRBNPK";
	ChessPiece* tempChessPiece;
	BoardPosition kingPosition;
	bool checkFlag = false;

	// Simulating board update:
	tempChessPiece = this->_board[destPos.getRow()][destPos.getColumn()];
	this->_board[destPos.getRow()][destPos.getColumn()] = this->_board[srcPos.getRow()][srcPos.getColumn()];
	this->_board[srcPos.getRow()][srcPos.getColumn()] = NULL;

	// Getting the current King's position:
	kingPosition = ChessBoard::getKingPosition(isWhite);

	// Checking for Check on King:
	checkFlag = rowCheck(kingPosition, possibleEnemyPieces, isWhite, MOVE_DIFFERENCE) || rowCheck(kingPosition, possibleEnemyPieces, isWhite, -MOVE_DIFFERENCE) ||
		columnCheck(kingPosition, possibleEnemyPieces, isWhite, MOVE_DIFFERENCE) || columnCheck(kingPosition, possibleEnemyPieces, isWhite, -MOVE_DIFFERENCE) ||
		mainDiagonalCheck(kingPosition, possibleEnemyPieces, isWhite, MOVE_DIFFERENCE) || mainDiagonalCheck(kingPosition, possibleEnemyPieces, isWhite, -MOVE_DIFFERENCE) ||
		secondaryDiagonalCheck(kingPosition, possibleEnemyPieces, isWhite, MOVE_DIFFERENCE) || secondaryDiagonalCheck(kingPosition, possibleEnemyPieces, isWhite, -MOVE_DIFFERENCE) ||
		knightCheck(kingPosition, possibleEnemyPieces) || pawnCheck(kingPosition, possibleEnemyPieces, isWhite); // TODO: KING THREAT CHECK

	// Un-doing the board update:
	this->_board[srcPos.getRow()][srcPos.getColumn()] = this->_board[destPos.getRow()][destPos.getColumn()];
	this->_board[destPos.getRow()][destPos.getColumn()] = tempChessPiece;

	return checkFlag;
}


// isChecked Helper Methods:

/*
Checks for check in the King's row

Input:
kingPos - the King's current position
possibleEnemyPieces - string of enemy pieces
isWhite - the current player
difference - the check difference

Output:
true - check was found
false - otherwise
*/
bool ChessBoard::rowCheck(const BoardPosition& kingPos, const string& possibleEnemyPieces, const bool isWhite, const int difference)
{
	// Inits:
	char currentChessPiece = '0';
	bool blockingPieceFound = false;
	int row = kingPos.getRow(), column = 0;

	// Checking the King's row for Check:
	for (column = kingPos.getColumn() + difference; column < BOARD_SIZE && column >= 0 && !blockingPieceFound; column += difference)
	{
		// Condition: chess piece at board[row][column]
		if (this->_board[row][column] != NULL)
		{
			// Getting the current Chess Piece:
			currentChessPiece = this->_board[row][column]->getPieceType();

			// Condition: enemy piece found in King's path
			if (currentChessPiece == possibleEnemyPieces[QUEEN_INDEX] || currentChessPiece == possibleEnemyPieces[ROOK_INDEX])
				return true;

			// Condition: blocking piece found in King's path
			else
				blockingPieceFound = true;
		}
	}

	return false;
}

/*
Checks for check in the King's column

Input:
kingPos - the King's current position
possibleEnemyPieces - string of enemy pieces
isWhite - the current player
difference - the check difference

Output:
true - check was found
false - otherwise
*/
bool ChessBoard::columnCheck(const BoardPosition& kingPos, const string& possibleEnemyPieces, const bool isWhite, const int difference)
{
	// Inits:
	char currentChessPiece = '0';
	bool blockingPieceFound = false;
	int row = 0, column = kingPos.getColumn();

	// Checking the King's column for Check:
	for (row = kingPos.getRow() + difference; row < BOARD_SIZE && row >= 0 && !blockingPieceFound; row += difference)
	{
		// Condition: chess piece at board[row][column]
		if (this->_board[row][column] != NULL)
		{
			// Getting the current Chess Piece:
			currentChessPiece = this->_board[row][column]->getPieceType();

			// Condition: enemy piece found in King's path
			if (currentChessPiece == possibleEnemyPieces[QUEEN_INDEX] || currentChessPiece == possibleEnemyPieces[ROOK_INDEX])
				return true;

			// Condition: blocking piece found in King's path
			else
				blockingPieceFound = true;
		}
	}

	return false;
}

/*
Checks for check in the King's main diagonal

Input:
kingPos - the King's current position
possibleEnemyPieces - string of enemy pieces
isWhite - the current player
difference - the check difference

Output:
true - check was found
false - otherwise
*/
bool ChessBoard::mainDiagonalCheck(const BoardPosition& kingPos, const string& possibleEnemyPieces, const bool isWhite, const int difference)
{
	// Inits:
	char currentChessPiece = '0';
	bool blockingPieceFound = false;
	int row = 0, column = 0;

	// Checking the King's main diagonal for Check:
	for (row = kingPos.getRow() + difference, column = kingPos.getColumn() + difference; 
		row < BOARD_SIZE && row >= 0 && column < BOARD_SIZE && column >= 0 && !blockingPieceFound;
		row += difference, column += difference)
	{
		// Condition: chess piece at board[row][column]
		if (this->_board[row][column] != NULL)
		{
			// Getting the current Chess Piece:
			currentChessPiece = this->_board[row][column]->getPieceType();

			// Condition: enemy piece found in King's path
			if (currentChessPiece == possibleEnemyPieces[QUEEN_INDEX] || currentChessPiece == possibleEnemyPieces[BISHOP_INDEX])
				return true;

			// Condition: blocking piece found in King's path
			else
				blockingPieceFound = true;
		}
	}

	return false;
}

/*
Checks for check in the King's secondary diagonal

Input:
kingPos - the King's current position
possibleEnemyPieces - string of enemy pieces
isWhite - the current player
difference - the check difference

Output:
true - check was found
false - otherwise
*/
bool ChessBoard::secondaryDiagonalCheck(const BoardPosition& kingPos, const string& possibleEnemyPieces, const bool isWhite, const int difference)
{
	// Inits:
	char currentChessPiece = '0';
	bool blockingPieceFound = false;
	int row = 0, column = 0;

	// Checking the King's secondary diagonal for Check:
	for (row = kingPos.getRow() + difference, column = kingPos.getColumn() - difference;
		row < BOARD_SIZE && row >= 0 && column < BOARD_SIZE && column >= 0 && !blockingPieceFound;
		row += difference, column -= difference)
	{
		// Condition: chess piece at board[row][column]
		if (this->_board[row][column] != NULL)
		{
			// Getting the current Chess Piece:
			currentChessPiece = this->_board[row][column]->getPieceType();

			// Condition: enemy piece found in King's path
			if (currentChessPiece == possibleEnemyPieces[QUEEN_INDEX] || currentChessPiece == possibleEnemyPieces[BISHOP_INDEX])
				return true;

			// Condition: blocking piece found in King's path
			else
				blockingPieceFound = true;
		}
	}

	return false;
}

/*
Checks for check in the King's Knight positions

Input:
kingPos - the King's current position
possibleEnemyPieces - string of enemy pieces
isWhite - the current player
difference - the check difference

Output:
true - check was found
false - otherwise
*/
bool ChessBoard::knightCheck(const BoardPosition& kingPos, const string& possibleEnemyPieces)
{
	// Inits:
	BoardPosition candidateMove(kingPos.getRow(), kingPos.getColumn());
	int diffArray[POSSIBLE_KNIGHT_THREATS_ARRAY_SIZE] = { KNIGHT_DIFFERENCE_1, KNIGHT_DIFFERENCE_2, -KNIGHT_DIFFERENCE_1, -KNIGHT_DIFFERENCE_2 };
	int i = 0, j = 0;

	// Checking for Knight threat:
	for (i = 0; i < POSSIBLE_KNIGHT_THREATS_ARRAY_SIZE; i++)
	{
		for (j = 0; j < POSSIBLE_KNIGHT_THREATS_ARRAY_SIZE; j++)
		{
			// Condition: different difference
			if (abs(diffArray[i]) != abs(diffArray[j]))
			{
				// Setting the new position to check for Knight in:
				candidateMove.setRow(kingPos.getRow() + diffArray[i]);
				candidateMove.setColumn(kingPos.getColumn() + diffArray[j]);

				// Condition: Chess Piece is not out of bounds and exists
				if (!candidateMove.isOutOfBounds() && this->_board[candidateMove.getRow()][candidateMove.getColumn()] != NULL)

					// Condition: Knight threat found
					if (this->_board[candidateMove.getRow()][candidateMove.getColumn()]->getPieceType() == possibleEnemyPieces[KNIGHT_INDEX])
						return true;
			}
		}
	}

	return false;
}

/*
Checks for check in the King's Pawn positions

Input:
kingPos - the King's current position
possibleEnemyPieces - string of enemy pieces
isWhite - the current player
difference - the check difference

Output:
true - check was found
false - otherwise
*/
bool ChessBoard::pawnCheck(const BoardPosition& kingPos, const string& possibleEnemyPieces, const bool isWhite)
{
	// Inits:
	int moveDirection = (isWhite) ? -PAWN_DIFFERENCE : PAWN_DIFFERENCE;
	BoardPosition candidateMove(kingPos.getRow() + moveDirection, kingPos.getColumn() - PAWN_DIFFERENCE);
	int i = 0;

	for (i = 0; i < POSSIBLE_PAWN_THREATS; i++)
	{
		// Condition: Chess Piece is not out of bounds and exists
		if (!candidateMove.isOutOfBounds() && this->_board[candidateMove.getRow()][candidateMove.getColumn()] != NULL)

			// Condition: Pawn threat found
			if (this->_board[candidateMove.getRow()][candidateMove.getColumn()]->getPieceType() == possibleEnemyPieces[PAWN_INDEX])
				return true;

		// Checking other possible Pawn threat position:
		candidateMove.setColumn(kingPos.getColumn() + PAWN_DIFFERENCE);
	}

	return false;
}