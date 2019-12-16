#pragma once
#include "GameMove.h"
class ConnectFourMove : public GameMove {
private: 
	int mColumn;
	friend class ConnectFourBoard;
public:
	ConnectFourMove(int column);

	// Inherited via GameMove
	virtual operator std::string() const override;
	virtual bool operator==(const GameMove & rhs) const override;
};

