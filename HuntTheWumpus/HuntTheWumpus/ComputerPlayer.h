#pragma once
#include "Piece.h";
namespace game {
	namespace pieces {
		class ComputerPlayer : public Piece {
		public:
			virtual void doAction();
			char* getName() final;
			int getPositionX() final;
			int getPositionY() final;
			void setPositionX(int x) final;
			void setPositionY(int y) final;
		};
	}
}