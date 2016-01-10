#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

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
	Person players[3] = {Person("Jason",(1.0/3.0)),Person("Kyle",(1.0/2.0)),Person("Lenny",1.0)};
	int size = 3;
	unsigned int limit = 100000;
	unsigned int turn = 0;

	//Loops
	do {
		std::cout << "Match " << (turn+1) << std::endl;
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

	for (int i = 0; i < size; i++) {
		std::cout << players[i].getName() << "'s Record: " << players[i].getMatchesWon() << "/" << limit << " = " << ((double)players[i].getMatchesWon() / (double)limit * 100.0) << std::endl;
	}

	return 0;
}

/**
	@param array(Person) players
		an array of Persons
*/
void reset(Person players[], int size) {
	for (int i = 0; i < size; i++) {
		players[i].alive();
	}
}

/**
	@param array(Person) players
		an array of Persons
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
	@param array(Person) players
		an array of Persons
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
