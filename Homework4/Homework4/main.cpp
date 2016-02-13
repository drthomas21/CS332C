#include "polynomial.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>
#include <cmath>

void printObjects(Polynomial*, int);

int main() {
	srand(static_cast<unsigned int>(time(NULL)));

	//Create objects
	const int size = 4;
	std::cout << "Creating "<< size << " Polynomials" << std::endl;
	Polynomial objs[size];
	for (int i = 0; i < size; i++) {
		objs[i] = Polynomial(rand() % 6 + 2);
	}

	//Input coefficients
	for (int i = 0; i < size; i++) {
		std::cout << "Polynomial #" << (i + 1) << ": Input " << objs[i].getSize() << " coefficients: ";
		std::cin >> objs[i];
		if (std::cin.fail()) {
			std::cout << "Invalid value" << std::endl;
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			continue;
		}
		//std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	}

	//Showing created coefficients
	printObjects(objs, size);

	//Lets do some math
	std::cout << "Adding Polynomials [Press Enter To Continue]" << std::endl;
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << "Adding Polynomial #" << (i + 1) << ": " << objs[i] << " to " << "Polynomial #" << (j + 1) << ": " << objs[j] << std::endl;
			Polynomial item = objs[i] + objs[j];
			std::cout << item << std::endl << std::endl;
		}
	}

	std::cout << "Subtracting Polynomials [Press Enter To Continue]" << std::endl;
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << "Subtracting Polynomial #" << (i + 1) << ": " << objs[i] << " and " << "Polynomial #" << (j + 1) << ": " << objs[j] << std::endl;
			Polynomial item = objs[i] - objs[j];
			std::cout << item << std::endl << std::endl;
		}
	}

	//Compare
	std::cout << "Comparing polynomials Polynomials [Press Enter To Continue]" << std::endl;
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << "Is Polynomial #" << (i + 1) << ": " << objs[i] << " equal to " << "Polynomial #" << (j + 1) << ": " << objs[j] << std::endl;
			std::cout << (objs[i] == objs[j] ? "Yes!" : "No!") << std::endl << std::endl;
		}
	}

	//Compound Assignment
	std::cout << "Compound assignments [Press Enter to Continue]" << std::endl;
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	int i = rand() % size;
	int j = rand() % size;
	std::cout << "Polynomial #" << (i + 1) << ": " << objs[i] << " += " << "Polynomial #" << (j + 1) << ": " << objs[j] << std::endl;
	objs[i] += objs[j];
	std::cout << objs[i] << std::endl << std::endl;

	i = rand() % size;
	j = rand() % size;
	std::cout << "Polynomial #" << (i + 1) << ": " << objs[i] << " -= " << "Polynomial #" << (j + 1) << ": " << objs[j] << std::endl;
	objs[i] -= objs[j];
	std::cout << objs[i] << std::endl << std::endl;;

	//Sign flipped
	std::cout << "Flipping sign [Press Enter to Continue]" << std::endl;
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	i = rand() % size;
	std::cout << "Polynomial #" << (i + 1) << ": " << objs[i] << " to be flipped "<< std::endl;
	-objs[i];
	std::cout << objs[i] << std::endl << std::endl;

	//Showing created coefficients
	std::cout << "Final Output [Press Enter to Continue]" << std::endl;
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	printObjects(objs, size);
}

void printObjects(Polynomial* objs, int size) {
	for (int i = 0; i < size; i++) {
		std::cout << "Polynomial #" << (i + 1) << ": " << objs[i] << std::endl;
	}
}