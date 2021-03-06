#pragma once

#include <iostream>

using std::string;

class MoveCodes
{
public:
	// Move Codes Enum:
	enum CODES{
		VALID_MOVE,
		VALID_CHECK,
		ERROR_NO_FRIENDLY_PIECE_IN_SRC,
		ERROR_FRIENDLY_PIECE_IN_DEST,
		ERROR_FRIENDLY_CHECK,
		ERROR_INVALID_PIECE_INDEX,
		ERROR_INVALID_MOVE,
		ERROR_SRC_IS_DEST,
		VALID_CHECKMATE,
		VALID_CASTLE,
		VALID_EN_PASSANT,
		VALID_PROMOTION
	};

	// Static Functions:
	static string ToString(int code);
};



