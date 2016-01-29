#include "Trap.h"
#include "Board.h"

namespace game {
	namespace pieces {
		Trap::Trap(int i, char* name)
			:Piece(i, name) {

		}

		void Trap::doAction(int id = 0) {
			Board::getInstance()->setEvent(Board::TRIGGERED_TRAP);
		}
	}
}