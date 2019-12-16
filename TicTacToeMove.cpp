#include "TicTacToeMove.h"
#include <string>
using namespace std;

TicTacToeMove::operator std::string() const {
	std::ostringstream os;

	os << "(" << (int)mPosition.getRow() << "," << (int)mPosition.getCol() << ")";
	// Return the compiled string.
	return os.str();
}

bool TicTacToeMove::operator==(const GameMove & rhs) const {
	// Downcast and compare columns.
	const TicTacToeMove &m = dynamic_cast<const TicTacToeMove&>(rhs);
	return mPosition == m.mPosition;
}
