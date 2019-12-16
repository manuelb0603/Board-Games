#include "GameBoard.h"
#include <array>
#include <memory>
#include <vector>
#include "BoardPosition.h"
//Manuel Beltran
//016517551

class TicTacToeBoard : public GameBoard {
private:
	enum class Player { EMPTY = 0, O = 1, X = -1 };
	std::array<std::array<Player, 3>, 3> mBoard;
	std::vector<std::unique_ptr<GameMove>> mHistory;

	Player mCurrentPlayer;
	int mCurrentValue;

	friend class TicTacToeView;

	void CheckForWinner();
	bool InBounds(BoardPosition p) {
		return p.InBounds(mBoard.size(), mBoard[0].size());
	}

	inline Player GetPlayerAtPosition(BoardPosition position) const {
		return mBoard[position.getRow()][position.getCol()];
	}

public:
	TicTacToeBoard();

	// Inherited via GameBoard
	std::vector<std::unique_ptr<GameMove>> GetPossibleMoves() const override;
	void ApplyMove(std::unique_ptr<GameMove> move) override;
	void UndoLastMove() override;
	bool IsFinished() const override;
	int GetValue() const override;
	int GetCurrentPlayer() const override;
	const std::vector<std::unique_ptr<GameMove>>& GetMoveHistory() const override;
};