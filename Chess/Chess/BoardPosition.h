#pragma once

#define BOARD_SIZE 8

class BoardPosition
{
public:
	// Constructors:
	BoardPosition();
	BoardPosition(int row, int column);

	// Destructors:
	~BoardPosition();

	// Getters:
	int getRow() const;
	int getColumn() const;

	// Setters:
	void setRow(int row);
	void setColumn(int column);

	// Operators:
	bool operator==(const BoardPosition& otherPos) const;

	// Methods:
	bool isOutOfBounds() const;

private:
	// Fields:
	int _row;
	int _column;
};