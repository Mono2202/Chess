#include "Pipe.h"
#include "ChessBoard.h"
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::string;

#define MESSAGE_SIZE 1024
#define TRY_CONNECTION_AGAIN "0"
#define FIVE_SECONDS 5000
#define QUIT_GAME_LOOP "quit"

#define SRC_COLUMN 0
#define SRC_ROW 1
#define DEST_COLUMN 2
#define DEST_ROW 3

#define ZERO_ASCII '0'
#define LOWERCASE_A_ASCII 'a'

#define MOVE_CODE_INDEX 0
#define NULL_TERMINATOR_INDEX 1

void main()
{
	// Starting board string:
	char startingBoard[MESSAGE_SIZE] = "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0";

	// Creating the board:
	ChessBoard board(startingBoard);

	// Pipe connection:
	Pipe p;
	bool isConnect = p.connect();

	// Pipe connection error handling:
	string userChoice = "";
	while (!isConnect)
	{
		// User instructions:
		cout << "Unable to connect to frontend..." << endl;
		cout << "0. Try Again" << endl;
		cout << "1. Exit" << endl;
		std::cin >> userChoice;

		// Condition: trying to connect to frontend again
		if (userChoice == TRY_CONNECTION_AGAIN)
		{
			cout << endl << "Trying to Reconnect..." << endl;
			Sleep(FIVE_SECONDS);
			isConnect = p.connect();
		}

		// Condition: exiting program
		else
		{
			p.close();
			return;
		}
	}

	// Sending the starting board message to the frontend:
	char msgToGraphics[MESSAGE_SIZE];
	strcpy_s(msgToGraphics, startingBoard);
	p.sendMessageToGraphics(msgToGraphics); 

	// Getting the message from the frontend:
	string msgFromGraphics = p.getMessageFromGraphics();

	// Inits:
	BoardPosition srcPos;
	BoardPosition destPos;
	string moveCode = "";
	bool isWhite = true;

	// Game loop:
	while (msgFromGraphics != QUIT_GAME_LOOP)
	{
		// Printing the board:
		board.printBoard();

		// Calculating the current board positions:
		srcPos.setRow(BOARD_SIZE - (msgFromGraphics[SRC_ROW] - ZERO_ASCII));
		srcPos.setColumn(msgFromGraphics[SRC_COLUMN] - LOWERCASE_A_ASCII);
		destPos.setRow(BOARD_SIZE - (msgFromGraphics[DEST_ROW] - ZERO_ASCII));
		destPos.setColumn(msgFromGraphics[DEST_COLUMN] - LOWERCASE_A_ASCII);

		// Getting the Move Code:
		moveCode = board.moveCheck(srcPos, destPos, isWhite);

		// Condition: valid move, update board and current player
		if (moveCode == MoveCodes::ToString(MoveCodes::CODES::VALID_MOVE) ||
			moveCode == MoveCodes::ToString(MoveCodes::CODES::VALID_CHECK) ||
			moveCode == MoveCodes::ToString(MoveCodes::CODES::VALID_CHECKMATE))
		{
			board.updateBoard(srcPos, destPos);
			isWhite = !isWhite;
		}

		// Building the message to the frontend:
		msgToGraphics[MOVE_CODE_INDEX] = moveCode[MOVE_CODE_INDEX];
		msgToGraphics[NULL_TERMINATOR_INDEX] = 0;

		// Sending the Move Code to the frontend:		
		p.sendMessageToGraphics(msgToGraphics);

		// Getting the message from the frontend:
		msgFromGraphics = p.getMessageFromGraphics();
	}

	// Closing the pipe:
	p.close();
}