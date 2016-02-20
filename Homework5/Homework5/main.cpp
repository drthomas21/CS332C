#include "myset.h"
#include <vector>
#include <iostream>
#include <limits>
#include <ctime>
#include <cstdlib>

int main() {
	srand(static_cast<unsigned int>(time(NULL)));
	std::vector<int> set1(10,0);
	set1[9] = 31;
	set1[8] = 30;
	set1[7] = 24;
	set1[6] = 15;
	set1[5] = 13;
	set1[4] = 10;
	set1[3] = 9;
	set1[2] = 5;
	set1[1] = 4;
	set1[0] = 2;
	MySet obj1(set1);

	std::cout << "Set 1: " << obj1 << std::endl << std::endl;

	//Insert
	for (int i = 0; i < 20; i++) {
		int randNum = rand() % 1000;
		std::cout << "Lets insert " << randNum << " into the set";
		obj1.insert(randNum);
		std::cout << obj1 << std::endl << std::endl;
	}

	//Remove
	for (int i = 0; i < 20; i++) {
		int randNum = rand() % 20;
		std::cout << "Lets remove " << randNum << " into the set";
		obj1.remove(randNum);
		std::cout << obj1 << std::endl << std::endl;
	}
	

	//New Set
	std::vector<int> set2(30,0);
	for (int i = 0; i < set2.size(); i++) {
		set2[i] = rand() % 1000;
	}
	MySet obj2(set2);
	std::cout << "Set 2: " << obj2 << std::endl;

	//Add
	std::cout << "Set 1 + Set 2: ";
	MySet _temp1 = obj1 + obj2;
	std::cout << _temp1 << std::endl;

	//Sub
	std::cout << "Set 1 - Set 2: ";
	MySet _temp2 = obj1 - obj2;
	std::cout << _temp2 << std::endl;

	//Intersect
	std::cout << "Set 1 & Set 2: ";
	MySet _temp3 = obj1 & obj2;
	std::cout << _temp3 << std::endl;

	return 0;
}
