#include "Arrow.h"

namespace game {
	namespace pieces {
		Arrow::Arrow(char* name, int x, int y)
			:name(name),pointX(x),pointY(y) {

		};
		Arrow::Arrow(char* name) :name(name){

		}
	}
}