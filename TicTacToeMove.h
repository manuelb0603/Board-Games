#pragma once
#include "GameMove.h"
#include "BoardPosition.h"
#include "BoardDirection.h"
class TicTacToeMove : public GameMove {
private:
	BoardPosition mPosition;
	friend class TicTacToeBoard;

public:
	// Default constructor: initializes this move as a PASS.
	TicTacToeMove() : mPosition(-1, -1) {

	}
	/*
	1-parameter constructor: initializes this move with the given position.
	*/
	TicTacToeMove(BoardPosition p) : mPosition(p) {

	}

	// Inherited via GameMove
	virtual operator std::string() const override;
	virtual bool operator==(const GameMove & rhs) const override;
};