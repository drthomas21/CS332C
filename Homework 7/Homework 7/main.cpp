#include <iostream>
#include <vector>
#include <map>
#include <limits>

int main() {
	int input;
	std::vector<int> inputtedGrades;
	std::map<int, int> grades;
	do {
		std::cout << "Input a grade: ";
		std::cin >> input;
		if (std::cin.fail()) {
			std::cout << "Invalid Input" << std::endl;
			input = 0;
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		} else {
			if (input >= 0) {
				inputtedGrades.push_back(input);
			} else if(input != -1) {
				std::cout << "Invalid Input" << std::endl;
			}
		}
	} while (input != -1);


	//Move Vector to Map
	for (size_t i = 0; i < inputtedGrades.size(); i++) {
		std::map<int, int>::iterator it;
		it = grades.find(inputtedGrades[i]);
		if (it == grades.end()) {
			grades[inputtedGrades[i]] = 0;
		}

		grades[inputtedGrades[i]]++;
	}

	//Display Map
	std::map<int, int>::iterator it;
	for (it = grades.begin(); it != grades.end(); it++) {
		std::cout << it->second << " grade"<< (it->second == 1 ? "" :"s") << " of " << it->first << std::endl;
	}
}