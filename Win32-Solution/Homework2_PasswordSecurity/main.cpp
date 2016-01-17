#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>
#include <cmath>

const int PIN = 59240;
const int MODE = 1;

void showMap(const int[]);
bool isValid(const int[], int);
bool isValid(const int[], int, int);
void simpleMode();
void advanceMode();

int main() {
	srand(static_cast<unsigned int>(time(NULL)));
	std::cout << "Welcome to Password Security" << std::endl;
	switch (MODE) {
		case 1:
			simpleMode();
			break;
		case 2:
			advanceMode();
			break;
	}
}

//Shows the key map
void showMap(const int map[]) {
	std::cout << "PIN:\t";
	for (int i = 0; i < 10; i++) {
		std::cout << i << " ";
	}

	std::cout << std::endl;

	std::cout << "NUM:\t";
	for (int i = 0; i < 10; i++) {
		std::cout << map[i] << " ";
	}

	std::cout << std::endl;
}

//Checks if the passcode matches the PIN's hashedPin
bool isValid(const int keyMap[], int passcode) {
	int hashedPin = 0;
	std::string stringPin = std::to_string(PIN);
	for (int i = 0; i < stringPin.length(); i++) {
		int c = stringPin.at(i) -'0';
		hashedPin += (int)pow(10, stringPin.length() - i - 1) * keyMap[c];
	}

	return hashedPin == passcode;
}

//Checks if the passcode matches the PIN's hashedPin for a specific position
bool isValid(const int keyMap[], int passcode, int pos) {
	int hashedPin = 0;
	std::string stringPin = std::to_string(PIN);
	int c = stringPin.at(pos) - '0';
	hashedPin = keyMap[c];
	return hashedPin == passcode;
}

//The basics
void simpleMode() {
	int passcode, keyMap[10];
	bool passed = false;

	std::cout << "Using Simple Mode: Input the whole PIN" << std::endl;
	do {
		for (int i = 0; i < 10; i++) {
			keyMap[i] = (int)(rand() % 3) + 1;
		}

		showMap(keyMap);
		std::cout << "Passcode: ";
		std::cin >> passcode;
		if (std::cin.fail()) {
			std::cout << "Invalid value" << std::endl;
			passcode = 0;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			continue;
		}
		passed = isValid(keyMap, passcode);
		if (!passed) {
			std::cout << "Incorrect PIN" << std::endl;
		}
	} while (!passed);
	std::cout << "Login Successful" << std::endl;
}

//Adding in max number of attempts, adding in the hash map changes after each guess
void advanceMode() {
	char passcode;
	int attempts = 0, keyMap[10], step = 0, maxAttempts = 3;
	bool passed = false;
	std::string labels[] = { "First","Second","Third","Forth","Fifth","Sixth","Seventh","Eighth","Nineth","Tenth" }, stringPin = std::to_string(PIN);

	std::cout << "Using Advanced Mode:" << std::endl;
	do {
		for (int i = 0; i < 10; i++) {
			keyMap[i] = (int)(rand() % 3) + 1;
		}

		showMap(keyMap);
		std::cout << "Input The " << labels[step] << " Number Of The Pin" << std::endl;
		std::cin >> passcode;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		if (!isValid(keyMap, passcode - '0', step)) {
			attempts++;
		} else {
			step++;
			if (step >= stringPin.length()) {
				break;
			}
		}
	} while (attempts < maxAttempts);

	if (attempts == maxAttempts) {
		std::cout << "Account is locked" << std::endl;
	} else {
		std::cout << "Login Successful" << std::endl;
	}
}