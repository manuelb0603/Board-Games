#include "ConnectFourBoard.h"
#include "ConnectFourMove.h"
#include "BoardDirection.h"
#include "BoardPosition.h"
using namespace std;

void ConnectFourBoard::CheckForWinner() {
	// It would be most efficient if we only checked squares adjacent to the most 
	// recent move. But I'm lazy. We'll check every possible direction of four squares
	// in a row. Only the current player can be the winner, so we'll only look for those squares.
	for (auto pos : BoardPosition::GetRectangularPositions(mBoard.size(), mBoard[0].size())) {
		for (auto dir : BoardDirection::CARDINAL_DIRECTIONS) {
			// Having chosen a square and a direction, walk up to 4 steps in that direction.
			BoardPosition current = pos;
			bool fourInARow = true;

			for (int steps = 0; steps < 4; steps++) {
				if (!InBounds(current) || mCurrentPlayer != GetPlayerAtPosition(current)) {
					// We either walked out of bounds, or found a square that doesn't match current player.
					fourInARow = false;
					break;
				}
				current = current + dir;
			}

			// If we matched four in a row, set the current value to the current player, indicating
			// a winner.
			if (fourInARow) {
				mCurrentValue = static_cast<int>(mCurrentPlayer);
				return;
			}
		}
	}
}

ConnectFourBoard::ConnectFourBoard() : mBoard({Player::EMPTY}), mCurrentPlayer(Player::RED), mCurrentValue(0) {
}

vector<unique_ptr<GameMove>> ConnectFourBoard::GetPossibleMoves() const {
	vector<unique_ptr<GameMove>> moves;

	// Each column that has an empty spot at the top is a valid column.
	for (int c = 0; c < mBoard[0].size(); c++) {
		if (mBoard[0][c] == Player::EMPTY) {
			moves.push_back(std::make_unique<ConnectFourMove>(c));
		}
	}
	
	return moves;
}

void ConnectFourBoard::ApplyMove(unique_ptr<GameMove> move) {
	// Borrow a downcast of the given move.
	ConnectFourMove *m = dynamic_cast<ConnectFourMove*>(move.get());

	// Find the first row from the bottom that is empty in the given move's column.
	for (int r = mBoard.size() - 1; r >= 0; r--) {
		if (mBoard[r][m->mColumn] == Player::EMPTY) {
			mBoard[r][m->mColumn] = mCurrentPlayer;
			break;
		}
	}
	CheckForWinner();

	// Push the move into the history vector, switch sides.
	mHistory.push_back(std::move(move));
	mCurrentPlayer = mCurrentPlayer == Player::RED ? Player::YELLOW : Player::RED;
}

void ConnectFourBoard::UndoLastMove() {
	// Borrow a downcast of the last applied move.
	ConnectFourMove *m = dynamic_cast<ConnectFourMove*>(mHistory.back().get());

	// Remove the topmost piece in the move's column.
	for (int r = 0; r < mBoard.size(); r++) {
		if (mBoard[r][m->mColumn] != Player::EMPTY) {
			mBoard[r][m->mColumn] = Player::EMPTY;
			break;
		}
	}

	// Remove and delete the last move.
	mHistory.pop_back(); 
	mCurrentValue = 0;
	mCurrentPlayer = mCurrentPlayer == Player::RED ? Player::YELLOW : Player::RED;
}

bool ConnectFourBoard::IsFinished() const {
	// mCurrentValue will be non-zero iff there is a winner.
	return mCurrentValue != 0 || mHistory.size() == mBoard.size() * mBoard[0].size();
}

// Reminder: positive = player 1 wins; negative = player 2 wins.
int ConnectFourBoard::GetValue() const {
	return mCurrentValue;
}

// Reminder: this function MUST return either 1 or 2.
int ConnectFourBoard::GetCurrentPlayer() const {
	return mCurrentPlayer == Player::RED ? 1 : 2;
	//return (int)mCurrentPlayer;
}

const vector<unique_ptr<GameMove>>& ConnectFourBoard::GetMoveHistory() const {
	return mHistory;
}
