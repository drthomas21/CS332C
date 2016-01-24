#include "Board.h"
#include "Player.h"
#include "Bat.h"
#include "Arrow.h"
#include "Trap.h"
#include "Wumpus.h"
#include <math.h>
#include <cstdlib>

namespace game {
	//Static Variables
	Board* Board::Instance = nullptr;
	int Board::size = 0;

	//Private & Protected functions
	bool const Board::isValidLocation(int x, int y) {
		return x >= 0 && x < Board::size && y >= 0 && y < Board::size;
	}
	bool const Board::moveNorth(int id) {

	}
	bool const Board::moveSouth(int id) {

	}
	bool const Board::moveEast(int id) {

	}
	bool const Board::moveWest(int id) {

	}

	void Board::operator =(Board const&) {

	}

	void Board::placePiece(int id, int x, int y) {

	}

	void Board::setUp() {
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
		this->pieces[0] = pieces::Player(0, "You", x, y);

		//Place the Wumpus
		do {
			x = rand() % Board::size, y = rand() % Board::size;
		} while (x != this->pieces[0].getPositionX() && y != this->pieces[0].getPositionY());
		this->pieces[1] = pieces::Player(1, "Wumpus", x, y);

		
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
		for (int i = 0; i < numOfTraps; i++)

		//Place the bats

		//Place the arrows
	}

	//Public functions
	void Board::setBoardSize(int size) {
		if (Board::size == 0) {
			Board::size = size;
		}
	}
	bool const Board::move(int direction, int id) {

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
	void Board::operator=(Board const&) {}

	//Copy Constructor
	Board::Board(Board const&) {}
	
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