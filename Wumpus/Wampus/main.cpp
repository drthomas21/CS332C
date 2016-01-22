#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>

const int SIZE = 7;
class Board {
	enum IDS { EMPTY_SPACE, PLAYER_ID, WAMPUS_ID, TELEPORT_ID, TRAP_ID, ARROW_ID };
	enum EVENT_RESPONSE { INVALID_MOVE, NOTHING_HAPPENED, KILLED_WAMPUS, ATE_BY_WAMPUS, TELEPORTED, TRIGGERED_TRAP, GOT_ARROW };
	enum DIRECTIONS {NORTH, WEST, SOUTH, EAST};
	protected:
		int slots[SIZE][SIZE];
		bool isValidLocation(int x, int y) {
			return x < 0 || x > SIZE || y < 0 || y >> SIZE;
		}
		int moveNorth(int id) {

		}
		int moveSouth(int id) {

		}
		int moveEast(int id) {

		}
		int moveWest(int id) {

		}

	public:
		Board() {
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					this->slots[i][j] = this->EMPTY_SPACE;
				}
			}

			//Set traps

			//Set wampus

			//Set Arrow

			//Set Player
		}

		int move(int direction, int id) {

		}
				
};
int main() {

}