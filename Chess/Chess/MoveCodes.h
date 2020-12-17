#pragma once

#include <iostream>

using std::string;

class MoveCodes
{
public:
	// Move Codes Enum:
	enum {
		VALID_MOVE,
		VALID_CHECK,
		ERROR_NO_FRIENDLY_PIECE_IN_SRC,
		ERROR_FRIENDLY_PIECE_IN_DEST,
		ERROR_FRIENDLY_CHECK,
		ERROR_INVALID_INDEX,
		ERROR_INVALID_MOVE,
		ERROR_SRC_IS_DEST,
		VALID_CHECKMATE
	};

	// Static Functions:
	static string ToString(int code);
};



