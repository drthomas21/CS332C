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
const int SMALL = 7;
const int MEDIUM = 14;
const int LARGE = 30;

void displayBoard();

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

	do {
		//Create Game Board
		game::Board::getInstance();

		//Display Board
		displayBoard();

		//Check events

		//Movement
		char direction = askDirection();
	} while (true);

	
}

void displayBoard() {
	std::cout << game::Board::getInstance()->printBoard(!DEBUG) << std::endl;
	std::cout << "P = Player, W = Wumpus, T = Trap, B = Bat, A = Arrow" << std::endl;
}

char askDirection() {
	std::cout << "Where do you want to move?"
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
		return askDirection();
	}
	return choice;
}