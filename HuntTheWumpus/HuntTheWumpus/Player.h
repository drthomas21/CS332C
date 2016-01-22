#pragma once
#include "Piece.h";
namespace game {
	namespace pieces {
		class Player : public Piece {
		public:
			Player(char*, int, int);
			Player(char*);
		};
	}
}