#pragma once
#include "ComputerPlayer.h";
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