#pragma once

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

private:
	// Fields:
	int _row;
	int _column;
};