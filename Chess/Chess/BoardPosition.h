#pragma once

class BoardPosition
{
public:
	// Constructors:
	BoardPosition(int row, int column);

	// Deconstructors:
	~BoardPosition();

	// Getters:
	int getRow() const;
	int getColumn() const;

private:
	// Fields:
	int _row;
	int _column;
};