#include "BoardPosition.h"
BoardPosition::BoardPosition() : mRow(0), mCol(0) {
}

BoardPosition::BoardPosition(char row, char col)
	: mRow(row), mCol(col) {
}

char BoardPosition::getRow() const {
	return mRow;
}

char BoardPosition::getCol() const {
	return mCol;
}

BoardPosition::operator std::string() const {
	std::ostringstream os;
	os << "(" << (int)mRow << " " << (int)mCol << ")";
	
	// Return the compiled string.
	return os.str();
}

bool BoardPosition::operator==(BoardPosition rhs) const
{
	return mRow == rhs.getRow() && mCol == rhs.getCol();
}

bool BoardPosition::operator<(BoardPosition rhs)
{
	return mRow < rhs.getRow() || (mRow == rhs.getRow() && mCol < rhs.getCol());
}

BoardPosition BoardPosition::operator+(BoardDirection dir)
{	
	return BoardPosition(mRow + dir.getRow(), mCol + dir.getCol());
}

bool BoardPosition::InBounds(int boardSize)
{
	return mRow >= 0 && mRow < boardSize && mCol >= 0 && mCol < boardSize;
}

bool BoardPosition::InBounds(int rows, int columns)
{
	return mRow >= 0 && mRow < rows && mCol >= 0 && mCol < columns;
}

std::vector<BoardPosition> BoardPosition::GetRectangularPositions(int rows, int columns)
{
	std::vector<BoardPosition> positions;
	for (int r = 0; r <= rows; r++) {
		for (int c = 0; c <= columns; c++) {
			positions.push_back(BoardPosition(r, c));
		}
	}

	return positions;
}
std::istream& operator>>(std::istream & lhs, BoardPosition & rhs)
{
	std::string toParse;
	lhs >> toParse;
	std::istringstream parser{ toParse };
	char para1, comma, para2;
	int row, col;
	parser >> para1 >> row >> comma >> col >> para2;
	rhs.mRow = row;
	rhs.mCol = col;
	return lhs;

}

std::ostream& operator<<(std::ostream & lhs, BoardPosition rhs)
{
	lhs << "(" << (int)rhs.getRow() << ", " << (int)rhs.getCol() << ")";
	return lhs;
}

