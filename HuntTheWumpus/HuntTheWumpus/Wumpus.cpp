#include "Wumpus.h"

namespace game {
	namespace pieces {
		Wumpus::Wumpus(int i, char* name, int x, int y)
			:ComputerPlayer(i, name, x, y) {

		};
		Wumpus::Wumpus(int i, char* name)
			:ComputerPlayer(i, name) {

		}

		void Wumpus::doAction() {

		}
	}
}