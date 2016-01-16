#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>

const int SIZE = 10;

int main() {

}

//Shifts the array
void arrayShift(int list[]) {
	int headValue = list[0];
	for (int i = 0; i < SIZE - 1; i++) {
		list[i] = list[i + 1];
	}
	list[SIZE - 1] = headValue;
}

void arraySwap(int list[]) {
	int newList[SIZE];
	
	for (int i = 1; i < SIZE-1; i++) {
		newList[i] = list[i-1] > list[i+1] ? list[i-1] : list[i+1];
	}
	newList[0] = list[0];
	newList[SIZE - 1] = list[SIZE - 1];
	list = newList;
}

void arraySort(int list[]) {
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
	
	list = newList;
}

bool isInOrder(int list[], bool asc = true) {
	if (asc) {
		for (int i = 0; i < SIZE-1; i++) {
			if (list[i] > list[i + 1]) {
				return false;
			}
		}
	} else {
		for (int i = 0; i < SIZE - 1; i++) {
			if (list[i] < list[i + 1]) {
				return false;
			}
		}
	}

	return true;
}

bool hasAdjancent(int list[], int min = 3) {
	int count = 0;
	int match = list[0];
	for (int i = 1; i < SIZE; i++) {
		if (match == list[i]) {
			count++;

			if (count >= min) {
				return true;
			}
		} else {
			match = list[i];
			count = 0;
		}
	}
	return false;
}