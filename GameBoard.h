#pragma once
#include "GameMove.h"
#include <vector>
#include <memory>

/*
Represents the state of a game board, with methods to query and manipulate that state
to support a game-agnostic main application.
*/
class GameBoard {
public:
	/*
	Returns a vector with all possible moves that are valid for the current
	board state. 
	*/
	virtual std::vector<std::unique_ptr<GameMove>> GetPossibleMoves() const = 0;

	/*
	Applies a given move to the board, updating its game state and history
	accordingly. The board takes ownership of the move given. The
	GameMove must an appropriate type for this GameBoard.
	*/
	virtual void ApplyMove(std::unique_ptr<GameMove> move) = 0;

	/*
	Undoes the most recent move applied to the board.
	*/
	virtual void UndoLastMove() = 0;

	/*
	Returns true if the game board is "finished", e.g., if one player has won
	and no more moves should be allowed.
	*/
	virtual bool IsFinished() const = 0;

	/*
	Gets the value of the board, indicating who is winning. Positive indicates player 1,
	negative indicates player 2.
	*/
	virtual int GetValue() const = 0;

	/*
	Gets the player whose turn it is; that is, which player will the next move
	belong to?

	Regardless of how the game represents the current player, this function (and all public functions
	that deal with "players") must return a 1 for the first player, and 2 for the second player.
	*/
	virtual int GetCurrentPlayer() const = 0;

	/*
	Gets a vector of all moves applied to this board. The last move in the vector
	is the most recent move applied to the board.
	*/
	virtual const std::vector<std::unique_ptr<GameMove>>& GetMoveHistory() const = 0;

};
