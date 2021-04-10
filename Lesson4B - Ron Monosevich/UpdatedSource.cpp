// Includes:
#include "Pipe.h"
#include "ChessBoard.h"
#include <iostream>
#include <thread>
#include <algorithm>

// Using:
using std::cout;
using std::endl;
using std::string;

// Pipe Defines:
#define STARTING_BOARD_MESSAGE_SIZE 66
#define MOVE_CODE_MESSAGE_SIZE 2
#define TRY_CONNECTION_AGAIN 0
#define PIPE_CONNECTION_DELAY 5000
#define QUIT_GAME_LOOP "quit"

// Position Defines:
#define SRC_COLUMN 0
#define SRC_ROW 1
#define DEST_COLUMN 2
#define DEST_ROW 3
#define ZERO_ASCII '0'
#define LOWERCASE_A_ASCII 'a'

// Constants:
const std::string VALID_MOVES_ARRAY[] = { MoveCodes::ToString(MoveCodes::CODES::VALID_MOVE),
			MoveCodes::ToString(MoveCodes::CODES::VALID_CHECK),
			MoveCodes::ToString(MoveCodes::CODES::VALID_CHECKMATE),
			MoveCodes::ToString(MoveCodes::CODES::VALID_CASTLE),
			MoveCodes::ToString(MoveCodes::CODES::VALID_EN_PASSANT),
			MoveCodes::ToString(MoveCodes::CODES::VALID_PROMOTION) };

// Function Declarations:
bool connectPipe(Pipe& pipe);

void main()
{
	// Inits:
	char startingBoard[STARTING_BOARD_MESSAGE_SIZE] = "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0";
	char msgToPipe[MOVE_CODE_MESSAGE_SIZE] = { 0 };
	string msgFromPipe = "";
	string moveCode = "";
	ChessBoard board(startingBoard);
	BoardPosition srcPos;
	BoardPosition destPos;
	Pipe pipe;
	bool isConnected = false;
	bool isWhite = true;

	// Connecting with the pipe:
	isConnected = connectPipe(pipe);

	// Sending the starting board message to the frontend:
	pipe.sendMessageToGraphics(msgToPipe);

	// Game loop:
	while ((msgFromPipe = pipe.getMessageFromGraphics()) != QUIT_GAME_LOOP)
	{
		// Printing the board:
		board.printBoard();

		// Calculating the current board positions:
		srcPos.setRow(BOARD_SIZE - (msgFromPipe[SRC_ROW] - ZERO_ASCII));
		srcPos.setColumn(msgFromPipe[SRC_COLUMN] - LOWERCASE_A_ASCII);
		destPos.setRow(BOARD_SIZE - (msgFromPipe[DEST_ROW] - ZERO_ASCII));
		destPos.setColumn(msgFromPipe[DEST_COLUMN] - LOWERCASE_A_ASCII);

		// Getting the Move Code:
		moveCode = board.moveCheck(srcPos, destPos, isWhite);

		// Condition: valid move, update board and current player
		if (std::find(std::begin(VALID_MOVES_ARRAY), std::end(VALID_MOVES_ARRAY), moveCode))
		{
			// Updating the chess board:
			board.updateBoard(srcPos, destPos);

			// Updating the current player:
			isWhite = !isWhite;
		}

		// Building the message to the frontend:
		strncpy(msgToPipe, moveCode.c_str(), MOVE_CODE_MESSAGE_SIZE);

		// Sending the Move Code to the frontend:	
		pipe.sendMessageToGraphics(msgToPipe);
	}

	// Closing the pipe:
	pipe.close();
}

/*
Connecting the pipe to the frontend
Input : pipe  - the pipe object
Output: true  - the pipe is connected to the frontend
		false - otherwise
*/
bool connectPipe(Pipe& pipe)
{
	// Inits:
	bool isConnected = pipe.connect();
	int userChoice = 0;

	// Stopping Condition: pipe is connected
	while (!isConnected)
	{
		// User instructions:
		cout << "ERROR: Unable to Connect Pipe to Frontend..." << endl;
		cout << "0. Try Again" << endl;
		cout << "1. Exit" << endl;

		// Getting the user's choice:
		std::cin >> userChoice;

		// Condition: trying to connect pipe to frontend again
		if (userChoice == TRY_CONNECTION_AGAIN)
		{
			cout << endl << "Trying to Reconnect..." << endl;
			Sleep(PIPE_CONNECTION_DELAY);
			isConnected = pipe.connect();
		}

		// Condition: exiting program
		else
		{
			pipe.close();
			return false;
		}
	}

	// Condition: pipe connected successfully
	return true;
}
