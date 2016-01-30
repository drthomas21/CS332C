#include "Trap.h"
#include "Board.h"
#include <string>

namespace game {
	namespace pieces {
		Trap::Trap(int i, std::string name)
			:Piece(i, name) {

		}

		void Trap::doAction(int id = 0) {
			Board::getInstance()->setEvent(Board::TRIGGERED_TRAP);
		}

		char* const Trap::makeSound() {
			return "You feel a breeze nearby";
		}
	}
}