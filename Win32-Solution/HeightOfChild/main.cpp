#include <iostream>

double childHeight(double, double, bool = true);
int main() {
	double fatherHeight, motherHeight;

	//Intro
	std::cout << "Welcome to Child Height Prediction Program" << std::endl;
	
	while (true) {
		char resp;
		std::cout << "Would you like to predict your child height? (y/n) ";
		std::cin >> resp;
		//clear char buffer from extra characters
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');

		//Process resp
		if (resp == 'n' || resp == 'N') {
			//End program
			break;
		}
		else if (resp == 'y' || resp == 'Y') {
			//Get Data
			do {
				std::cout << "What is the father and mother height? ";
				std::cin >> fatherHeight >> motherHeight;
				if (std::cin.fail()) {
					std::cout << "Invalid value" << std::endl;
					fatherHeight = 0;
					motherHeight = 0;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<int>::max(), '\n');
					continue;
				}
			} while (fatherHeight <= 0 && motherHeight <= 0);

			do {
				resp = NULL;
				std::cout << "Is the child a male? (y/n) ";
				std::cin >> resp;
				//clear char buffer from extra characters
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			} while (resp != 'Y' && resp != 'y' && resp != 'N' && resp != 'n');

			std::cout << "The predicted child height is: " << childHeight(fatherHeight, motherHeight, (resp == 'Y' || resp == 'y')) << std::endl;
			
		}
	}

	std::cout << "Thank you for using this program :) ";
	return 0;
}

double childHeight(double fatherHeight, double motherHeight, bool isMale) {
	return isMale ? ((motherHeight * (13.0 / 12.0)) + fatherHeight) / 2.0 : ((motherHeight * (12.0 / 13.0)) + fatherHeight) / 2.0;
}