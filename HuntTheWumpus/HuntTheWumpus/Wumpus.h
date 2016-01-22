#pragma once
#include "ComputerPlayer.h";
namespace game {
	namespace pieces {
		class Wumpus : public ComputerPlayer {
		public:
			Wumpus(char*, int, int);
			Wumpus(char*);
			void doAction();
		};
	}
}