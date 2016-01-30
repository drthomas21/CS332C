#include "Piece.h"
#include <string>
#ifndef TRAP_H
#define TRAP_H

namespace game {
	namespace pieces {
		class Trap : public Piece {
		public:
			Trap(int,std::string);
			void doAction(int);
			char* const makeSound();
		};
	}
}
#endif //TRAP_H