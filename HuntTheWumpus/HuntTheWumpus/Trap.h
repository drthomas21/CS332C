#pragma once
#include "ComputerPlayer.h";
namespace game {
	namespace pieces {
		class Trap : public ComputerPlayer {
		public:
			Trap(char*, int, int);
			Trap(char*);
			void doAction();
		};
	}
}