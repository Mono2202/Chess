#include "ChessBoard.h"
#include "Rook.h"
#include "King.h"

/* ChessBoard Class */

// Constructors:

ChessBoard::ChessBoard(string startingBoard)
{
	// Inits:
	int i = 0, j = 0;

	// Initializing the board array:
	for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			// Condition: chess piece to create
			if (startingBoard[i * BOARD_SIZE + j] != EMPTY_SPACE)
			{
				this->addPiece(startingBoard[i * BOARD_SIZE + j], i, j);
			}

			// Condition: empty spot
			else
			{
				this->_board[i][j] = NULL;
			}
		}
	}
}


// Destructors:

ChessBoard::~ChessBoard()
{
	// Inits:
	int i = 0, j = 0;

	// Clearing the board:
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			// Condition: deleting the current chess piece
			if (this->_board[i] != NULL)
			{
				delete this->_board[i][j];
			}
		}
	}
}


// General Methods:

string ChessBoard::toString() const
{
	// Inits:
	string boardString = "";
	int i = 0, j = 0;

	// Building the board string:
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			// Condition: chess piece
			if (this->_board[i][j] != NULL)
			{
				boardString += this->_board[i][j]->getPieceType();
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
	int i = 0, j = 0;

	// Printing the board as a 2D-array:
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			// Condition: chess piece
			if (this->_board[i][j] != NULL)
				std::cout << this->_board[i][j]->getPieceType() << " ";

			// Condition: empty spot
			else
				std::cout << "# ";
		}

		// New line:
		std::cout << std::endl;
	}
}


// Chess Methods:

void ChessBoard::updateBoard(int srcRow, int srcCol, int destRow, int destCol)
{
	// Condition: deleting the chess piece
	if (this->_board[destRow][destCol] != NULL)
		delete this->_board[destRow][destCol];

	// Switching both positions:
	this->_board[destRow][destCol] = this->_board[srcRow][srcCol];

	// Emptying the source position:
	this->_board[srcRow][srcCol] = NULL;
}


// Helper Methods:

void ChessBoard::addPiece(char pieceType, int row, int column)
{
	// Creating the proper chess piece:
	switch (toupper(pieceType))
	{
		//case 'P': this->_board.push_back(new Pawn(pieceType, position)); break;
		//case 'N': this->_board.push_back(new Knight(pieceType, position)); break;
		//case 'B': this->_board.push_back(new Bishop(pieceType, position)); break;
		case 'R': this->_board[row][column] = new Rook(pieceType); break;
		//case 'Q': this->_board.push_back(new Queen(pieceType, position)); break;
		case 'K': this->_board[row][column] = new King(pieceType); break;
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
