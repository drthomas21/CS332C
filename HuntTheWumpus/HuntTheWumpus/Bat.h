#include "Piece.h"
#ifndef BAT_H
#define BAT_H

namespace game {
	namespace pieces {
		class Bat : public Piece {
		public:
			Bat(int, char*);
			void doAction(int);
			char* const makeSound();
		};
	}
}
#endif //BAT_H