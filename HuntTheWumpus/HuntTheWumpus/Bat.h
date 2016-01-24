#pragma once
#include "ComputerPlayer.h";
namespace game {
	namespace pieces {
		class Bat : public ComputerPlayer {
		public:
			Bat(int,char*, int, int);
			Bat(int, char*);
			void doAction();
		};
	}
}