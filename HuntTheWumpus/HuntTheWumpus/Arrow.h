#include "Piece.h"
#pragma once

namespace game {
	namespace pieces {
		class Arrow : public Piece {
			public:
				Arrow(int, char*);
				void doAction(int);
		};
	}
}