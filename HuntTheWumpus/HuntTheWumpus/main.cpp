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
const bool GOD_MODE = true;
const int SMALL = 7;
const int MEDIUM = 14;
const int LARGE = 30;

void displayBoard();
void handleSave();
void handleLoad();
char askDirection();
char askOption();

int main() {
	//Setup
	srand(static_cast<unsigned int>(time(NULL)));
	char choice;

	//Intro
	std::cout << "Hunt The Wumpus!!!" << std::endl;
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
			game::Board::setBoardSize(SMALL);
			break;
		case('b') :
		case('B') :
			game::Board::setBoardSize(MEDIUM);
			break;
		case('c') :
		case('C') :
			game::Board::setBoardSize(LARGE);
			break;
	}

	//Create Game Board
	game::Board::getInstance();
	bool run = true;
	do {
		//Display Board
		displayBoard();

		//Check events
		switch (game::Board::getInstance()->getEvent()) {
			case(game::Board::KILLED_WAMPUS) :
				std::cout << "You managed to defeat the Wumpus!!! You Win!!!" << std::endl;
				std::cout << "[Press ENTER to Continue...]" << std::endl;
				std::cin.ignore();
				run = false;
				break;
			case(game::Board::ATE_BY_WAMPUS) :
				std::cout << "You was eaten by a Wumpus!!! You Lose!!!" << std::endl;
				std::cout << "[Press ENTER to Continue...]" << std::endl;
				std::cin.ignore();
				if (!GOD_MODE) {
					run = false;
				}
				break;
			case(game::Board::TELEPORTED) :
				std::cout << "A large bat picked you up and moved you!!!!" << std::endl;
				std::cout << "[Press ENTER to Continue...]" << std::endl;
				std::cin.ignore();
				break;
			case(game::Board::TRIGGERED_TRAP) :
				std::cout << "You was not paying attention and fell into a trap!!! You Lose!!!" << std::endl;
				std::cout << "[Press ENTER to Continue...]" << std::endl;
				std::cin.ignore();
				if (!GOD_MODE) {
					run = false;
				}
				break;
			case(game::Board::GOT_ARROW) :
				std::cout << "You found a magical Wumpus- Killing arrow!" << std::endl;
				std::cout << "[Press ENTER to Continue...]" << std::endl;
				std::cin.ignore();
				break;
		}

		if (!run) {
			break;
		}

		//Check surrounding area
		std::string sounds = game::Board::getInstance()->nearBy(game::Board::PLAYER_ID);
		if (sounds.length() > 0) {
			std::cout << sounds << std::endl;
		}

		//Movement
		char direction = askDirection();
		bool ret = false;
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
			case('0') :
				char option = askOption();
				switch (option) {
					case(0) :
						continue;
						break;
					case(1) :
						handleSave();
						run = false;
						break;
					case(2) :
						handleSave();
						break;
					case(3) :
						handleLoad();
						break;
					case(4) :
						run = false;
						break;		
					case(5) :
						game::Board::reset();
						break;
				}
		}
	} while (run);

	return (0);
}

void displayBoard() {
	std::cout << game::Board::getInstance()->printBoard(!DEBUG) << std::endl;
	std::cout << "P = Player, W = Wumpus, T = Trap, B = Bat, A = Arrow" << std::endl;
}

char askDirection() {
	std::cout << "Where do you want to move (or do you want the option menu)?"
		<< "\n\tw) North"
		<< "\n\ts) South"
		<< "\n\td) East"
		<< "\n\ta) West"
		<< "\n\t0) Options"
		<< std::endl;
	char choice;
	std::cin >> choice;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	if (choice != '0' && choice != 'w' && choice != 'a' && choice != 's' && choice != 'd' && choice != 'W' && choice != 'A' && choice != 'S' && choice != 'D') {
		return askDirection();
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
		<< "\n\t0) Leave Option Menu"
		<< std::endl;
	char choice;
	std::cin >> choice;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	if (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '0') {
		return askOption();
	}
	return choice;
}

void handleSave() {

}

void handleLoad() {

}