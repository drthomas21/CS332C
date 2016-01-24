#pragma once
#include "Piece.h";
namespace game {
	namespace pieces {
		class Player : public Piece {
		public:
			Player(int, char*, int, int);
			Player(int, char*);
		};
	}
}