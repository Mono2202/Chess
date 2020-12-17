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
string ToString(int code)
{
	switch (code)
	{
		case MoveCodes::VALID_MOVE:			   			return "0";
		case MoveCodes::VALID_CHECK:					return "1";
		case MoveCodes::ERROR_NO_FRIENDLY_PIECE_IN_SRC: return "2";
		case MoveCodes::ERROR_FRIENDLY_PIECE_IN_DEST:	return "3";
		case MoveCodes::ERROR_FRIENDLY_CHECK:			return "4";
		case MoveCodes::ERROR_INVALID_INDEX:			return "5";
		case MoveCodes::ERROR_INVALID_MOVE:				return "6";
		case MoveCodes::ERROR_SRC_IS_DEST:				return "7";
		case MoveCodes::VALID_CHECKMATE:				return "8";
	}
}