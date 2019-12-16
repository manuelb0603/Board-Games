#include "OthelloMove.h"
bool OthelloMove::operator==(const GameMove & rhs) const {
	const OthelloMove &m = dynamic_cast<const OthelloMove&>(rhs);
	return mPosition == m.mPosition;
}

OthelloMove::operator std::string() const {
	std::ostringstream os;
	if (mPosition.getRow() == -1 && mPosition.getCol() == -1) {
		os << "pass";
	}
	else {
		os << "(" << (int)mPosition.getRow() << "," << (int)mPosition.getCol() << ")";
	}
	// Return the compiled string.
	return os.str();
}