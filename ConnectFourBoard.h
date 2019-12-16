#pragma once
#include "GameBoard.h"
#include <array>
#include <memory>
#include <vector>
#include "BoardPosition.h"
class ConnectFourBoard : public GameBoard {
private:
	enum class Player { EMPTY = 0, RED = 1, YELLOW = -1 };
	std::array<std::array<Player, 7>, 6> mBoard;
	std::vector<std::unique_ptr<GameMove>> mHistory;
	
	Player mCurrentPlayer;
	int mCurrentValue;

	friend class ConnectFourView;

	void CheckForWinner();
	bool InBounds(BoardPosition p) {
		return p.InBounds(mBoard.size(), mBoard[0].size());
	}

	inline Player GetPlayerAtPosition(BoardPosition position) const {
		return mBoard[position.getRow()][position.getCol()];
	}

public:
	ConnectFourBoard();

	// Inherited via GameBoard
	std::vector<std::unique_ptr<GameMove>> GetPossibleMoves() const override;
	void ApplyMove(std::unique_ptr<GameMove> move) override;
	void UndoLastMove() override;
	bool IsFinished() const override;
	int GetValue() const override;
	int GetCurrentPlayer() const override;
	const std::vector<std::unique_ptr<GameMove>>& GetMoveHistory() const override;
};

