#pragma once
#include "Piece.h";
namespace game {
	namespace pieces {
		class Arrow : public Piece {
		public:
			Arrow(int, char*, int, int);
			Arrow(int, char*);
		};
	}
}