#include "ConnectFourView.h"
#include "ConnectFourMove.h"
#include <memory>
using namespace std;


ConnectFourView::ConnectFourView(shared_ptr<ConnectFourBoard> board) : mCFBoard(board) {
}

void ConnectFourView::PrintBoard(std::ostream & s) const {
	// Print column headers.
	for (size_t i = 0; i < mCFBoard->mBoard[0].size(); i++) {
		s << (char)(i + 'A') << ' ';
	}
	s << endl;

	// output the board row by row
	for (size_t i = 0; i < mCFBoard->mBoard.size(); i++) {
		for (size_t j = 0; j < mCFBoard->mBoard[i].size(); j++) {
			ConnectFourBoard::Player space = mCFBoard->mBoard[i][j];
			s << (space == ConnectFourBoard::Player::EMPTY ? '.' : 
				space == ConnectFourBoard::Player::RED ? 'R' : 'Y');
			if (j < 6)
				s << ' ';
		}
		s << endl;
	}
}

unique_ptr<GameMove> ConnectFourView::ParseMove(const string & move) const {
	// Assumes the move is just a single capital letter.
	char letter = move[0];
	int column = letter - 'A';
	return make_unique<ConnectFourMove>(column);
}

string ConnectFourView::GetPlayerString(int player) const {
	return player == 1 ? "Red" : "Yellow";
}
