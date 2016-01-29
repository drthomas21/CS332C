#include "Piece.h"
#include "Board.h"

namespace game {
	Piece::Piece() {
		this->id = 0;
		this->name = "";
	}
	Piece::Piece(int id, char* name)
		:id(id),
		name(name) {}

	const int Piece::getId() {
		return this->id;
	}

	char* Piece::getName() {
		return this->name;
	}

	void Piece::doAction(int id = 0) {
		Board::getInstance()->setEvent(Board::NOTHING_HAPPENED);
	}
}