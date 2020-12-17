#include "ChessBoard.h"

/* ChessBoard Class */

// Constructors:

ChessBoard::ChessBoard(string startingBoard)
{
	// Inits:
	int i = 0;

	// Initializing the board array:
	for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
	{
		// Condition: chess piece to create
		if (startingBoard[i] != '#')
		{
			this->addPiece(startingBoard[i], i);
		}

		// Condition: empty spot
		else
		{
			this->_board.push_back(NULL);
		}
	}
}


// Destructors:

ChessBoard::~ChessBoard()
{
	// Inits:
	int i = 0, j = 0;

	// Clearing the vector:
	for (i = 0; i < BOARD_SIZE; i++)
	{
		// Condition: deleting the current chess piece
		if (this->_board[i] != NULL)
		{
			delete this->_board[i];
		}
	}

	this->_board.clear();
}


// Getters:

std::vector<ChessPiece*> ChessBoard::getBoard() const
{
	return this->_board;
}


// Setters:

void ChessBoard::setBoard(BoardPosition src, BoardPosition dest)
{
	// Switching both positions:
	this->_board[dest.getRow() * BOARD_SIZE + dest.getColumn()] = this->_board[src.getRow() * BOARD_SIZE + src.getColumn()];
	
	// Emptying the source position:
	this->_board[src.getRow() * BOARD_SIZE + src.getRow()] = NULL;
}


// Methods:

string ChessBoard::toString() const
{
	// Inits:
	string boardString = "";
	int i = 0;

	// Building the board string:
	for (i = 0; i < this->_board.size(); i++)
	{
		// Condition: chess piece
		if (this->_board[i] != NULL)
		{
			boardString += this->_board[i]->getPieceType();
		}

		// Condition: empty spot
		else
		{
			boardString += EMPTY_SPACE;
		}
	}

	// Starting player:
	boardString += STARTING_PLAYER;

	return boardString;
}


// Helper Methods:

void ChessBoard::addPiece(char pieceType, int position)
{
	// Creating the proper chess piece:
	switch (toupper(pieceType))
	{
		case 'P': this->_board.push_back(new Pawn(pieceType, position)); break;
		case 'N': this->_board.push_back(new Knight(pieceType, position)); break;
		case 'B': this->_board.push_back(new Bishop(pieceType, position)); break;
		case 'R': this->_board.push_back(new Rook(pieceType, position)); break;
		case 'Q': this->_board.push_back(new Queen(pieceType, position)); break;
		case 'K': this->_board.push_back(new King(pieceType, position)); break;
	}
}