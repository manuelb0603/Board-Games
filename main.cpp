#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"
#include "ConnectFourBoard.h"
#include "ConnectFourView.h"
#include "ConnectFourMove.h"
#include "TicTacToeView.h"
#include "TicTacToeMove.h"
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
	//Games loop
	while (true) {
		// Initialization
		shared_ptr<GameBoard> board; // the state of the game board
		unique_ptr<GameView> v; // a View for outputting the board via operator<<
		string userInput; // a string to hold the user's command choice
		string moveFormat; //what format to use for move choice

		cout << "\nWhat game do you want to play? 1) Othello; 2)Tic Tac Toe; 3) Connect Four; 4) Exit -->";
		getline(cin, userInput);
		if (userInput == "1") {
			auto oBoard = std::make_shared<OelloBoard>();
			v = make_unique<OthelloView>(oBoard);
			board = oBoard;
		}
		else if (userInput == "2") {
			auto tttBoard = std::make_shared<TicTacToeBoard>();
			v = make_unique<TicTacToeView>(tttBoard);
			board = tttBoard;
		}
		else  if (userInput == "3") {
			auto cfBoard = std::make_shared<ConnectFourBoard>();
			v = make_unique<ConnectFourView>(cfBoard);
			board = cfBoard;
		}
		else if (userInput == "4") {
			break;
		}
		moveFormat = userInput == "3" ? "Z" : "(r,c)";


		// Main loop for a game
		do {
		begin: {}
			if (board->IsFinished()) {
				goto end;
			}
			// Print the game board using the OthelloView object
			cout << "Board:\n" << *v << endl;
			// Print all possible moves
			cout << "Possible moves: ";

			auto possibleMoves = board->GetPossibleMoves();
			for (auto itr2 = possibleMoves.begin(); itr2 != possibleMoves.end(); itr2++) {
				cout << (string)**itr2 << " ";
				
			}
			cout << endl;

			// Ask to input a command
			while (true) {
				cout << "Choose a move: 'move " + moveFormat + "', 'undo n' , 'showValue', 'showHistory', 'quit'" << endl;
				getline(cin, userInput);


				// Command loop:
					// move (r,c)
				if (userInput.find("move ") != string::npos) {

					string pos = userInput.substr(5);
					unique_ptr<GameMove> m{ v->ParseMove(pos) };


					//use vector of possible moves to look for a move that equals the user's input
					for (auto itr2 = possibleMoves.begin(); itr2 != possibleMoves.end(); itr2++) {
						if (**itr2 == *m) {
							cout << "Applying the move " << (string)*m << endl;
							
							board->ApplyMove(std::move(m));
							goto begin;
						}
						else if (itr2 + 1 == possibleMoves.end()) {
							cout << "Invalid Move. Enter a new command. " << endl;
						}
					}
				}
				// undo n
				else if (userInput.find("undo ") != string::npos) {
					istringstream parser{ userInput };
					string string;
					int undoCount;
					parser >> string >> undoCount;

					for (int i = 0; i < undoCount; i++) {
						if (board->GetMoveHistory().size() == 0) {
							break;
						}
						board->UndoLastMove();
					}
					break;
				}
				// showValue
				else if (userInput.compare("showValue") == 0) {
					cout << board->GetValue() << endl;
				}
				// showHistory
				else if (userInput.compare("showHistory") == 0) {
					int i = board->GetCurrentPlayer();
					for (auto itr2 = board->GetMoveHistory().rbegin(); itr2 != board->GetMoveHistory().rend(); itr2++) {
						i = i * -1;
						string player = v->GetPlayerString(i);
						cout << player << " - " << (string)**itr2 << endl;
						

					}
				}
				// quit
				else if (userInput.compare("quit") == 0) {
					goto end;
				}
			}
			
		} while (true);
	end: {}
		// Print the final state of game board using the OthelloView object
		cout << "Final Board:\n" << *v << endl;
		int value = board->GetValue();
		if (value > 0) {
			cout << v->GetPlayerString(1) + " wins!" << endl;
		}
		else if (value < 0) {
			cout << v->GetPlayerString(-1) + " wins!"<< endl;
		}
		else {
			cout << "It's a tie!" << endl;
		}
	}

}