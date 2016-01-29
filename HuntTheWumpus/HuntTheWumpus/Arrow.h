#include "Piece.h"
#ifndef ARROW_H
#define ARROW_H

namespace game {
	namespace pieces {
		class Arrow : public Piece {
			public:
				Arrow(int, char*);
				void doAction(int);
		};
	}
}
#endif //ARROW_H