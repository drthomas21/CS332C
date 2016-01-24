#include "Arrow.h"

namespace game {
	namespace pieces {
		Arrow::Arrow(int i, char* name, int x, int y)
			:Piece(i,name,x,y) {

		};
		Arrow::Arrow(int i, char* name) 
			:Piece(i,name) {

		}
	}
}