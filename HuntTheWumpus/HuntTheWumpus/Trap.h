#include "Piece.h"
#pragma once

namespace game {
	namespace pieces {
		class Trap : public Piece {
		public:
			Trap(int,char*);
			void doAction(int);
		};
	}
}