#include "Wumpus.h"
#include "Board.h"

namespace game {
	namespace pieces {
		Wumpus::Wumpus(int i, char* name)
			:Piece(i, name) {

		}

		void Wumpus::doAction(int id = 0) {
			Board::getInstance()->setEvent(Board::ATE_BY_WAMPUS);
		}
	}
}