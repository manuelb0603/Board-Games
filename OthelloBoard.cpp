#include "OthelloBoard.h"
#include "BoardPosition.h"
#include "BoardDirection.h"
#include "OthelloMove.h"
#include <iostream>
#include <string>
using namespace std;
OthelloBoard::OthelloBoard() : mCurrentValue(0), mCurrentPlayer(Player::BLACK), mBoard { Player::EMPTY } {
	mBoard[3][3] = Player::WHITE;
	mBoard[4][4] = Player::WHITE;
	mBoard[3][4] = Player::BLACK;
	mBoard[4][3] = Player::BLACK;
}



std::vector<std::unique_ptr<GameMove>> OthelloBoard::GetPossibleMoves() const {
	//go through every empty position on the board
	//check for nearby enemy pieces followed by ally
	//if possible move, push back to vector
	BoardDirection dir;
	std::vector<std::unique_ptr<GameMove>> possibleMoves;
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (mBoard[x][y] == Player::EMPTY) {
				unique_ptr<OthelloMove> move = make_unique<OthelloMove>(BoardPosition(x, y));
				for (int i = 0; i <= 7; i++) {
					BoardPosition start = move->mPosition;
					BoardDirection CD = dir.CARDINAL_DIRECTIONS[i];
					while (i <= 7 && InBounds(start + CD) && PositionIsEnemy(start + CD, mCurrentPlayer)) {
						start = start + CD;
						if (InBounds(start + CD) && GetPlayerAtPosition(start + CD) == mCurrentPlayer) {
							possibleMoves.push_back(std::move(move));
							i = 8;
						}
					}
				}
			}
		}
	}
	if (possibleMoves.size() == 0) {
		auto move = make_unique<OthelloMove>();
		possibleMoves.push_back(std::move(move));
	}
	return possibleMoves;
}

void OthelloBoard::ApplyMove(std::unique_ptr<GameMove> m) {
	//look for enemy pieces in every direction
	BoardDirection dir;
	OthelloMove *move = dynamic_cast<OthelloMove*>(m.get());
	for (int x = 0; x <= 7; x++) {
		int enemyFound = 0;
		BoardPosition start = move->mPosition;
		BoardDirection CD = dir.CARDINAL_DIRECTIONS[x];
		//count how many times I find an enemy piece before
		//I find my piece.
		while (!move->IsPass() && InBounds(start + CD) && PositionIsEnemy(start + CD, mCurrentPlayer)) {
			start = start + CD;
			enemyFound++;
			//If I found enemy pieces & they're surrounded, go back & flip
			if (InBounds(start + CD) &&	GetPlayerAtPosition(start + CD) == mCurrentPlayer) {
				BoardPosition start = move->mPosition;
				for (int i = 0; i <= enemyFound; i++) {
					mBoard[start.getRow()][start.getCol()] = mCurrentPlayer;
					start = start + CD;
				}
				mCurrentValue += (int)mCurrentPlayer * (enemyFound * 2);
				//add flip object to position's flipSets and add position to history
				move->AddFlipSet(OthelloMove::FlipSet{ (char)enemyFound, CD });

			}
		}

				
	}
	mCurrentValue += (move->IsPass() ? 0 : (int) mCurrentPlayer);
	mHistory.push_back(std::move(m));
	mCurrentPlayer = (Player) ((int) mCurrentPlayer * -1);
}

void OthelloBoard::UndoLastMove() {
	OthelloMove *move = dynamic_cast<OthelloMove*>(mHistory.back().get());
	BoardPosition pos = move->mPosition;
	//turn position to empty , subtract from board value
		
	if (!move ->IsPass()) {
		mCurrentValue = mCurrentValue + (int)mCurrentPlayer;

		mBoard[pos.getRow()][pos.getCol()] = Player::EMPTY;

		//go through every direction walking that direction n flip times
		for (int i = 0; i < move->mFlips.size(); i++) {
			BoardPosition start = pos;
			for (int j = 0; j < move->mFlips[i].mFlipCount; j++) {
				start = start + move->mFlips[i].mDirection;
				mBoard[start.getRow()][start.getCol()] = (Player)((int)mCurrentPlayer);
				mCurrentValue += (int)mCurrentPlayer * 2;
			}
		}
	}
	mCurrentPlayer = (Player)((int)mCurrentPlayer * -1);
	//delete last element in history
	mHistory.pop_back();
}

bool OthelloBoard::IsFinished() const {
	
	if (mHistory.size() > 1 ) {
		OthelloMove *move = dynamic_cast<OthelloMove*>(mHistory[mHistory.size() - 1].get());
		OthelloMove *move2 = dynamic_cast<OthelloMove*>(mHistory[mHistory.size() - 2].get());
		return (move->IsPass() && move2->IsPass()) || mHistory.size() == mBoard.size() * mBoard[0].size();
	}
	return false;
}