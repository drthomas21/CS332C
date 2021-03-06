#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>

class Person {
	std::string name;
	double accuracy;
	bool dead;
	unsigned int won;

public:
	Person() {
		this->name = "";
		this->accuracy = 0;
		this->dead = true;
		this->won = 0;
	}
	Person(std::string name, double accuracy) {
		this->name = name;
		this->accuracy = accuracy;
		this->dead = false;
		this->won = 0;
	}
	void died() {
		this->dead = true;
	}
	void alive() {
		this->dead = false;
	}
	void hasWon() {
		this->won++;
	}
	bool isDead() {
		return this->dead;
	}
	std::string getName() {
		return this->name;
	}
	double getAccuracy() {
		return this->accuracy;
	}
	unsigned int getMatchesWon() {
		return this->won;
	}
	bool isEqual(Person player) {
		return this->name.compare(player.getName()) == 0;
	}
	bool hasGreaterAccuracy(Person player) {
		return this->accuracy > player.getAccuracy();
	}
};

void strategy1(unsigned int, Person[], int);
void strategy2(unsigned int, Person[], int);
void reset(Person[], int);
int numOfAlivePlayers(Person[], int);
void alivePlayersWon(Person[], int);
bool playerHitsTarget(Person&);
Person* getTarget(Person&, Person[], int);

int main() {
	srand(static_cast<unsigned int>(time(NULL)));
	//Intro
	std::cout << "Welcome to Dueling Doofuses" << std::endl;

	//Data
	Person players[3] = { Person("Jason",(1.0 / 3.0)),Person("Kyle",(1.0 / 2.0)),Person("Lenny",1.0) };
	int size = 3;
	unsigned int limit = 100000;

	int choice;
	do {
		std::cout << "Which strategy would you like to use? \n\t(1) Normal \n\t(2) Jason always misses first shot\n:";
		std::cin >> choice;
		if (std::cin.fail()) {
			std::cout << "Invalid value" << std::endl;
			choice = 0;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		}
	} while (choice < 1 || choice > 2);
	//Loops
	std::cout << "Running simulation, please wait patiently..." << std::endl;
	if (choice == 1) {
		strategy1(limit, players, size);
	}
	else {
		strategy2(limit, players, size);
	}
	std::cout << "Finished simulation" << std::endl;

	for (int i = 0; i < size; i++) {
		std::cout << players[i].getName() << "'s Record: " << players[i].getMatchesWon() << "/" << limit << " = " << ((double)players[i].getMatchesWon() / (double)limit * 100.0) << std::endl;
	}

	return 0;
}

/**
	Normal Strategy
	@param unsigned int limit
		how many turns
	@param array(Person)
		list of players
	@param int size
		number of players
*/
void strategy1(unsigned int limit, Person players[], int size) {
	unsigned int turn = 0;
	do {
		do {
			//Match
			for (int i = 0; i < size; i++) {
				if (players[i].isDead()) {
					continue;
				}

				if (playerHitsTarget(players[i])) {
					Person* target = getTarget(players[i], players, size);
					(*target).died();
				}
			}
		} while (numOfAlivePlayers(players, size) > 1);
		alivePlayersWon(players, size);
		turn++;
		reset(players, size);
	} while (turn < limit);
}

/**
	Jason Always Misses First Shot
	@param unsigned int limit
		how many turns
	@param array(Person)
		list of players
	@param int size
		number of players
*/
void strategy2(unsigned int limit, Person players[], int size) {
	unsigned int turn = 0;
	unsigned int unsignedSize = static_cast<unsigned int>(size);
	do {
		bool firstRound = true;
		do {
			//Match
			for (int i = 0; i < size; i++) {
				if (players[i].isDead()) {
					continue;
				}

				//Jason has to miss first shot
				if (playerHitsTarget(players[i]) && ((firstRound && players[i].getName().compare("Jason") != 0) || !firstRound)) {
					Person* target = getTarget(players[i], players, size);
					(*target).died();
				}
			}
			firstRound = false;
		} while (numOfAlivePlayers(players, size) > 1);
		alivePlayersWon(players, size);
		turn++;
		reset(players, size);
	} while (turn < limit);
}

/**
	@param array(Person) players
		an array of Persons
	@param int size
		number of players
*/
void reset(Person players[], int size) {
	for (int i = 0; i < size; i++) {
		players[i].alive();
	}
}

/**
	@param array(Person) players
		an array of Persons
	@param int size
		number of players
*/
int numOfAlivePlayers(Person players[], int size) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (!players[i].isDead()) {
			count++;
		}
	}
	return count;
}

/**
	@param array(Person) players
		an array of Persons
	@param int size
		number of players
*/
void alivePlayersWon(Person players[], int size) {
	for (int i = 0; i < size; i++) {
		if (!players[i].isDead()) {
			players[i].hasWon();
		}
	}
}

/**
	@param Person player
		the person that is shooting
	@return bool hitsTarget
*/
bool playerHitsTarget(Person &player) {
	return (rand() % 100) < (player.getAccuracy() * 100);
}

/**
	@param Person self
		the current shooter
	@param array(Person) players
		an array of Persons
	@param int size
		number of players
	@return Person target
*/
Person* getTarget(Person &self, Person players[], int size) {
	if (size == 0) {
		return nullptr;
	}
	else if (size == 1 && self.isEqual(players[0])) {
		return nullptr;
	}

	Person *target = NULL;
	for (int i = 0; i < size; i++) {
		if (self.isEqual(players[i]) || players[i].isDead()) {
			continue;
		}
		else if (target == NULL) {
			target = &players[i];
		}
		else if (!players[i].isEqual(*target) && players[i].hasGreaterAccuracy(*target)) {
			target = &players[i];
		}
	}
	return target;
}
