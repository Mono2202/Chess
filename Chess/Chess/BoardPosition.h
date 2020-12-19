#pragma once

#define BOARD_SIZE 8

class BoardPosition
{
public:
	// Constructors:
	BoardPosition();
	BoardPosition(int row, int column);

	// Deconstructors:
	~BoardPosition();

	// Getters:
	int getRow() const;
	int getColumn() const;

	// Setters:
	void setRow(int row);
	void setColumn(int column);

	// Methods:
	bool isOutOfBounds();

private:
	// Fields:
	int _row;
	int _column;
};