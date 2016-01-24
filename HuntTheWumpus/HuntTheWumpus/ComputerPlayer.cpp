#include "ComputerPlayer.h"

namespace game {
	namespace pieces {
		ComputerPlayer::ComputerPlayer(int i, char* name, int x, int y)
			:Piece(i, name, x, y) {

		};
		ComputerPlayer::ComputerPlayer(int i, char* name)
			:Piece(i, name) {

		}
	}
}