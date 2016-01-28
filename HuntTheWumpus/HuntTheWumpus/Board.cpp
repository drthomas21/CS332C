#include "Board.h"
#include "Player.h"
#include "Bat.h"
#include "Arrow.h"
#include "Trap.h"
#include "Wumpus.h"
#include <math.h>
#include <cstdlib>
#include <string>

namespace game {
	//Static Variables
	Board* Board::Instance = nullptr;
	int Board::size = 0;

	//Private & Protected functions
	bool const Board::isValidLocation(int x, int y) {
		bool ret = x >= 0 && x < Board::size && y >= 0 && y < Board::size;
		return ret;
	}
	bool const Board::isValidLocation(int x, int y, int s) {
		bool ret = x >= 0 && x < Board::size && y >= 0 && y < Board::size;
		if (ret) {
			for (int i = 0; i < s; i++) {
				if (this->pieces[i].getPositionX() == x && this->pieces[i].getPositionY() == y) {
					ret = false;
					break;
				}
			}
		}
		return ret;
	}
	bool const Board::moveNorth(int id) {
		bool ret = false;
		int x = this->pieces[id].getPositionX(), y = this->pieces[id].getPositionY();
		if (this->isValidLocation(x, y - 1)) {
			this->placePiece(id, x, y - 1);
			ret = true;
		}

		return ret;
	}
	bool const Board::moveSouth(int id) {
		bool ret = false;
		int x = this->pieces[id].getPositionX(), y = this->pieces[id].getPositionY();
		if (this->isValidLocation(x, y + 1)) {
			this->placePiece(id, x, y + 1);
			ret = true;
		}

		return ret;
	}
	bool const Board::moveEast(int id) {
		bool ret = false;
		int x = this->pieces[id].getPositionX(), y = this->pieces[id].getPositionY();
		if (this->isValidLocation(x + 1, y)) {
			this->placePiece(id, x + 1, y);
			ret = true;
		}

		return ret;
	}
	bool const Board::moveWest(int id) {
		bool ret = false;
		int x = this->pieces[id].getPositionX(), y = this->pieces[id].getPositionY();
		if (this->isValidLocation(x - 1, y)) {
			this->placePiece(id, x - 1, y);
			ret = true;
		}

		return ret;
	}

	void Board::operator =(Board const&) {
		//Do nothing
	}

	void Board::setUp() {
		int id = 0;
		if (Board::size > 7) {
			//Trying to keep the ration of 49 slots : 8 players
			this->players = static_cast<int>(pow(Board::size, 2) / 6.125);
		} else {
			this->players = 8;
		}

		this->pieces = new Piece[this->players];
		int x = 0, y = 0;

		//Place the player
		x = rand() % Board::size, y = rand() % Board::size;
		this->pieces[0] = pieces::Player(id, "You");
		this->placePiece(id, x, y);
		id++;

		//Place the Wumpus
		do {
			x = rand() % Board::size, y = rand() % Board::size;
		} while (!this->isValidLocation(x,y,id));
		this->pieces[1] = pieces::Wumpus(id, "Wumpus");
		this->placePiece(id, x, y);
		id++;
		
		int numOfTraps, numOfBats, numOfArrows;
		if (this->players > 8) {
			do {
				numOfTraps = rand() % (this->players - 2);
				numOfBats = rand() % (this->players - 2 - numOfTraps);
				numOfArrows = (this->players - 2)- (numOfTraps + numOfBats);
			} while (numOfTraps <= 0 || numOfBats <= 0 || numOfArrows <= 0);
		} else {
			numOfArrows = 2;
			numOfBats = 2;
			numOfTraps = 2;
		}
		
		//Place the traps
		for (int i = 0; i < numOfTraps; i++) {
			int x, y;
			do {
				x = rand() % Board::size, y = rand() % Board::size;
			} while (!this->isValidLocation(x, y, id));
			std::string name = "Trap " + (i + 1);
			this->pieces[id] = pieces::Trap(id, "Trap");
			this->placePiece(id, x, y);
			id++;
		}

		//Place the bats
		for (int i = 0; i < numOfBats; i++) {
			int x, y;
			do {
				x = rand() % Board::size, y = rand() % Board::size;
			} while (!this->isValidLocation(x, y, id));
			std::string name = "Bat " + (i + 1);
			this->pieces[id] = pieces::Bat(id, "Bat");
			this->placePiece(id, x, y);
			id++;
		}

		//Place the arrows
		for (int i = 0; i < numOfArrows; i++) {
			int x, y;
			do {
				x = rand() % Board::size, y = rand() % Board::size;
			} while (!this->isValidLocation(x, y, id));
			std::string name = "Arrow"  + (i + 1);
			this->pieces[id] = pieces::Arrow(id, "Arrow");
			this->placePiece(id, x, y);
			id++;
		}
	}

	//Public functions	
	bool const Board::move(int direction, int id) {
		bool ret = false;
		switch (direction) {
			case(Board::NORTH) :
				ret = this->moveNorth(id);
				break;
			case(Board::SOUTH) :
				ret = this->moveSouth(id);
				break;
			case(Board::EAST) :
				ret = this->moveEast(id);
				break;
			case(Board::WEST) :
				ret = this->moveWest(id);
				break;
		}
		return ret;
	}

	bool const Board::isLocationFree(int x, int y) {
		return this->isValidLocation(x, y);
	}

	void Board::placePiece(int id, int x, int y) {
		int _x = this->pieces[id].getPositionX(), _y = this->pieces[id].getPositionY();
		this->pieces[id].setPositionX(x);
		this->pieces[id].setPositionY(y);

		//Only set the previous spot to "empty_space" if the piece was originally there
		if (this->slots[_x][_y] == id) {
			this->slots[_x][_y] = Board::EMPTY_SPACE;
		}

		//Set the id to the new location
		this->slots[x][y] = id;
	}

	std::string Board::printBoard(bool fog) {
		char shade = fog ? (char)178 : ' ',
			open = ' ',
			player = 'P',
			wumpus = fog ? (char)178 : 'W',
			bat = fog ? (char)178 : 'B',
			trap = fog ? (char)178 : 'T',
			arrow = fog ? (char)178 : 'A';
		std::string output = "";
		//Output numbers on top
		if (!fog) {
			output.append( "  ");
			for (int i = 0; i < Board::size; i++) {
				int _i = i % 10;
				output.append(" "+ std::to_string(_i));
			}
			output.append( "\n");
		}
		//Output board
		for (int x = 0; x < Board::size; x++) {
			//Row divider
			if (!fog) {
				//Number buffer
				output.append( "  ");
			}

			for (int y = 0; y < Board::size; y++) {
				output.append( "--");
			}

			output.append( "-\n");
			//Characters and Shade
			if (!fog) {
				//Output side numbers
				int _i = x % 10;
				output.append(std::to_string(_i) + " ");
			}
			for (int y = 0; y < Board::size; y++) {
				switch (this->slots[x][y]) {
					case(Board::EMPTY_SPACE) :
						output.append( "|");
						output.push_back(shade);
						break;
					case(Board::DISCOVERED_SPACE) :
						output.append( "|");
						output.push_back(open);
						break;
					case(0) :
						output.append( "|");
						output.push_back(player);
						break;
					case(1) :
						output.append( "|");
						output.push_back(wumpus);
						break;
					default:
						char *name = this->pieces[this->slots[x][y]].getName();
						switch (name[0]) {
							case('B') :
								output.append( "|");
								output.push_back(bat);
								break;
							case('T') :
								output.append( "|");
								output.push_back(trap);
								break;
							case('A') :
								output.append( "|");
								output.push_back(arrow);
								break;
							default:
								output.append( "|");
								output.push_back(shade);
								break;
						}
						break;
				}				
			}
			output.append("|\n");
		}

		//Bottom Row divider
		if (!fog) {
			//Number buffer
			output.append( "  ");
		}

		for (int y = 0; y < Board::size; y++) {
			output.append( "--");
		}
		output.append("-");

		return output;
	}

	//Singleton
	Board* Board::getInstance() {
		if (!Board::Instance) {
			Board::Instance = new Board;
		}
		return Board::Instance;
	}

	void Board::setBoardSize(int size) {
		if (Board::size == 0) {
			Board::size = size;
		}
	}

	int const Board::getSize() {
		return Board::size;
	}

	int const Board::getRandomNum() {
		return rand() % Board::size;
	}

	//Copy Constructor
	Board::Board(Board const&) {
		//Do Nothing
	}
	
	//Constructors
	Board::Board() {
		this->slots = new int*[Board::size];
		for (int i = 0; i < Board::size; i++) {
			this->slots[i] = new int[Board::size];
			for (int j = 0; j < Board::size; j++) {
				this->slots[i][j] = Board::EMPTY_SPACE;
			}
		}
		this->setUp();
	}

	Board::~Board() {
		for (int i = 0; i < Board::size; i++) {
			delete [] this->slots[i];
		}
		delete [] this->slots;
	}
}