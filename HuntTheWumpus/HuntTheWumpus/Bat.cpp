#include "Bat.h"
#include "Board.h"

namespace game {
	namespace pieces {
		Bat::Bat(int i, char* name, int x, int y)
			:ComputerPlayer(i, name, x, y) {

		};
		Bat::Bat(int i, char* name)
			:ComputerPlayer(i, name) {

		}

		void Bat::doAction() {
			int x =0, y=0;
			do {
				x = Board::getRandomNum(), y = Board::getRandomNum();
			} while (!Board::getInstance()->isLocationFree(x, y));

			Board::getInstance()->placePiece(0, x, y);
		}
	}
}