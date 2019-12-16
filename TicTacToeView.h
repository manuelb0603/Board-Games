#pragma once
#include "GameView.h"
#include "TicTacToeBoard.h"
#include <memory>
class TicTacToeView : public GameView {
private:
	std::shared_ptr<TicTacToeBoard> mTTTBoard;
public:
	TicTacToeView(std::shared_ptr<TicTacToeBoard> board);

	// Inherited via GameView
	void PrintBoard(std::ostream &s) const override;
	std::unique_ptr<GameMove> ParseMove(const std::string & move) const override;
	std::string GetPlayerString(int player) const override;
};
