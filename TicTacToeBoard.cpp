#include "TicTacToeBoard.h"
#include "TicTacToeMove.h"
#include "BoardDirection.h"
using namespace std;

void TicTacToeBoard::CheckForWinner() {
	// Check every possible direction of three squares
	// in a row. Only the current player can be the winner, so only look for those squares.
	for (auto pos : BoardPosition::GetRectangularPositions(mBoard.size(), mBoard[0].size())) {
		for (auto dir : BoardDirection::CARDINAL_DIRECTIONS) {
			// Having chosen a square and a direction, walk up to 3 steps in that direction.
			BoardPosition current = pos;
			bool threeInARow = true;

			for (int steps = 0; steps < 3; steps++) {
				if (!InBounds(current) || mCurrentPlayer != GetPlayerAtPosition(current)) {
					// Either walk out of bounds, or find a square that doesn't match current player.
					threeInARow = false;
					break;
				}
				current = current + dir;
			}

			// If matched three in a row is matched, set the current value to the current player, indicating
			// a winner.
			if (threeInARow) {
				mCurrentValue = static_cast<int>(mCurrentPlayer);
				return;
			}
		}
	}
}

TicTacToeBoard::TicTacToeBoard() : mBoard({ Player::EMPTY }), mCurrentPlayer(Player::X), mCurrentValue(0) {
}

vector<unique_ptr<GameMove>> TicTacToeBoard::GetPossibleMoves() const {
	vector<unique_ptr<GameMove>> moves;

	// Go to each spot and see if it's empty
	for (int x = 0; x < mBoard[0].size(); x++) {
		for (int y = 0; y < mBoard[0].size(); y++) {
			if (mBoard[x][y] == Player::EMPTY) {
				moves.push_back(std::make_unique<TicTacToeMove>(BoardPosition{ (char)x, (char)y }));
			}
		}
	}

	return moves;
}

void TicTacToeBoard::ApplyMove(unique_ptr<GameMove> move) {
	// Borrow a downcast of the given move.
	TicTacToeMove *m = dynamic_cast<TicTacToeMove*>(move.get());

	// Place piece on spot
	mBoard[m->mPosition.getRow()][m->mPosition.getCol()] = mCurrentPlayer;
	CheckForWinner();

	// Push the move into the history vector, switch sides.
	mHistory.push_back(std::move(move));
	mCurrentPlayer = mCurrentPlayer == Player::O ? Player::X : Player::O;
}

void TicTacToeBoard::UndoLastMove() {
	// Borrow a downcast of the last applied move.
	TicTacToeMove *m = dynamic_cast<TicTacToeMove*>(mHistory.back().get());

	// Remove the last piece in placed
	mBoard[m->mPosition.getRow()][m->mPosition.getCol()] = Player::EMPTY;

	// Remove and delete the last move.
	mHistory.pop_back();
	mCurrentValue = 0;
	mCurrentPlayer = mCurrentPlayer == Player::O ? Player::X : Player::O;
}

bool TicTacToeBoard::IsFinished() const {
	// mCurrentValue will be non-zero iff there is a winner.
	return mCurrentValue != 0 || mHistory.size() == mBoard.size() * mBoard[0].size();
}

// Reminder: positive = player O wins; negative = player X wins.
int TicTacToeBoard::GetValue() const {
	return mCurrentValue;
}

int TicTacToeBoard::GetCurrentPlayer() const {
	return (int)mCurrentPlayer;
}

const vector<unique_ptr<GameMove>>& TicTacToeBoard::GetMoveHistory() const {
	return mHistory;
}

