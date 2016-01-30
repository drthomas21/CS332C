#include "Wumpus.h"
#include "Board.h"
#include <string>

namespace game {
	namespace pieces {
		Wumpus::Wumpus(int i, std::string name)
			:Piece(i, name) {

		}

		void Wumpus::doAction(int id = 0) {
			Board::getInstance()->setEvent(Board::ATE_BY_WAMPUS);
		}

		char* const Wumpus::makeSound() {
			return "You smell a foul stench nearby";
		}
	}
}