#include "Piece.h"
#pragma once

namespace game {
	namespace pieces {
		class Player : public Piece {
		public:
			Player(int, char*);
			void doAction(int);
		};
	}
}