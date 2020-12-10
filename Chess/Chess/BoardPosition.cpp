#include "BoardPosition.h"

/* BoardPosition Class */

// Constructors:

BoardPosition::BoardPosition(int row, int column)
{
	this->_row = row;
	this->_column = column;
}


// Deconstructors:

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