#include "ChessBoard.h"

/* ChessBoard Class */

// Constructors:

ChessBoard::ChessBoard(string startingBoard)
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
				this->addPiece(startingBoard[row * BOARD_SIZE + column], BoardPosition(row, column)); // TODO: PASS BoardPosition object
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

string ChessBoard::toString() const
{
	// Inits:
	string boardString = "";
	int row = 0, column = 0;

	// Building the board string:
	for (row = 0; row < BOARD_SIZE; row++)
	{
		for (column = 0; column < BOARD_SIZE; column++)
		{
			// Condition: chess piece
			if (this->_board[row][column] != NULL)
			{
				boardString += this->_board[row][column]->getPieceType();
			}

			// Condition: empty spot
			else
			{
				boardString += EMPTY_SPACE;
			}
		}
	}

	// Starting player:
	boardString += STARTING_PLAYER;

	return boardString;
}

void ChessBoard::printBoard()
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

string ChessBoard::moveCheck(BoardPosition srcPos, BoardPosition destPos, bool isWhite)
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
		returnCode = MoveCodes::ToString(MoveCodes::CODES::ERROR_FRIENDLY_CHECK);  // TODO: MOVE AFTER SPECIFIC MOVES CHECK

	// Condition: valid move (Move Code: 0)
	if (returnCode == "0")

		// Condition: move made check on enemy King (Move Code: 1)
		returnCode = (isChecked(srcPos, destPos, !isWhite)) ? "1" : "0";

	return returnCode;
}

void ChessBoard::updateBoard(BoardPosition srcPos, BoardPosition destPos)
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

void ChessBoard::addPiece(char pieceType, BoardPosition position)
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

BoardPosition ChessBoard::getKingPosition(bool isWhite)
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

bool ChessBoard::isChecked(BoardPosition srcPos, BoardPosition destPos, bool isWhite)
{
	// Inits:
	string possibleEnemyPieces = (isWhite) ? "qrbnpk" : "QRBNPK"; // TODO: #define indexes
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
	checkFlag = rowCheck(kingPosition, possibleEnemyPieces, isWhite, 1) || rowCheck(kingPosition, possibleEnemyPieces, isWhite, -1) ||
		columnCheck(kingPosition, possibleEnemyPieces, isWhite, 1) || columnCheck(kingPosition, possibleEnemyPieces, isWhite, -1) ||
		mainDiagonalCheck(kingPosition, possibleEnemyPieces, isWhite, 1) || mainDiagonalCheck(kingPosition, possibleEnemyPieces, isWhite, -1) ||
		secondaryDiagonalCheck(kingPosition, possibleEnemyPieces, isWhite, 1) || secondaryDiagonalCheck(kingPosition, possibleEnemyPieces, isWhite, -1) ||
		knightCheck(kingPosition, possibleEnemyPieces) || pawnCheck(kingPosition, possibleEnemyPieces, isWhite); // TODO: KING THREAT CHECK

	// Un-doing the board update:
	this->_board[srcPos.getRow()][srcPos.getColumn()] = this->_board[destPos.getRow()][destPos.getColumn()];
	this->_board[destPos.getRow()][destPos.getColumn()] = tempChessPiece;

	return checkFlag;
}


// isChecked Helper Methods:

bool ChessBoard::rowCheck(BoardPosition kingPos, string possibleEnemyPieces, bool isWhite, int difference)
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
			if (currentChessPiece == possibleEnemyPieces[0] || currentChessPiece == possibleEnemyPieces[1])
				return true;

			// Condition: blocking piece found in King's path
			else
				blockingPieceFound = true;
		}
	}

	return false;
}

bool ChessBoard::columnCheck(BoardPosition kingPos, string possibleEnemyPieces, bool isWhite, int difference)
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
			if (currentChessPiece == possibleEnemyPieces[0] || currentChessPiece == possibleEnemyPieces[1])
				return true;

			// Condition: blocking piece found in King's path
			else
				blockingPieceFound = true;
		}
	}

	return false;
}

bool ChessBoard::mainDiagonalCheck(BoardPosition kingPos, string possibleEnemyPieces, bool isWhite, int difference)
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
			if (currentChessPiece == possibleEnemyPieces[0] || currentChessPiece == possibleEnemyPieces[2])
				return true;

			// Condition: blocking piece found in King's path
			else
				blockingPieceFound = true;
		}
	}

	return false;
}

bool ChessBoard::secondaryDiagonalCheck(BoardPosition kingPos, string possibleEnemyPieces, bool isWhite, int difference)
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
			if (currentChessPiece == possibleEnemyPieces[0] || currentChessPiece == possibleEnemyPieces[2])
				return true;

			// Condition: blocking piece found in King's path
			else
				blockingPieceFound = true;
		}
	}

	return false;
}

bool ChessBoard::knightCheck(BoardPosition kingPos, string possibleEnemyPieces)
{
	// Inits:
	BoardPosition candidateMove(kingPos.getRow(), kingPos.getColumn());
	int diffArray[4] = { 1, 2, -1, -2 };
	int i = 0, j = 0;

	// Checking for Knight threat:
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
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
					if (this->_board[candidateMove.getRow()][candidateMove.getColumn()]->getPieceType() == possibleEnemyPieces[3])
						return true;
			}
		}
	}

	return false;
}

bool ChessBoard::pawnCheck(BoardPosition kingPos, string possibleEnemyPieces, bool isWhite)
{
	// Inits:
	int moveDirection = (isWhite) ? -1 : 1;
	BoardPosition candidateMove(kingPos.getRow() + moveDirection, kingPos.getColumn() - 1);
	int i = 0;

	for (i = 0; i < 2; i++)
	{
		// Condition: Chess Piece is not out of bounds and exists
		if (!candidateMove.isOutOfBounds() && this->_board[candidateMove.getRow()][candidateMove.getColumn()] != NULL)

			// Condition: Pawn threat found
			if (this->_board[candidateMove.getRow()][candidateMove.getColumn()]->getPieceType() == possibleEnemyPieces[4])
				return true;

		// Checking other possible Pawn threat position:
		candidateMove.setColumn(kingPos.getColumn() + 1);
	}

	return false;
}