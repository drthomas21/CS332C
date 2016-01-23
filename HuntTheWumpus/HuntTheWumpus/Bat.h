#pragma once
#include "ComputerPlayer.h";
namespace game {
	namespace pieces {
		class Bat : public ComputerPlayer {
		public:
			Bat(char*, int, int);
			Bat(char*);
			void doAction();
		};
	}
}