#include "Piece.h"
#pragma once

namespace game {
	namespace pieces {
		class Bat : public Piece {
		public:
			Bat(int, char*);
			void doAction(int);
		};
	}
}