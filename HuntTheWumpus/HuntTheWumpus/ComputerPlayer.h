#include "Piece.h"
#pragma once

namespace game {
	namespace pieces {
		class ComputerPlayer : public Piece {
		protected:
			//Only children can call constructor
			ComputerPlayer(int, char*, int, int);
			ComputerPlayer(int, char*);
		public:			
			virtual void doAction() = 0;
		};
	}
}