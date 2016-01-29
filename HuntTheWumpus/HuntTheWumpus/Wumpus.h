#include "Piece.h"
#pragma once

namespace game {
	namespace pieces {
		class Wumpus : public Piece {
		public:
			Wumpus(int,char*);
			void doAction(int);
		};
	}
}