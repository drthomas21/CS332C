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

	std::cout << std::endl << std::endl;
	

	//New Set
	std::vector<int> set2(30,0);
	for (int i = 0; i < set2.size(); i++) {
		set2[i] = rand() % 1000;
	}
	MySet obj2(set2);
	std::cout << "Set 2: " << obj2 << std::endl;

	std::vector<int> set3(30, 0);
	for (int i = 0; i < set3.size(); i++) {
		set3[i] = rand() % 1000;
	}
	MySet obj3(set3);
	std::cout << "Set 3: " << obj3 << std::endl;

	//Add
	std::cout << "Set 3 + Set 2: ";
	MySet _temp1 = obj3 + obj2;
	std::cout << _temp1 << std::endl << std::endl;

	//Sub
	std::cout << "Set 3 - Set 2: ";
	MySet _temp2 = obj3 - obj2;
	std::cout << _temp2 << std::endl << std::endl;

	//Intersect
	std::cout << "Set 3 & Set 2: ";
	MySet _temp3 = obj3 & obj2;
	std::cout << _temp3 << std::endl << std::endl;

	//Equals
	std::cout << "Set 3 == Set 2: ";
	std::cout << (obj3 == obj2 ? "Yes" : "No") << std::endl << std::endl << std::endl;

	//New Set
	std::vector<int> set4(30, 0);
	for (int i = 0; i < set4.size(); i++) {
		set4[i] = rand() % 1000;
	}
	MySet obj4(set4);
	std::cout << "Set 4: " << obj4 << std::endl;

	MySet obj5(set4);
	std::cout << "Set 5: " << obj5 << std::endl;

	//Equals
	std::cout << "Set 4 == Set 5: ";
	std::cout << (obj4 == obj5 ? "Yes" : "No") << std::endl;

	return 0;
}
