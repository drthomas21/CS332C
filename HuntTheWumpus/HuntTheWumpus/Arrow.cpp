#include "Arrow.h"
#include "Board.h"

namespace game {
	namespace pieces {
		Arrow::Arrow(int i, char* name) 
			:Piece(i,name) {

		}

		void Arrow::doAction(int id = 0) {
			Board::getInstance()->setEvent(Board::GOT_ARROW);
			//this->setPositionX(-1);
			//this->setPositionY(-1);
		}
	}
}