#include "Piece.h"
namespace game {
	Piece::Piece() {
		this->id = 0;
		this->name = "";
		this->pointX = 0;
		this->pointY = 0;
	}
	Piece::Piece(int id, char* name)
		:id(id),
		name(name) {
		this->pointX = 0;
		this->pointY = 0;
	}
	Piece::Piece(int id, char* name, int x, int y)
		: id(id),
		name(name),
		pointX(x),
		pointY(y) {
	}

	const int Piece::getId() {
		return this->id;
	}

	char* Piece::getName() {
		return this->name;
	}

	const int Piece::getPositionX() {
		return this->pointX;
	}

	const int Piece::getPositionY() {
		return this->pointY;
	}

	void Piece::setPositionX(int x) {
		this->pointX = x;
	}

	void Piece::setPositionY(int y) {
		this->pointY = y;
	}

	void Piece::doAction() {
	}
}