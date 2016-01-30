#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>
#include "Board.h"
#include "Arrow.h"
#include "Bat.h"
#include "Player.h"
#include "Trap.h"
#include "Wumpus.h"

const bool DEBUG = false;
const bool GOD_MODE = false;
const int SMALL = 7;
const int MEDIUM = 14;
const int LARGE = 30;
const char* FILENAME = "./playerinfo.ini";

int handleBoardSize();
void displayBoard();
bool handleSave();
bool handleLoad();
char askDirection();
char askOption();
char askArrowDirection();
int askArrowDistance();

int main() {
	//Setup
	srand(static_cast<unsigned int>(time(NULL)));

	//Intro
	std::cout << "Hunt The Wumpus!!!" << std::endl;
	int size = handleBoardSize();
	game::Board::setBoardSize(size);

	//Create Game Board
	game::Board::getInstance();
	bool run = true;
	do {
		//Display Board
		displayBoard();

		//Check movement events
		switch (game::Board::getInstance()->getEvent()) {
			case(game::Board::ATE_BY_WAMPUS) :
				std::cout << "You was eaten by a Wumpus!!! You Lose!!!" << std::endl;
				std::cout << "[Press ENTER to Continue...]" << std::endl;
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
				if (!GOD_MODE) {
					run = false;
				}
				break;
			case(game::Board::TELEPORTED) :
				std::cout << "A large bat picked you up and moved you!!!!" << std::endl;
				std::cout << "[Press ENTER to Continue...]" << std::endl;
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
				break;
			case(game::Board::TRIGGERED_TRAP) :
				std::cout << "You was not paying attention and fell into a trap!!! You Lose!!!" << std::endl;
				std::cout << "[Press ENTER to Continue...]" << std::endl;
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
				if (!GOD_MODE) {
					run = false;
				}
				break;
			case(game::Board::GOT_ARROW) :
				std::cout << "You found a magical Wumpus- Killing arrow!" << std::endl;
				std::cout << "[Press ENTER to Continue...]" << std::endl;
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
				break;
		}

		if (!run) {
			break;
		}

		//Check surrounding area
		std::string sounds = game::Board::getInstance()->nearBy(game::Board::PLAYER_ID);
		std::cout << "Nearby: " << sounds << std::endl << std::endl;

		//Movement
		char direction = askDirection();
		bool ret = false;
		char _direction;
		int distance;
		game::Board::EVENT_RESPONSE event;
		switch (direction) {
			case 'w':
			case 'W':
				ret = game::Board::getInstance()->move(game::Board::PLAYER_ID, game::Board::NORTH);
				break;
			case 's':
			case 'S':
				ret = game::Board::getInstance()->move(game::Board::PLAYER_ID, game::Board::SOUTH);
				break;
			case 'a':
			case 'A':
				ret = game::Board::getInstance()->move(game::Board::PLAYER_ID, game::Board::WEST);
				break;
			case 'd':
			case 'D':
				ret = game::Board::getInstance()->move(game::Board::PLAYER_ID, game::Board::EAST);
				break;
			case '^':
				_direction = askArrowDirection();
				distance = askArrowDistance();
				event = game::Board::EVENT_RESPONSE::NOTHING_HAPPENED;
				switch (_direction) {
					case 'w':
					case 'W':
						event = game::Board::getInstance()->shootArrow(game::Board::NORTH, distance);
						break;
					case 's':
					case 'S':
						event = game::Board::getInstance()->shootArrow(game::Board::SOUTH, distance);
						break;
					case 'a':
					case 'A':
						event = game::Board::getInstance()->shootArrow(game::Board::WEST, distance);
						break;
					case 'd':
					case 'D':
						event = game::Board::getInstance()->shootArrow(game::Board::EAST, distance);
						break;
				}

				switch (event) {
					case(game::Board::EVENT_RESPONSE::KILLED_WUMPUS) :
						std::cout << "You manage to hit the Wumpus!!! You Win!!!" << std::endl;
						std::cout << "[Press ENTER to Continue...]" << std::endl;
						std::cin.ignore(std::numeric_limits<int>::max(), '\n');
						run = false;
						break;
					case(game::Board::EVENT_RESPONSE::MISSED_WUMPUS) :
						std::cout << "You missed the Wumpus!!! Now the Wumpus moved out of rage!!!" << std::endl;
						std::cout << "[Press ENTER to Continue...]" << std::endl;
						std::cin.ignore(std::numeric_limits<int>::max(), '\n');
						break;
					case(game::Board::EVENT_RESPONSE::NO_ARROWS_LEFT) :
						std::cout << "You have no arrows left" << std::endl;
						std::cout << "[Press ENTER to Continue...]" << std::endl;
						std::cin.ignore(std::numeric_limits<int>::max(), '\n');
						break;
				}
				break;
			case('!') :
				char option = askOption();
				switch (option) {
				case('!') :
						continue;
						break;
					case('1') :
						if (handleSave()) {
							std::cout << "Progress saved!" << std::endl;
							std::cout << "[Press ENTER to Continue...]" << std::endl;
							std::cin.ignore(std::numeric_limits<int>::max(), '\n');
						} else {
							std::cout << "[Press ENTER to Continue...]" << std::endl;
							std::cin.ignore(std::numeric_limits<int>::max(), '\n');
						}
						run = false;
						break;
					case('2') :
						if (handleSave()) {
							std::cout << "Progress saved!" << std::endl;
							std::cout << "[Press ENTER to Continue...]" << std::endl;
							std::cin.ignore(std::numeric_limits<int>::max(), '\n');
						}
						else {
							std::cout << "[Press ENTER to Continue...]" << std::endl;
							std::cin.ignore(std::numeric_limits<int>::max(), '\n');
						}
						break;
					case('3') :
						if (handleLoad()) {
							std::cout << "Progress loaded!" << std::endl;
							std::cout << "[Press ENTER to Continue...]" << std::endl;
							std::cin.ignore(std::numeric_limits<int>::max(), '\n');
						}
						else {
							std::cout << "[Press ENTER to Continue...]" << std::endl;
							std::cin.ignore(std::numeric_limits<int>::max(), '\n');
							run = false;
						}
						break;
					case('4') :
						run = false;
						break;		
					case('5') :
						int size = handleBoardSize();
						game::Board::getInstance()->reset(size);
						break;
				}
		}
	} while (run);

	return (0);
}

void displayBoard() {
	std::cout << game::Board::getInstance()->printBoard(!DEBUG) << std::endl;
	std::cout << "P = Player, W = Wumpus, T = Trap, B = Bat, A = Arrow" << std::endl;
	std::cout << "Arrows = " << game::Board::getInstance()->showArrowCount() << std::endl;
}

int handleBoardSize() {
	char choice;
	do {
		std::cout << "Map Size?\n\ta) Small (" << SMALL << "x" << SMALL << ")\n\tb) Medium (" << MEDIUM << "x" << MEDIUM << ")\n\tc) Large (" << LARGE << "x" << LARGE << ")" << std::endl;
		std::cin >> choice;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	} while (choice != 'a' && choice != 'b' && choice != 'c' && choice != 'A' && choice != 'B' && choice != 'C');

	//Game Setup
	switch (choice) {
		case('a') :
		case('A') :
			return SMALL;
			break;
		case('b') :
		case('B') :
			return MEDIUM;
			break;
		case('c') :
		case('C') :
			return LARGE;
			break;
		default:
			return SMALL;
			break;
	}
}

char askDirection() {
	std::cout << "Where do you want to move (or do you want the option menu)?"
		<< "\n\tw) North"
		<< "\n\ts) South"
		<< "\n\td) East"
		<< "\n\ta) West"
		<< "\n\t^) Shoot Arrow"
		<< "\n\t!) Options"
		<< std::endl;
	char choice;
	std::cin >> choice;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	if (choice != '^' && choice != '!' && choice != 'w' && choice != 'a' && choice != 's' && choice != 'd' && choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D') {
		return askDirection();
	}
	return choice;
}

char askArrowDirection() {
	std::cout << "Where do you want to shoot the arrow?"
		<< "\n\tw) North"
		<< "\n\ts) South"
		<< "\n\td) East"
		<< "\n\ta) West"
		<< std::endl;
	char choice;
	std::cin >> choice;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	if (choice != 'w' && choice != 'a' && choice != 's' && choice != 'd' && choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D') {
		return askArrowDirection();
	}
	return choice;
}

int askArrowDistance() {
	std::cout << "How far do you want to shoot it (1 - 3 rooms)?" << std::endl;
	int choice;
	std::cin >> choice;
	if (std::cin.fail()) {
		choice = 0;		
	}
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	if (choice < 1 || choice > 3) {
		return askArrowDirection();
	}
	return choice;
}

char askOption() {
	std::cout << "What would you like to do?"
		<< "\n\t1) Save and Exit"
		<< "\n\t2) Save"
		<< "\n\t3) Load"
		<< "\n\t4) Exit Game"
		<< "\n\t5) New Game"
		<< "\n\t!) Leave Option Menu"
		<< std::endl;
	char choice;
	std::cin >> choice;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	if (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '!') {
		return askOption();
	}
	return choice;
}

bool handleSave() {
	FILE* fres = nullptr;
	fopen_s(&fres,FILENAME, "w+");
	if (fres == NULL || fres == nullptr) {
		std::cout << "Cannot access/create " << FILENAME << std::endl;
		return false;
	}
	fputs(game::Board::getInstance()->__serialize().c_str(), fres);
	fclose(fres);
	return true;
}

bool handleLoad() {
	const int bitLimit = 100;
	char* buffered = new char[bitLimit];
	std::string serialized = "";
	FILE* fres = nullptr;
	fopen_s(&fres, FILENAME, "r");
	if (fres == NULL || fres==nullptr) {
		std::cout << FILENAME << " does not exists" << std::endl;
		return false;
	}
	while (fgets(buffered, bitLimit, fres) != NULL) {
		serialized.append(buffered);
	}
	delete[] buffered;
	fclose(fres);
	if (!game::Board::getInstance()->__unserialize(serialized)) {
		std::cout << "The game data was corrupted, please delete the file located at " << FILENAME << std::endl;
		return false;
	}
	return true;
}