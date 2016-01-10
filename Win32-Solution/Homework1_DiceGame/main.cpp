#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

int diceRoll();
char shouldComputerRollAgain(int turnPoints);
char getChoice(int, int);
bool hasWinner(int, int);

int main() {
	srand(static_cast<unsigned int>(time(NULL)));

	//intro
	std::cout << "Welcome to the Dice Game!" << std::endl << "You are Player 1 and the computer is Player 2" << std::endl;

	//data
	int totalPlayer1Points = 0;
	int totalPlayer2Points = 0;
	int turn = 0;

	do {
		int turnPoints = 0;
		int whichPlayer = turn % 2;

		//Slow the programe down so that it is easier to read
		std::cout << "Press [ENTER] to continue" << std::endl;
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');

		do {
			int diceChoice = diceRoll();
			turnPoints += diceChoice;
			//Display Roll
			std::cout << "Player " << (whichPlayer + 1) << " rolled " << diceChoice << std::endl;
			if (diceChoice != 1) {
				std::cout << "Turn Points: " << turnPoints << std::endl;
				if (diceChoice % 2 == 0) {
					//Roll again?
					char choice = getChoice(whichPlayer, turnPoints);
					if (choice == 'r' || choice == 'R') {
						continue;
					}
				}

				//Add up points
				if (whichPlayer == 0) {
					totalPlayer1Points += turnPoints;
				}
				else {
					totalPlayer2Points += turnPoints;
				}

				break;

			} else {
				std::cout << "Player " << (whichPlayer + 1) << " loses a turn! " << std::endl;
				break;
			}
		} while (true);

		turn++;
		std::cout << "Total Points: " << std::endl << "\tPlayer 1: " << totalPlayer1Points << std::endl << "\tPlayer 2: " << totalPlayer2Points << std::endl;
		if (hasWinner(totalPlayer1Points, totalPlayer2Points)) {
			break;
		}
	} while (true);
	return 0;
}

/**
	@return int roll
		returns a number in the range [1,6]
*/
int diceRoll() {
	return (rand() % 5) + 1;
}

/**
	@param int turnPoints
		the total points that the player earned
	@return char choice
		returns either 'r' for "roll again" or 'h' for "hold"
*/
char shouldComputerRollAgain(int turnPoints) {
	return turnPoints < 20 ? 'r' : 'h';
}

/**
	@param int whichPlayer
		0 = player 1
		1 = player 2
	@param int turnPoints
		total points for turn
	@return char choice
		the choice of the player
*/
char getChoice(int whichPlayer, int turnPoints) {
	char choice;
	do {
		if (whichPlayer == 0) {
			//Ask Player
			std::cout << "Do you want to Roll again or Hold (r/h)? ";
			std::cin >> choice;
			//clear char buffer from extra characters
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		}
		else {
			//Ask Computer
			choice = shouldComputerRollAgain(turnPoints);
		}
	} while (choice != 'R' && choice != 'r' && choice != 'H' && choice != 'h');
	return choice;
}

/**
	@param int totalPlayer1Points
	@param int totalPlayer2Points
	@return bool hasWinner
		if there is a winner
*/
bool hasWinner(int totalPlayer1Points, int totalPlayer2Points) {
	bool ret = false;
	if (totalPlayer1Points >= 100) {
		std::cout << "Player 1 won!" << std::endl;
		ret = true;
	} else if (totalPlayer2Points >= 100) {
		std::cout << "Player 2 won!" << std::endl;
		ret = true;
	}
	return ret;
}