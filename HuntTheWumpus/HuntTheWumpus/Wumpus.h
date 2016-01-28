#include "ComputerPlayer.h"
#pragma once

namespace game {
	namespace pieces {
		class Wumpus : public ComputerPlayer {
		public:
			Wumpus(int,char*, int, int);
			Wumpus(int,char*);
			void doAction();
		};
	}
}