#pragma once
#include "ComputerPlayer.h";
namespace game {
	namespace pieces {
		class Trap : public ComputerPlayer {
		public:
			Trap(int,char*, int, int);
			Trap(int,char*);
			void doAction();
		};
	}
}