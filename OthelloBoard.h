#ifndef __OTHELLOBOARD_H
#define __OTHELLOBOARD_H
#include "GameBoard.h"
#include "BoardPosition.h"
#include <array>
#include <memory>
#include <vector>
//Manuel Beltran
//016517551

/*
An OthelloBoard encapsulates data needed to represent a single game of Othello.
This includes the state of the board, tracking the current player, and keeping
a history of moves on the board.
*/
class OthelloBoard : public GameBoard {
public:
	// This enum represents all three values that a board position can take in Othello:
	// blank, black, or white.
	enum class Player : char {
		EMPTY = 0,
		BLACK = 1,
		WHITE = -1
	};

	// Constructs a new board with the default player locations and no move history.
	OthelloBoard();
	
	/*
	Returns a vector with all possible moves on the current board state for
	the current player. The moves should be ordered based first on row, then on
	column. Example ordering: (0, 5) (0, 7) (1, 0) (2, 0) (2, 2) (7, 7)
	You cannot use a sorting method to achieve this ordering.

	If there are no legal moves for the current player, then a single "pass"
	OthelloMove should be the only element of the returned vector.
	*/
	std::vector<std::unique_ptr<GameMove>> GetPossibleMoves() const override;

	/*
	Applies a valid move to the board, updating the board state accordingly.
	You may assume that this move is valid, and is consistent with the list
	of possible moves returned by GetAllMoves. Takes ownership of this move
	by placing it in the move history vector.
	*/
	void ApplyMove(std::unique_ptr<GameMove> m) override;

	/*
	Undoes the last move applied to the board, restoring it to the state it was
	in prior to the most recent move, and removing that move from the move history.
	*/
	void UndoLastMove() override;

	/*
	Gets the current player. (The next player to make a move.)
	*/
	inline int GetCurrentPlayer() const override {
		return (int) mCurrentPlayer; 
	}

	bool IsFinished() const override;
	/*
	Accesses the board's vector of applied moves, in FILO order. (The most-recent
	move is last in the vector.)
	*/
	inline const std::vector<std::unique_ptr<GameMove>> &GetMoveHistory() const override {
		return mHistory;
	}

	/*
	Gets a value indicating who is winning the game, and by how many pieces:
	positive for Black, negative for White.
	*/
	inline int GetValue() const override {
		return mCurrentValue;
	}

	

	static const int BOARD_SIZE = 8;

	
private:
	// OthelloView needs access to mBoard for printing
	friend class OthelloView;

	// The state of the game board, as in project 1.
	std::array<std::array<Player, BOARD_SIZE>, BOARD_SIZE> mBoard;

	// The next player to move (the next move in ApplyMove is this player's)
	Player mCurrentPlayer;

	// A history of moves applied to the board.
	std::vector<std::unique_ptr<GameMove>> mHistory;

	// The current value of the board. Updates after every apply/undo.
	int mCurrentValue;

	// Returns true if the given position is in the bounds of the board.
	inline bool InBounds(BoardPosition p) const { 
		return p.InBounds(BOARD_SIZE);
	}

	// Returns true if the given position contains the enemy of the given player.
	inline bool PositionIsEnemy(BoardPosition position, Player p) const {
		Player atPosition = GetPlayerAtPosition(position);
		return atPosition != Player::EMPTY && atPosition != p;
	}

	// Gets the player at the given position on the board, assuming it is in bounds.
	inline Player GetPlayerAtPosition(BoardPosition position) const {
		return mBoard[position.getRow()][ position.getCol()];
	}
};
#endif