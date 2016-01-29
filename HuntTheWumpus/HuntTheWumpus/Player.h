#include "Piece.h"
#ifndef PLAYER_H
#define PLAYER_H

namespace game {
	namespace pieces {
		class Player : public Piece {
		public:
			Player(int, char*);
			void doAction(int);
		};
	}
}
#endif //PLAYER_H