#include "Player.h"

namespace game {
	namespace pieces {
		Player::Player(int i, char* n, int x, int y)
			:Piece(i,n,x,y) { }
		Player::Player(int i, char* n)
			: Piece(i, n) {

		}
	}
}