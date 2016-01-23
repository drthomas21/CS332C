#include "Board.h"
namespace game {
	Board Board::getInstance(int s) {
		if (Board::Instance) {
			Board::Instance = Board(s);
		}

		return Board::Instance;
	}
	bool Board::isValidLocation(int x, int y) {
		return x >= 0 && x < this->size && y >= 0 && y < this->size;
	}
	int Board::moveNorth(int id) {

	}
	int Board::moveSouth(int id) {

	}
	int Board::moveEast(int id) {

	}
	int Board::moveWest(int id) {

	}

	Board::Board(int size)
		:size(size) {
		this->size = size;
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++) {
				this->slots[i][j] = this->EMPTY_SPACE;
			}
		}

		//Set traps

		//Set wampus

		//Set Arrow

		//Set Player
	}

	int Board::move(int direction, int id) {

	}

	int Board::getSize() {
		return this->size;
	}
}