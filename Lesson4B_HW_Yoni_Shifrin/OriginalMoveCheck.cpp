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