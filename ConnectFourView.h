#pragma once
#include "GameView.h"
#include "ConnectFourBoard.h"
#include <memory>
class ConnectFourView : public GameView {
private:
	std::shared_ptr<ConnectFourBoard> mCFBoard;
public:
	ConnectFourView(std::shared_ptr<ConnectFourBoard> board);

	// Inherited via GameView
	void PrintBoard(std::ostream &s) const override;
	std::unique_ptr<GameMove> ParseMove(const std::string & move) const override;
	std::string GetPlayerString(int player) const override;
};

