#include "Pipe.h"
#include "ChessBoard.h"
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::string;

void main()
{
	// Creating the board:
	ChessBoard board("rrrkrrrrrrrrrrrr################################RRRRRRRRRRRRKRRR0");

	// Pipe connection:
	Pipe p;
	bool isConnect = p.connect();

	// Pipe connection error handling:
	string ans = "";
	while (!isConnect)
	{
		// User instructions:
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		// Condition: trying to connect to frontend again
		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
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
	char msgToGraphics[1024];
	strcpy_s(msgToGraphics, "rrrkrrrrrrrrrrrr################################RRRRRRRRRRRRKRRR0"); // TODO: Change to toString function from ChessBoard
	p.sendMessageToGraphics(msgToGraphics); 

	// Getting the message from the frontend:
	string msgFromGraphics = p.getMessageFromGraphics();

	// Inits:
	BoardPosition srcPos;
	BoardPosition destPos;
	string moveCode = "";
	bool isWhite = true;

	// Game loop:
	while (msgFromGraphics != "quit")
	{
		// Printing the board:
		board.printBoard();

		// Calculating the current board positions:
		srcPos.setRow(BOARD_SIZE - (msgFromGraphics[1] - '0'));
		srcPos.setColumn(msgFromGraphics[0] - 'a');
		destPos.setRow(BOARD_SIZE - (msgFromGraphics[3] - '0'));
		destPos.setColumn(msgFromGraphics[2] - 'a');

		// Getting the Move Code:
		moveCode = board.moveCheck(srcPos, destPos, isWhite);

		// Condition: valid move, update board and current player
		if (moveCode == "0" || moveCode == "1" || moveCode == "8") // TODO: Change to 1 condition
		{
			board.updateBoard(srcPos, destPos);
			isWhite = !isWhite;
		}

		// Building the message to the frontend:
		msgToGraphics[0] = moveCode[0];
		msgToGraphics[1] = 0;

		// Sending the Move Code to the frontend:		
		p.sendMessageToGraphics(msgToGraphics);

		// Getting the message from the frontend:
		msgFromGraphics = p.getMessageFromGraphics();
	}

	// Closing the pipe:
	p.close();
}

// TODO: #define EVERYTHING