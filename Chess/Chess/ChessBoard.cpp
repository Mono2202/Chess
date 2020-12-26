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
				addPiece(startingBoard[row * BOARD_SIZE + column], BoardPosition(row, column));
			}

			// Condition: empty spot
			else
			{
				this->_board[row][column] = NULL;
			}
		}
	}

	// Initializing the en-passant Pawn:
	this->_enPassantPawn = NULL;
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
	string returnCode = "00";

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

	// Condition: invalid specific Chess Piece move (Move Code: 6)
	if (returnCode == MoveCodes::ToString(MoveCodes::CODES::ERROR_INVALID_MOVE))
	{
		// Condition: Castling was taking place (Move Code: 9)
		if (isCastle(srcPos, destPos, isWhite))
			returnCode = MoveCodes::ToString(MoveCodes::CODES::VALID_CASTLE);

		// Condition: En-Passant was taking place (Move Code: 10)
		else if (isEnPassant(srcPos, destPos, isWhite))
			returnCode = MoveCodes::ToString(MoveCodes::CODES::VALID_EN_PASSANT);
	}

	// Condition: valid move (Move Code: 0 / 9 / 10)
	if (returnCode == MoveCodes::ToString(MoveCodes::CODES::VALID_MOVE) ||
		returnCode == MoveCodes::ToString(MoveCodes::CODES::VALID_CASTLE) ||
		returnCode == MoveCodes::ToString(MoveCodes::CODES::VALID_EN_PASSANT))
	{
		// Condition: Promotion was taking place (Move Code: 11)
		if (isPromotion(srcPos, destPos, isWhite))
			returnCode = MoveCodes::ToString(MoveCodes::CODES::VALID_PROMOTION);
		
		// Condition: move made check on enemy King (Move Code: 1)
		if (isChecked(srcPos, destPos, !isWhite))
			returnCode = MoveCodes::ToString(MoveCodes::CODES::VALID_CHECK);
		
		// Sets the current En-Passant Pawn:
		setEnPassant(srcPos, isWhite);
	}
	
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
	char kingToFind = (isWhite) ? WHITE_PIECES[KING_INDEX] : BLACK_PIECES[KING_INDEX];
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
Checks whether a position is threatenend

Input:
srcPos - the source position
destPos - the destination position
isWhite - the current player

Output:
true - position is threatened
false - otherwise
*/
bool ChessBoard::isThreatened(const BoardPosition& srcPos, const string& possibleEnemyPieces, const bool isWhite)
{
	return rowCheck(srcPos, possibleEnemyPieces, isWhite, MOVE_DIFFERENCE) || rowCheck(srcPos, possibleEnemyPieces, isWhite, -MOVE_DIFFERENCE) ||
		columnCheck(srcPos, possibleEnemyPieces, isWhite, MOVE_DIFFERENCE) || columnCheck(srcPos, possibleEnemyPieces, isWhite, -MOVE_DIFFERENCE) ||
		mainDiagonalCheck(srcPos, possibleEnemyPieces, isWhite, MOVE_DIFFERENCE) || mainDiagonalCheck(srcPos, possibleEnemyPieces, isWhite, -MOVE_DIFFERENCE) ||
		secondaryDiagonalCheck(srcPos, possibleEnemyPieces, isWhite, MOVE_DIFFERENCE) || secondaryDiagonalCheck(srcPos, possibleEnemyPieces, isWhite, -MOVE_DIFFERENCE) ||
		knightCheck(srcPos, possibleEnemyPieces) || pawnCheck(srcPos, possibleEnemyPieces, isWhite) || kingCheck(srcPos, possibleEnemyPieces);
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
	string possibleEnemyPieces = (isWhite) ? BLACK_PIECES : WHITE_PIECES;
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
	checkFlag = isThreatened(kingPosition, possibleEnemyPieces, isWhite);

	// Un-doing the board update:
	this->_board[srcPos.getRow()][srcPos.getColumn()] = this->_board[destPos.getRow()][destPos.getColumn()];
	this->_board[destPos.getRow()][destPos.getColumn()] = tempChessPiece;

	return checkFlag;
}

/*
Checks wheter Castle is possible

Input:
srcPos - the source position
destPos - the destination position
isWhite - the current player

Output:
true - Castle is possible
false - otherwise
*/
bool ChessBoard::isCastle(const BoardPosition& srcPos, const BoardPosition& destPos, const bool isWhite)
{
	// Inits:
	int difference = (destPos.getColumn() < srcPos.getColumn()) ? -MOVE_DIFFERENCE : MOVE_DIFFERENCE;
	int castleMoves = (destPos.getColumn() < srcPos.getColumn()) ? QUEEN_SIDE_CASTLE : KING_SIDE_CASTLE;
	string possibleEnemyPieces = (isWhite) ? BLACK_PIECES : WHITE_PIECES;
	BoardPosition candidateMove(srcPos.getRow(), srcPos.getColumn());
	King* currentKing = dynamic_cast<King*>(this->_board[srcPos.getRow()][srcPos.getColumn()]);
	Rook* currentRook = dynamic_cast<Rook*>(this->_board[srcPos.getRow()][srcPos.getColumn() + (castleMoves + MOVE_DIFFERENCE) * difference]);
	int i = 0;

	// Condition: more than 2 King steps were made
	if (abs(destPos.getColumn() - srcPos.getColumn()) > KING_SIDE_CASTLE)
		return false;

	// Condition: srcPos has a Chess Piece
	if (this->_board[srcPos.getRow()][srcPos.getColumn()] != NULL)
	{
		// Condition: srcPos is not the King's position
		if (!(srcPos == getKingPosition(isWhite)))
			return false;

		else
		{
			// Condition: destPos has a Chess Piece
			if (this->_board[srcPos.getRow()][srcPos.getColumn() + (castleMoves + MOVE_DIFFERENCE) * difference] != NULL)
			{
				// Condition: Rook is in Castle position
				if (toupper(this->_board[srcPos.getRow()][srcPos.getColumn() + (castleMoves + MOVE_DIFFERENCE) * difference]->getPieceType()) == WHITE_PIECES[ROOK_INDEX])
				{
					// Condition: Chess Piece can't Castle
					if (!currentKing->getCanCastle() || !currentRook->getCanCastle())
						return false;
				}

				// Condition: Rook is not in Castle position
				else
					return false;
					
			}

			// Condition: destPos doesn't have a Chess Piece
			else
				return false;
				
		}
	}

	// Condition: srcPos doesn't have a Chess Piece
	else
		return false;

	// Checking whether Castling is possible:
	for (i = 1; i <= castleMoves; i++)
	{
		// Updating the candidate move positions:
		candidateMove.setColumn(srcPos.getColumn() + difference * i);

		// Condition: empty spot
		if (this->_board[candidateMove.getRow()][candidateMove.getColumn()] == NULL)
		{
			// Condition: Chess Piece at candidate move positions is threatend
			if (i <= KING_SIDE_CASTLE && isThreatened(candidateMove, possibleEnemyPieces, isWhite))
				return false;
		}
		
		// Condition: spot with Chess Piece
		else
			return false;
	}

	// Setting the canCastle flag:
	currentKing->setCanCastle(false);
	currentRook->setCanCastle(false);

	// Moving the Rook and updating the board:
	updateBoard(BoardPosition(srcPos.getRow(), srcPos.getColumn() + (castleMoves + MOVE_DIFFERENCE) * difference), BoardPosition(srcPos.getRow(), srcPos.getColumn() + difference));

	return true;
}

/*
Checks wheter En-Passant is possible

Input:
srcPos - the source position
destPos - the destination position
isWhite - the current player

Output:
true - En-Passant is possible
false - otherwise
*/
bool ChessBoard::isEnPassant(const BoardPosition& srcPos, const BoardPosition& destPos, const bool isWhite)
{
	// Inits:
	int direction = (isWhite) ? MOVE_DIFFERENCE : -MOVE_DIFFERENCE;

	// Condition: En-Passant Pawn exists and attacking Chess Piece is a Pawn
	if (this->_board[destPos.getRow() + direction][destPos.getColumn()] == this->_enPassantPawn &&
		toupper(this->_board[srcPos.getRow()][srcPos.getColumn()]->getPieceType()) == WHITE_PIECES[PAWN_INDEX])
		
		// Condition: valid diagonal Pawn attack, En-Passant is possible
		if ((destPos.getRow() - srcPos.getRow()) * direction * -PAWN_DIFFERENCE == DEFAULT_PAWN_MOVE &&
			abs(destPos.getColumn() - srcPos.getColumn()) == 1)
			return true;

	return false;
}

/*
Sets the En-Passant Pawn

Input:
srcPos - the source position
isWhite - the current player

Output:
None
*/
void ChessBoard::setEnPassant(const BoardPosition& srcPos, const bool isWhite)
{
	// Inits:
	Pawn* currentPawn;

	// Condition: current En-Passant Pawn exists
	if (this->_enPassantPawn != NULL)
	{
		// Condition: En-Passant is not longer possible
		if (isupper(this->_enPassantPawn->getPieceType()) == isWhite)
		{
			this->_enPassantPawn->setIsEnPassant(false);
			this->_enPassantPawn = NULL;
		}
	}

	// Condition: new candidate to En-Passant Pawn
	if (toupper(this->_board[srcPos.getRow()][srcPos.getColumn()]->getPieceType()) == WHITE_PIECES[PAWN_INDEX])
	{
		// Casting ChessPiece* as Pawn:
		currentPawn = dynamic_cast<Pawn*>(this->_board[srcPos.getRow()][srcPos.getColumn()]);

		// Condition: candidate Pawn can En-Passant
		if (currentPawn->getIsEnPassant())
		{
			// Condition: current En-Passant Pawn exists 
			if (this->_enPassantPawn != NULL)
				this->_enPassantPawn->setIsEnPassant(false);

			// Setting the new current En-Passant Pawn:
			this->_enPassantPawn = currentPawn;
		}
	}
}

/*
Checks wheter Promotion is possible

Input:
srcPos - the source position
destPos - the destination position
isWhite - the current player

Output:
true - Promotion is possible
false - otherwise
*/
bool ChessBoard::isPromotion(const BoardPosition& srcPos, const BoardPosition& destPos, const bool isWhite)
{
	// Inits:
	int promotionRow = (isWhite) ? WHITE_PROMOTION_ROW : BLACK_PROMOTION_ROW;
	char queenToPromote = (isWhite) ? WHITE_PIECES[QUEEN_INDEX] : BLACK_PIECES[QUEEN_INDEX];

	// Condition: Promotion was made
	if (toupper(this->_board[srcPos.getRow()][srcPos.getColumn()]->getPieceType()) == WHITE_PIECES[PAWN_INDEX] &&
		destPos.getColumn() == promotionRow)
	{
		// Deleting the Pawn object and creating a Queen object instead of it:
		delete this->_board[srcPos.getRow()][srcPos.getColumn()];
		addPiece(queenToPromote, destPos);
		return true;
	}

	return false;
}


// isThreatened Helper Methods:

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

/*
Checks for check in the King's King positions

Input:
kingPos - the King's current position
possibleEnemyPieces - string of enemy pieces
isWhite - the current player
difference - the check difference

Output:
true - check was found
false - otherwise
*/
bool ChessBoard::kingCheck(const BoardPosition& kingPos, const string& possibleEnemyPieces)
{
	// Inits:
	BoardPosition candidateMove(kingPos.getRow(), kingPos.getColumn());
	int diffArray[POSSIBLE_KING_THREATS_ARRAY_SIZE] = { 0, KING_DIFFERENCE, -KING_DIFFERENCE };
	int i = 0, j = 0;

	// Checking for King threat:
	for (i = 0; i < POSSIBLE_KING_THREATS_ARRAY_SIZE; i++)
	{
		for (j = 0; j < POSSIBLE_KING_THREATS_ARRAY_SIZE; j++)
		{
			// Setting the new position to check for King in:
			candidateMove.setRow(kingPos.getRow() + diffArray[i]);
			candidateMove.setColumn(kingPos.getColumn() + diffArray[j]);

			// Condition: Chess Piece is not out of bounds and exists
			if (!candidateMove.isOutOfBounds() && this->_board[candidateMove.getRow()][candidateMove.getColumn()] != NULL)

				// Condition: Knight threat found
				if (this->_board[candidateMove.getRow()][candidateMove.getColumn()]->getPieceType() == possibleEnemyPieces[KING_INDEX])
					return true;
		}
	}

	return false;
}

