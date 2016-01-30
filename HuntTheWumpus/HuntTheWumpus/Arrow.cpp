#include "Arrow.h"
#include "Board.h"
#include <string>

namespace game {
	namespace pieces {
		Arrow::Arrow(int i, std::string name) 
			:Piece(i,name) {

		}

		void Arrow::doAction(int id = 0) {
			Board::getInstance()->setEvent(Board::GOT_ARROW);
			//this->setPositionX(-1);
			//this->setPositionY(-1);
		}
	}
}