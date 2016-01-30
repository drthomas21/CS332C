#include "Piece.h"
#include "Board.h"
#include <string>

namespace game {
	Piece::Piece() {
		this->id = 0;
		this->name = "";
	}
	Piece::Piece(int id, std::string name)
		:id(id),
		name(name) {}

	const int Piece::getId() {
		return this->id;
	}

	std::string const Piece::getName() {
		return this->name;
	}

	void Piece::doAction(int id = 0) {
		Board::getInstance()->setEvent(Board::NOTHING_HAPPENED);
	}

	char* const Piece::makeSound() {
		return "";
	}
}