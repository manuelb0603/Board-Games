#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "BoardDirection.h"
class BoardPosition {
private:
	char mRow;
	char mCol;

public:
	//Constructor
	BoardPosition();
	BoardPosition(char Row, char Col);

	//Accessors
	char getRow() const;
	char getCol() const;

	//Operators
	operator std::string() const;

	friend std::istream& operator>>(std::istream &lhs, BoardPosition& rhs);
	bool operator==(BoardPosition rhs) const;
	bool operator<(BoardPosition rhs);

	BoardPosition operator+(BoardDirection rhs);

	//member methods
	bool InBounds(int boardSize);
	bool InBounds(int rows, int columns);
	static std::vector<BoardPosition> GetRectangularPositions(int rows, int columns);

};

std::ostream& operator<<(std::ostream &lhs, BoardPosition rhs);