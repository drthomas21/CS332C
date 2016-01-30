#include "Piece.h"
#include <string>
#ifndef WUMPUS_H
#define WUMPUS_H

namespace game {
	namespace pieces {
		class Wumpus : public Piece {
		public:
			Wumpus(int,std::string);
			void doAction(int);
			char* const makeSound();
		};
	}
}
#endif //WUMPUS_H