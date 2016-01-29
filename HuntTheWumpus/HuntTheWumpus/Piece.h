#pragma once

namespace game {
	class Piece {
		protected:
			//Only Children can call contructor
			Piece(int, char*);			
			char* name;
			int id;
		public:
			Piece();
			virtual char* getName() final;
			virtual int const getId() final;
			virtual void doAction(int);
	};
}