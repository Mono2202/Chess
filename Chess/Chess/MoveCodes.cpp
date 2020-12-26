#include "MoveCodes.h"

/* MoveCodes Class */

// Static Functions:

/*
Converts MoveCodes enum type to string

Input:
code - the move code

Output:
the code as a string
*/
string MoveCodes::ToString(int code)
{
	switch (code)
	{
		case MoveCodes::VALID_MOVE:			   			return "00"; break;
		case MoveCodes::VALID_CHECK:					return "01"; break;
		case MoveCodes::ERROR_NO_FRIENDLY_PIECE_IN_SRC: return "02"; break;
		case MoveCodes::ERROR_FRIENDLY_PIECE_IN_DEST:	return "03"; break;
		case MoveCodes::ERROR_FRIENDLY_CHECK:			return "04"; break;
		case MoveCodes::ERROR_INVALID_PIECE_INDEX:		return "05"; break;
		case MoveCodes::ERROR_INVALID_MOVE:				return "06"; break;
		case MoveCodes::ERROR_SRC_IS_DEST:				return "07"; break;
		case MoveCodes::VALID_CHECKMATE:				return "08"; break;
		case MoveCodes::VALID_CASTLE:					return "09"; break;
		case MoveCodes::VALID_EN_PASSANT:				return "10"; break;
	}
}