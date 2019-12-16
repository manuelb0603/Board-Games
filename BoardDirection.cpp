#include "BoardDirection.h"
std::array<BoardDirection, 8> BoardDirection::CARDINAL_DIRECTIONS = { BoardDirection(-1,-1),
	BoardDirection(-1,0), BoardDirection(-1,1), BoardDirection(0,-1), BoardDirection(0,1),
	BoardDirection(1,-1), BoardDirection(1,0), BoardDirection(1,1) };


BoardDirection::BoardDirection() : mRowChange(0), mColChange(0) {
	}

BoardDirection::BoardDirection(char rowChange, char colChange)
	: mRowChange(rowChange), mColChange(colChange) {
}

