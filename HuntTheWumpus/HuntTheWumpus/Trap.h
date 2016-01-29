#include "Piece.h"
#ifndef TRAP_H
#define TRAP_H

namespace game {
	namespace pieces {
		class Trap : public Piece {
		public:
			Trap(int,char*);
			void doAction(int);
			char* const makeSound();
		};
	}
}
#endif //TRAP_H