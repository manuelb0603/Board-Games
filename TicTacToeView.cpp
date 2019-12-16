#include "TicTacToeView.h"
#include "TicTacToeMove.h"
#include <memory>
using namespace std;

TicTacToeView::TicTacToeView(std::shared_ptr<TicTacToeBoard> board) : mTTTBoard(board) {
}

void TicTacToeView::PrintBoard(std::ostream & s) const {
	s << "- " << " 0 " << " 1 " << " 2 " ;
	for (int x = 0; x <= 2; x++) {
		s << "\n" << x << " ";
		for (int y = 0; y <= 2; y++) {
			TicTacToeBoard::Player space = mTTTBoard->mBoard[x][y];
			s << (space == TicTacToeBoard::Player::EMPTY ? " . " :
				space == TicTacToeBoard::Player::O ? " O " : " X ");
		}
	}
}

std::unique_ptr<GameMove> TicTacToeView::ParseMove(const std::string & move) const {
	istringstream parser{ move };
	char p1, c, p2;
	int row, col;
	parser >> p1 >> row >> c >> col >> p2;
	return std::make_unique<TicTacToeMove>(BoardPosition(row, col));
}

std::string TicTacToeView::GetPlayerString(int player) const {
	return player == 1 ? "O" : "X";
}
