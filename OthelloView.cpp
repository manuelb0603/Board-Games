#include "OthelloView.h"
#include "OthelloMove.h"
#include <iostream>
using namespace std;

void OthelloView::PrintBoard(std::ostream & s) const {
	s << "- ";
	for (int i = 0; i < OthelloBoard::BOARD_SIZE; i++) {
		s << " " << i << " ";
	}
	s << endl;

	for (int x = 0; x < OthelloBoard::BOARD_SIZE; x++) {
		s << x << " ";

		for (int y = 0; y < OthelloBoard::BOARD_SIZE; y++) {
			if (mOthelloBoard->OthelloBoard::mBoard[x][y] == (OthelloBoard::Player) 1) {
				s << " B ";
			}
			else if (mOthelloBoard->OthelloBoard::mBoard[x][y] == (OthelloBoard::Player) -1) {
				s << " W ";
			}
			else {
				s << " . ";
			}

		}
		s << endl;
	}
}

std::unique_ptr<GameMove> OthelloView::ParseMove(const std::string & strFormat) const{
	if (strFormat == "pass") {
		return std::make_unique<OthelloMove>(BoardPosition(-1, -1));
	}
	istringstream parser{ strFormat };
	char p1, c, p2;
	int row, col;
	parser >> p1 >> row >> c >> col >> p2;
	return std::make_unique<OthelloMove>(BoardPosition(row, col));
}

std::string OthelloView::GetPlayerString(int player) const
{
	return player == 1 ? "Black" : "White";
}
