#include "Piece.h"
#include <string>
#ifndef BAT_H
#define BAT_H

namespace game {
	namespace pieces {
		class Bat : public Piece {
		public:
			Bat(int, std::string);
			void doAction(int);
			std::string const makeSound();
		};
	}
}
#endif //BAT_H