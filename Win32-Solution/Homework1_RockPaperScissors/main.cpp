#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>

std::string fancyMessage(int, int, int);
int didPlayer1Win(char, char);
char numToChoice(int);
std::string numToString(int);
int computerChoice();

int main() {
	//Seed Random
	srand(static_cast<unsigned int>(time(NULL)));

	//Intro
	std::cout << "Welcome To Rock-Paper-Scissors" << std::endl;

	//Data
	int player1Choice;
	int player2Choice;

	while (true) {
		player2Choice = computerChoice();
		do {
			player1Choice = 0;
			std::cout << "Choose (1) Rock, (2) Paper, (3) Scissors ";
			std::cin >> player1Choice;
			if (std::cin.fail()) {
				std::cout << "Invalid value" << std::endl;
				player1Choice = 0;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
		} while (player1Choice < 1 || player1Choice > 3);

		//Results
		int winner = didPlayer1Win(numToChoice(player1Choice), numToChoice(player2Choice));
		if (winner != 0) {
			std::string message = fancyMessage(player1Choice, player2Choice, winner);
			std::cout << message << std::endl;
		}

		//Choices
		std::cout << "You chose " << numToString(player1Choice) << std::endl;
		std::cout << "Computer chose " << numToString(player2Choice) << std::endl;

		//Winner
		switch (winner) {
			case -1:
				std::cout << "You Won!" << std::endl;
				break;
			case 0:
				std::cout << "Tie Game!" << std::endl;
				break;
			case 1:
				std::cout << "Computer Won!" << std::endl;
				break;
		}
	}

	return 0;
}

std::string fancyMessage(int player1Choice, int player2Choice, int winner) {
	std::string item1 = winner == -1 ? numToString(player1Choice) : numToString(player2Choice);
	std::string item2 = winner == -1 ? numToString(player2Choice) : numToString(player1Choice);

	std::string verb = "";
	switch (winner == -1 ? numToChoice(player1Choice) : numToChoice(player2Choice)) {
		case 'r':
			verb = " smashes ";
			break;
		case 'p':
			verb = " wraps ";
			break;
		case 's':
			verb = " cuts ";
			break;
	}

	return item1 + verb + item2;
}

/**
	@param char player1Choice
		player1Choice should be either 'r', 'p', 's'
	@param char player2Choice
		player2Choice should be either 'r', 'p', 's'
	@return int num
		-1 = Player 1 won
		0 = Tie
		1 = Player 2 won
*/
int didPlayer1Win(char player1Choice, char player2Choice) {
	int ret = 1;

	if (player1Choice == player2Choice) {
		ret = 0;
	} else {
		char beats[3][2] = { { 'r','s' },{ 's','p' },{ 'p','r' } };
		for (int i = 0; i < sizeof(beats); i++) {
			if (player1Choice == beats[i][0]) {
				if (player2Choice == beats[i][1]) {
					ret = -1;
				}
				break;
			}
		}
	}
	return ret;
}

/**
	@param int num
		num should be in the range [1,3]
	@return char choice
		r = rock (num = 1)
		p = paper (num = 2)
		s = scissors (num = 3)
*/
char numToChoice(int num) {
	char choice = ' ';
	switch (num) {
		case 1:
			choice = 'r';
			break;
		case 2:
			choice = 'p';
			break;
		case 3:
			choice = 's';
			break;
	}
	return choice;
}

/**
@param int num
num should be in the range [1,3]
@return char choice
r = rock (num = 1)
p = paper (num = 2)
s = scissors (num = 3)
*/
std::string numToString(int num) {
	std::string choice = "";
	switch (num) {
	case 1:
		choice = "Rock";
		break;
	case 2:
		choice = "Paper";
		break;
	case 3:
		choice = "Scissors";
		break;
	}
	return choice;
}

/**
	@return int num
		a random number between [1,3]
*/
int computerChoice() {
	return (rand() % 3) + 1;
}