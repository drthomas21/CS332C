#include "Piece.h"
#include <string>
#ifndef ARROW_H
#define ARROW_H

namespace game {
	namespace pieces {
		class Arrow : public Piece {
			public:
				Arrow(int, std::string);
				void doAction(int);
		};
	}
}
#endif //ARROW_H