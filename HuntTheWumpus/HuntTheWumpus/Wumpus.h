#include "Piece.h"
#ifndef WUMPUS_H
#define WUMPUS_H

namespace game {
	namespace pieces {
		class Wumpus : public Piece {
		public:
			Wumpus(int,char*);
			void doAction(int);
			char* const makeSound();
		};
	}
}
#endif //WUMPUS_H