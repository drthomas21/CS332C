#include "Piece.h"
#include <string>
#ifndef PLAYER_H
#define PLAYER_H

namespace game {
	namespace pieces {
		class Player : public Piece {
		public:
			Player(int, std::string);
			void doAction(int);
		};
	}
}
#endif //PLAYER_H