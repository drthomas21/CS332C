#include "Bat.h"
#include "Board.h"

namespace game {
	namespace pieces {
		Bat::Bat(int i, char* name)
			:Piece(i, name) {

		}

		void Bat::doAction(int id = 0) {
			int x =0, y=0;
			do {
				x = Board::getRandomNum(), y = Board::getRandomNum();
			} while (!Board::getInstance()->isLocationFree(x, y));

			Board::getInstance()->placePiece(id, x, y);
			Board::getInstance()->setEvent(Board::TELEPORTED);
		}
	}
}