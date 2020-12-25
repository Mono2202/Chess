#include "BoardPosition.h"

/* BoardPosition Class */

// Constructors:

BoardPosition::BoardPosition()
{
	this->_row = 0;
	this->_column = 0;
}

BoardPosition::BoardPosition(int row, int column)
{
	this->_row = row;
	this->_column = column;
}


// Destructors:

BoardPosition::~BoardPosition()
{
	this->_row = 0;
	this->_column = 0;
}


// Getters:

int BoardPosition::getRow() const
{
	return this->_row;
}

int BoardPosition::getColumn() const
{
	return this->_column;
}


// Setters:

void BoardPosition::setRow(int row)
{
	this->_row = row;
}

void BoardPosition::setColumn(int column)
{
	this->_column = column;
}


// Operators:

bool BoardPosition::operator==(const BoardPosition& otherPos)
{
	return this->_row == otherPos._row && this->_column == otherPos._column;
}


// Methods:

bool BoardPosition::isOutOfBounds()
{
	return this->_row < 0 || this->_row >= BOARD_SIZE || this->_column < 0 || this->_column >= BOARD_SIZE;
}