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

	void Board::placePiece(int id, int x, int y) {
		this->pieces[id].setPositionX(x);
		this->pieces[id].setPositionY(y);
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
		this->pieces[0] = pieces::Player(id, "You", x, y);
		id++;

		//Place the Wumpus
		do {
			x = rand() % Board::size, y = rand() % Board::size;
		} while (!this->isValidLocation(x,y,id));
		this->pieces[1] = pieces::Player(id, "Wumpus", x, y);
		id++;
		
		int numOfTraps, numOfBats, numOfArrows;
		if (this->players > 8) {
			do {
				numOfTraps = rand() % this->players;
				numOfBats = rand() % (this->players - numOfTraps);
				numOfArrows = this->players - (numOfArrows + numOfBats);
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
			this->pieces[id] = pieces::Trap(id, name.c_str, x, y);
			id++;
		}

		//Place the bats
		for (int i = 0; i < numOfBats; i++) {
			int x, y;
			do {
				x = rand() % Board::size, y = rand() % Board::size;
			} while (!this->isValidLocation(x, y, id));
			std::string name = "Bat " + (i + 1);
			this->pieces[id] = pieces::Bat(id, name.c_str, x, y);
			id++;
		}

		//Place the arrows
		for (int i = 0; i < numOfArrows; i++) {
			int x, y;
			do {
				x = rand() % Board::size, y = rand() % Board::size;
			} while (!this->isValidLocation(x, y, id));
			std::string name = "Arrow " + (i + 1);
			this->pieces[id] = pieces::Arrow(id, name.c_str, x, y);
			id++;
		}
	}

	//Public functions
	void Board::setBoardSize(int size) {
		if (Board::size == 0) {
			Board::size = size;
		}
	}
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

	int const Board::getSize() {
		return this->size;
	}

	//Singleton
	Board* Board::getInstance() {
		if (!Board::Instance) {
			Board::Instance = &Board();
		}
		return Board::Instance;
	}

	//Operators
	void Board::operator=(Board const&) {
		//Do Nothing
	}

	//Copy Constructor
	Board::Board(Board const&) {
		//Do Nothing
	}
	
	//Constructors
	Board::Board() {
		for (int i = 0; i < Board::size; i++) {
			for (int j = 0; j < Board::size; j++) {
				this->slots[i][j] = Board::EMPTY_SPACE;
			}
		}
		this->setUp();
	}
}