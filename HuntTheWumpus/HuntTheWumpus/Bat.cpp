#include "Bat.h"

namespace game {
	namespace pieces {
		Bat::Bat(int i, char* name, int x, int y)
			:ComputerPlayer(i, name, x, y) {

		};
		Bat::Bat(int i, char* name)
			:ComputerPlayer(i, name) {

		}

		void Bat::doAction() {

		}
	}
}