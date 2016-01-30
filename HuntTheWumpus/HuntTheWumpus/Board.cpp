#include "Board.h"
#include "Player.h"
#include "Bat.h"
#include "Arrow.h"
#include "Trap.h"
#include "Wumpus.h"
#include <math.h>
#include <cstdlib>
#include <string>
#include <sstream>

namespace game {
	//Static Variables
	Board* Board::Instance = nullptr;
	int Board::size = 0;

	//Private & Protected functions
	bool const Board::isValidLocation(Slot const oldSlot, int x, int y) {
		bool ret = x >= 0 && x < Board::size && y >= 0 && y < Board::size;
		if (ret) {
			if (this->slots[x][y].id != Board::EMPTY_SPACE && this->slots[x][y].id != Board::DISCOVERED_SPACE) {
				//Toggle Event
				if (oldSlot.id == Board::WUMPUS_ID && this->slots[x][y].id != Board::PLAYER_ID) {
					this->setEvent(Board::EVENT_RESPONSE::ITEM_DESTORYED);
				} else if(oldSlot.id == Board::WUMPUS_ID && this->slots[x][y].id == Board::PLAYER_ID) {
					this->pieces[oldSlot.id]->doAction(this->slots[x][y].id);
				} else {
					this->pieces[this->slots[x][y].id]->doAction(oldSlot.id);
				}
				
				if (this->event != Board::GOT_ARROW && this->event != Board::NOTHING_HAPPENED) {
					ret = false;
				}
			}
		}
		return ret;
	}
	bool const Board::isValidLocation(int x, int y, int s) {
		bool ret = x >= 0 && x < Board::size && y >= 0 && y < Board::size;
		if (ret) {
			if (this->slots[x][y].id != Board::EMPTY_SPACE && this->slots[x][y].id != Board::DISCOVERED_SPACE) {
				ret = false;
			}
		}
		return ret;
	}
	bool const Board::moveNorth(int id) {
		bool ret = false;
		Slot* slot = this->getSlot(id);
		int x, y;

		//There is something funky going on if a slot does not exists
		if (slot == nullptr) {
			exit(1);
		}

		x = slot->x, y = slot->y;
		if (this->isValidLocation(*slot,x, y - 1)) {
			this->placePiece(id, x, y - 1);
			ret = true;
		}

		return ret;
	}
	bool const Board::moveSouth(int id) {
		bool ret = false;
		Slot* slot = this->getSlot(id);
		int x, y;

		//There is something funky going on if a slot does not exists
		if (slot == nullptr) {
			exit(1);
		}

		x = slot->x, y = slot->y;
		if (this->isValidLocation(*slot,x, y + 1)) {
			this->placePiece(id, x, y + 1);
			ret = true;
		}

		return ret;
	}
	bool const Board::moveEast(int id) {
		bool ret = false;
		Slot* slot = this->getSlot(id);
		int x, y;

		//There is something funky going on if a slot does not exists
		if (slot == nullptr) {
			exit(1);
		}

		x = slot->x, y = slot->y;
		if (this->isValidLocation(*slot,x + 1, y)) {
			this->placePiece(id, x + 1, y);
			ret = true;
		}

		return ret;
	}
	bool const Board::moveWest(int id) {
		bool ret = false;
		Slot* slot = this->getSlot(id);
		int x, y;

		//There is something funky going on if a slot does not exists
		if (slot == nullptr) {
			exit(1);
		}

		x = slot->x, y = slot->y;
		if (this->isValidLocation(*slot,x - 1, y)) {
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

		this->pieces = new Piece*[this->players];
		int x = 0, y = 0;

		//Place the player
		x = rand() % Board::size, y = rand() % Board::size;
		this->pieces[0] = new pieces::Player(id, "Player");
		this->placePiece(id, x, y);
		id++;

		//Place the Wumpus
		do {
			x = rand() % Board::size, y = rand() % Board::size;
		} while (!this->isValidLocation(x,y,id));
		this->pieces[1] = new pieces::Wumpus(id, "Wumpus");
		this->placePiece(id, x, y);
		id++;
		
		//Setting some vars
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
			this->pieces[id] = new pieces::Trap(id, "Trap");
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
			this->pieces[id] = new pieces::Bat(id, "Bat");
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
			this->pieces[id] = new pieces::Arrow(id, "Arrow");
			this->placePiece(id, x, y);
			id++;
		}
	}

	Slot* const Board::getSlot(int id) {
		Slot* slot = nullptr;
		for (int _x = 0; _x < Board::size; _x++) {
			for (int _y = 0; _y < Board::size; _y++) {
				if (this->slots[_x][_y].id == id) {
					slot = &this->slots[_x][_y];
				}
			}
		}

		return slot;
	}

	//Public functions	
	bool const Board::move(int id, Board::DIRECTIONS direction) {
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
		return this->isValidLocation(x, y, Board::size);
	}

	void Board::placePiece(int id, int x, int y) {
		Slot* oldSlot = this->getSlot(id);

		//Only set the previous spot to "empty_space" if the piece was originally there
		if (oldSlot != nullptr && oldSlot->id == id && id == Board::PLAYER_ID) {
			oldSlot->id = Board::DISCOVERED_SPACE;
		}

		//Set the id to the new location
		this->slots[x][y].id = id;
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
		for (int y = 0; y < Board::size; y++) {
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
				int _i = y % 10;
				output.append(std::to_string(_i) + " ");
			}
			for (int x = 0; x < Board::size; x++) {
				switch (this->slots[x][y].id) {
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
						std::string name = this->pieces[this->slots[x][y].id]->getName();
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

	void Board::setEvent(Board::EVENT_RESPONSE event) {
		this->event = event;
	}

	Board::EVENT_RESPONSE const Board::getEvent() {
		Board::EVENT_RESPONSE resp =  this->event;
		this->event = Board::NOTHING_HAPPENED;
		return resp;
	}

	std::string const Board::nearBy(int id) {
		Slot* slot = this->getSlot(id);
		std::string response = "";

		//Left
		if (slot->x > 0 && this->slots[slot->x - 1][slot->y].id >= 0) {
			if (response.length() > 0) {
				response.append("\n");
			}
			response.append(this->pieces[this->slots[slot->x - 1][slot->y].id]->makeSound());
		}

		//Right
		if (slot->x < Board::size - 1 && this->slots[slot->x + 1][slot->y].id >= 0) {
			if (response.length() > 0) {
				response.append("\n");
			}
			response.append(this->pieces[this->slots[slot->x + 1][slot->y].id]->makeSound());
		}

		//Above
		if (slot->y > 0 && this->slots[slot->x][slot->y - 1].id >= 0) {
			if (response.length() > 0) {
				response.append("\n");
			}
			response.append(this->pieces[this->slots[slot->x][slot->y - 1].id]->makeSound());
		}

		//Below
		if (slot->y < Board::size - 1 && this->slots[slot->x][slot->y + 1].id >= 0) {
			if (response.length() > 0) {
				response.append("\n");
			}
			response.append(this->pieces[this->slots[slot->x][slot->y + 1].id]->makeSound());
		}

		return response;
	}

	void Board::reset(int size = Board::size) {
		//Delete pointers
		for (int i = 0; i < Board::size; i++) {
			delete[] this->slots[i];
		}
		delete[] this->slots;

		for (int i = 0; i<this->players; i++) {
			delete this->pieces[i];
		}
		delete[] this->pieces;

		//Rebuild everything
		Board::size = size;
		this->arrows = 5;
		this->event = Board::NOTHING_HAPPENED;
		this->slots = new Slot*[Board::size];
		for (int x = 0; x < Board::size; x++) {
			this->slots[x] = new Slot[Board::size];
			for (int y = 0; y < Board::size; y++) {
				this->slots[x][y] = Slot{ x,y,Board::EMPTY_SPACE };
			}
		}
		this->setUp();
	}

	std::string const Board::__serialize() {
		std::string serialized = "";
		//serialize arrows
		serialized.append("arrows_count=" + std::to_string(this->arrows) + "\n");
		serialized.append("\n");

		//serialize pieces
		serialized.append("pieces_size="+std::to_string(this->players)+"\n");
		for (int i = 0; i < this->players; i++) {
			serialized.append("pieces=");
			serialized.append(std::to_string(this->pieces[i]->getId())+",");
			serialized.append(this->pieces[i]->getName());
			serialized.append("\n");
		}
		serialized.append("\n");

		//serialized slots
		serialized.append("slots_size=" + std::to_string(Board::size) + "\n");
		for (int x = 0; x < Board::size; x++) {
			for (int y = 0; y < Board::size; y++) {
				serialized.append("slots=");
				serialized.append(std::to_string(this->slots[x][y].x)+ ",");
				serialized.append(std::to_string(this->slots[x][y].y) + ",");
				serialized.append(std::to_string(this->slots[x][y].id));
				serialized.append("\n");
			}
		}

		return serialized;
	}

	bool const Board::__unserialize(std::string serialized) {
		//Delete pointers
		for (int i = 0; i < Board::size; i++) {
			delete[] this->slots[i];
		}
		delete[] this->slots;

		for (int i = 0; i<this->players; i++) {
			delete this->pieces[i];
		}
		delete[] this->pieces;

		//Parse string
		std::stringstream ss(serialized);
		std::string line;
		int pSize = 0;
		int sSize = 0;

		//Search for sizes only
		while (std::getline(ss, line, '\n')) {
			if (line.find("pieces_size") != std::string::npos) {
				pSize = stoi(line.substr(line.find("=")+1));
			}

			if (line.find("slots_size") != std::string::npos) {
				sSize = stoi(line.substr(line.find("=") + 1));
			}

			if (line.find("arrows_count") != std::string::npos) {
				this->arrows = stoi(line.substr(line.find("=") + 1));
			}
		}

		//Check if we have sizes for our arrays
		if (pSize == 0 || sSize == 0 ) {
			//Missing data
			return false;
		}

		//Set some vars
		this->players = pSize;
		Board::size = sSize;
		this->event = Board::NOTHING_HAPPENED;

		//Build arrays		
		this->pieces = new Piece*[this->players];
		this->slots = new Slot*[Board::size];
		for (int x = 0; x < Board::size; x++) {
			this->slots[x] = new Slot[Board::size];
			for (int y = 0; y < Board::size; y++) {
				this->slots[x][y] = Slot{ x,y,Board::EMPTY_SPACE };
			}
		}

		//Reset stream;
		ss.clear();	
		ss.seekg(0, ss.beg);

		//Search for objects only
		int pCount = 0, sCount = 0;
		while (std::getline(ss, line, '\n')) {
			if (line.find("pieces=") != std::string::npos) {
				pCount++;
				std::string props = line.substr(line.find("=") + 1);
				size_t index = 0;
				int id = 0;
				std::string name = "";
				for (int i = 0; i < 2; i++) {
					size_t start = index > 0 ? index + 1 : index;
					index += 1;
					index = props.find(",", index);
					if (index == std::string::npos) {
						index = props.length();
					}
					std::string prop = props.substr(start, index);
					if (i == 0) {
						id = stoi(prop);
					}
					else {
						name = prop;
					}
				}

				if (name.compare("Arrow") == 0) {
					this->pieces[id] = new pieces::Arrow(id, name);
				} else if (name.compare("Bat") == 0) {
					this->pieces[id] = new pieces::Bat(id, name);
				} else if (name.compare("Player") == 0) {
					this->pieces[id] = new pieces::Player(id, name);
				} else if (name.compare("Trap") == 0) {
					this->pieces[id] = new pieces::Trap(id, name);
				} else if (name.compare("Wumpus") == 0) {
					this->pieces[id] = new pieces::Wumpus(id, name);
				} else {
					return false;
				}				
			}

			if (line.find("slots=") != std::string::npos) {
				sCount++;
				std::string props = line.substr(line.find("=") + 1);
				size_t index = 0;
				int x = 0, y = 0, id = 0;
				std::string name = "";
				for (int i = 0; i < 3; i++) {
					size_t start = index > 0 ? index + 1 : index;
					index += 1;
					index = props.find(",", index);
					std::string prop = props.substr(start, index);
					if (i == 0) {
						x = stoi(prop);
					} else if(i == 1) {
						y = stoi(prop);
					} else {
						id = stoi(prop);
					}
				}

				this->slots[x][y] = Slot{ x,y,id };
			}
		}

		//Check if our counts are matching
		if (pCount != this->players || sqrt(sCount) != Board::size) {
			return false;
		}

		return true;
	}

	Board::EVENT_RESPONSE const Board::shootArrow(Board::DIRECTIONS direction, int distance) {
		Slot slot = *this->getSlot(Board::PLAYER_ID);
		if (this->arrows > 0) {
			this->arrows--;
			int adj_x = 0, adj_y = 0;
			switch (direction) {
				case(Board::DIRECTIONS::NORTH) :
					adj_y = -1;
					break;
				case(Board::DIRECTIONS::SOUTH) :
					adj_y = 1;
					break;
				case(Board::DIRECTIONS::WEST) :
					adj_x = -1;
					break;
				case(Board::DIRECTIONS::EAST) :
					adj_x = 1;
					break;
			}

			int x = slot.x; int y = slot.y;
			for (int i = 0; i < distance; i++) {
				x += adj_x, y += adj_y;
				if (x >= 0 && x < Board::size && y >= 0 && y < Board::size && this->slots[x][y].id == Board::IDS::WUMPUS_ID) {
					return Board::EVENT_RESPONSE::KILLED_WUMPUS;
				}
			}

			//Wumpus was startled, so he moved
			switch (rand() % 4) {
				case(0):
					if (this->move(Board::WUMPUS_ID, game::Board::NORTH)) {
						break;
					}
				case(1):
					if (this->move(Board::WUMPUS_ID, game::Board::SOUTH)) {
						break;
					}
				case(2):
					if (this->move(Board::WUMPUS_ID, game::Board::EAST)) {
						break;
					}
				case(3):
					if (this->move(Board::WUMPUS_ID, game::Board::WEST)) {
						break;
					}
				default:
					if (!this->move(Board::WUMPUS_ID, game::Board::NORTH)) {
						this->move(Board::WUMPUS_ID, game::Board::SOUTH);
					}
					break;

			}
			return Board::EVENT_RESPONSE::MISSED_WUMPUS;
		}

		return Board::EVENT_RESPONSE::NO_ARROWS_LEFT ;
	}

	void Board::pickupArrow() {
		this->arrows++;
	}

	int const Board::showArrowCount() {
		return this->arrows;
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
		this->arrows = 5;
		this->event = Board::NOTHING_HAPPENED;
		this->slots = new Slot*[Board::size];
		for (int x = 0; x < Board::size; x++) {
			this->slots[x] = new Slot[Board::size];
			for (int y = 0; y < Board::size; y++) {
				this->slots[x][y] = Slot{ x,y,Board::EMPTY_SPACE };
			}
		}
		this->setUp();
	}

	Board::~Board() {
		for (int i = 0; i < Board::size; i++) {
			delete [] this->slots[i];
		}
		delete [] this->slots;
		
		for (int i = 0; i<this->players; i++) {
			delete this->pieces[i];
		}
		delete[] this->pieces;
	}
}