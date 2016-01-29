#ifndef PIECE_H
#define PIECE_H

namespace game {
	class Piece {
		protected:
			//Only Children can call contructor
			Piece(int, char*);			
			char* name;
			int id;
		public:
			Piece();
			virtual char* const getName() final;
			virtual int const getId() final;
			virtual void doAction(int);
			virtual char* const makeSound();
	};
}
#endif //PIECE_H