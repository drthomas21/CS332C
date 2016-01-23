#pragma once
#include "Piece.h";
namespace game {
	namespace pieces {
		class Arrow : public Piece {
		public:
			Arrow(char*, int, int);
			Arrow(char*);
		};
	}
}