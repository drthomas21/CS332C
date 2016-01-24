#include "Trap.h"

namespace game {
	namespace pieces {
		Trap::Trap(int i, char* name, int x, int y)
			:ComputerPlayer(i, name, x, y) {

		};
		Trap::Trap(int i, char* name)
			:ComputerPlayer(i, name) {

		}

		void Trap::doAction() {

		}
	}
}