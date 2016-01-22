#pragma once
namespace game {
	class Piece {
		protected:
			char* name;
			int pointX;
			int pointY;
		public:
			virtual char* getName();
			virtual int getPositionX();
			virtual int getPositionY();
			virtual void setPositionX(int);
			virtual void setPositionY(int);
	};
}