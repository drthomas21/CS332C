#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>

const int SIZE = 10;

void printList(const int[], std::string);

//Method 1
void arrayShift(const int[], int);

//Method 2
void arraySwap(const int[]);

//Method 3
void arraySort(const int[]);

//Method 4
void isInOrder(const int[], bool);

//Method 5
void hasAdjancent(const int[], int);

//Method 6
void hasDuplicate(const int[]);
int main() {
	srand(static_cast<unsigned int>(time(NULL)));
	std::cout << "Welcome to Array Manipulation" << std::endl;
	int choice = -1, amount = -1, list[SIZE];

	for (int i = 0; i < SIZE; i++) {
		list[i] = (int)(rand() % 20)+1;
	}

	do {
		printList(list, "Original Array");
		std::cout
			<< "Choose :" << std::endl
			<< "\t1 - Method 1: Shift Array" << std::endl
			<< "\t2 - Method 2: Swapping Array" << std::endl
			<< "\t3 - Method 3: Reordering Array" << std::endl
			<< "\t4 - Method 4: Is In Order" << std::endl
			<< "\t5 - Method 5: Has Adjancent Numbers" << std::endl
			<< "\t6 - Method 6: Has Duplicated" << std::endl
			<< "\t0 - To Exit" << std::endl;
		std::cout << ": ";
		std::cin >> choice;
		if (std::cin.fail()) {
			std::cout << "Invalid value" << std::endl;
			choice = -1;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			continue;
		}
		
		switch (choice) {
			case 1:
				do {
					std::cout << "Shift Amount? ";
					std::cin >> amount;
					if (std::cin.fail()) {
						std::cout << "Invalid value" << std::endl;
						amount = -1;
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<int>::max(), '\n');
						continue;
					}
				} while (amount < 0);
				arrayShift(list, amount);
				break;
			case 2:
				arraySwap(list);
				break;
			case 3:
				arraySort(list);
				break;
			case 4:
				isInOrder(list, true);
				break;
			case 5:
				hasAdjancent(list, 3);
				break;
			case 6:
				hasDuplicate(list);
				break;
		}
	} while (choice != 0);
}

void printList(const int list[],std::string label) {
	std::cout << label << " [";
	for (int i = 0; i < SIZE - 1; i++) {
		std::cout << list[i] << ", ";
	}
	std::cout << list[SIZE - 1] << "]" << std::endl;
}

//Method 1
void arrayShift(const int list[],int amount = 0) {
	int newList[SIZE];
	for (int i = 0; i < SIZE; i++) {
		int c = (amount + i) % SIZE;
		newList[i] = list[c];
	}
	printList(newList, "Method 01");
}

//Method 2
void arraySwap(const int list[]) {
	int newList[SIZE];
	
	for (int i = 1; i < SIZE-1; i++) {
		newList[i] = list[i-1] > list[i+1] ? list[i-1] : list[i+1];
	}
	newList[0] = list[0];
	newList[SIZE - 1] = list[SIZE - 1];
	printList(newList, "Method 02");
}

//Method 3
void arraySort(const int list[]) {
	int newList[SIZE];
	int oddList[SIZE];

	int ePointer = 0;
	int oPointer = 0;

	for (int i = 0; i < SIZE; i++) {
		if (list[i] % 2 == 0) {
			newList[ePointer] = list[i];
			ePointer++;
		} else {
			oddList[oPointer] = list[i];
			oPointer++;
		}
	}

	for (int i = 0; i < oPointer; i++) {
		newList[ePointer + i] = oddList[i];
	}
	
	printList(newList, "Method 03");
}

//Method 4
void isInOrder(const int list[], bool asc = true) {
	bool ret = true;
	if (asc) {
		for (int i = 0; i < SIZE-1; i++) {
			if (list[i] > list[i + 1]) {
				ret = false;
				break;
			}
		}
	} else {
		for (int i = 0; i < SIZE - 1; i++) {
			if (list[i] < list[i + 1]) {
				ret = false;
				break;
			}
		}
	}

	std::cout << "Method 04: " << (ret ? "True" : "False") << std::endl;
}

//Method 5
void hasAdjancent(const int list[], int min = 3) {
	int count = 0;
	int match = list[0];
	bool ret = false;
	for (int i = 1; i < SIZE; i++) {
		if (match == list[i]) {
			count++;

			if (count >= min) {
				ret = true;
				break;
			}
		} else {
			match = list[i];
			count = 0;
		}
	}
	std::cout << "Method 05: " << (ret ? "True" : "False") << std::endl;
}

//Method 6
void hasDuplicate(const int list[]) {
	std::string found = "";
	bool ret = false;

	for (int i = 1; i < SIZE; i++) {
		if (found.find(list[i] + ",") != std::string::npos) {
			ret = true;
			break;
		} else {
			found += list[i] + ",";
		}
	}

	std::cout << "Method 06: " << (ret ? "True" : "False") << std::endl;
}