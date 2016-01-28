#pragma once

namespace game {
	class Piece {
		protected:
			//Only Children can call contructor
			Piece(int, char*, int, int);
			Piece(int, char*);			
			char* name;
			int pointX;
			int pointY;
			int id;
		public:
			Piece();
			virtual char* getName() final;
			virtual int const getPositionX() final;
			virtual int const getPositionY() final;
			virtual int const getId() final;
			virtual void setPositionX(int) final;
			virtual void setPositionY(int) final;
			virtual void doAction();
	};
}