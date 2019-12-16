#pragma once
#include <array>
class BoardDirection {
private:
	char mRowChange;
	char mColChange;
public:
	static std::array<BoardDirection, 8> CARDINAL_DIRECTIONS;

	//Constructor
	BoardDirection();
	BoardDirection(char RowChange, char ColChange);

	//Acesscors
	inline char getRow() const { return mRowChange; }
	inline char getCol() const { return mColChange; }
};
