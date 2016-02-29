#include "ppmimage.h"
#include <iostream>
#include <fstream>
#include <string>

/**
Error Messages:
1xx I/O error
	101 - failed to read image
	102 - failed to write image
2xx Message R/W error
	201 - message is too large
	202 - no message found
**/

#define FAILED_READ_IMAGE 101
#define FAILED_WRITE_IMAGE 102
#define FAILED_MESSAGE_TOO_LAGER 201
#define FAILED_MESSAGE_NOT_FOUND 202

int main() {
	char choice = 0;
	std::string iFilename = "";
	std::string oFilename = "";
	PPMImage image;
	std::string message = "";
	do {
		//Which file
		if (iFilename.empty()) {
			std::cout << "Please name the image that you would like to work with: ";
			std::cin >> iFilename;

			//Check if file exists
			std::ifstream fileReader;
			fileReader.open(iFilename, std::ios::in | std::ios::binary);
			if (!fileReader.is_open()) {
				std::cout << "Failed to open file at: " << iFilename << std::endl;
				iFilename.clear();
				continue;
			}

			try {
				fileReader >> image;
				fileReader.close();
				std::cout << std::endl;
			} catch (int e) {
				switch (e) {
					case FAILED_READ_IMAGE:
						std::cout << "Failed to read file at: " << iFilename << std::endl;
						break;
					case FAILED_WRITE_IMAGE:
						std::cout << "Failed to write to file at: " << iFilename << std::endl;
						break;
					case FAILED_MESSAGE_TOO_LAGER:
						std::cout << "Message is too large for image" << std::endl;
						break;
					case FAILED_MESSAGE_NOT_FOUND:
						std::cout << "Cannot find message" << std::endl;
						break;
				}
				iFilename.clear();
			}
		}

		std::cout << "Current Image: " << iFilename << std::endl;
		std::cout << "What would you like to do:" << std::endl
			<< "\ta) Hide a message" << std::endl
			<< "\tb) Retrieve a message" << std::endl

			<< "\tc) Apply filter Sepia" << std::endl
			<< "\td) Apply filter Greyscale" << std::endl
			<< "\te) Apply filter Negative" << std::endl<< std::endl

			<< "\t1) Load another image" << std::endl
			<< "\t2) Save image" << std::endl
			<< "\t3) Exit" << std::endl
			<< "?";
		std::cin >> choice;

		switch (choice) {
			case 'A':
			case 'a':
				message.clear();
				while (message.empty()) {
					std::cout << "What message? ";
					std::cin >> message;
					try {
						image.hideData(message);
						std::cout << "Message hidden" << std::endl;
					} catch (int e) {
						if (e == FAILED_MESSAGE_TOO_LAGER) {
							std::cout << "Message was too large, try again" << std::endl;
							message.clear();
						}
					}					
				}
				break;

			case 'B':				
			case 'b':
				message.clear();
				try {
					message = image.recoverData();
					std::cout << "Retrieved message: " << message << std::endl;
				}
				catch (int e) {
					if (e == FAILED_MESSAGE_NOT_FOUND) {
						std::cout << "The image did not have an image" << std::endl;
						message.clear();
					}
				}
				break;

			case 'C':
			case 'c':
				image.sepia();
				break;

			case 'D':
			case 'd':
				image.grayscale();
				break;

			case 'E':
			case 'e':
				image.negative();
				break;

			case '1':
				iFilename.clear();
				continue;
			case '2':
				oFilename.clear();
				while (oFilename.empty()) {
					std::cout << "Output filename? ";
					std::cin >> oFilename;
					
					std::ofstream fileWriter;
					fileWriter.open(oFilename, std::ios::out | std::ios::binary);
					if (!fileWriter.is_open()) {
						std::cout << "Cannot write to file: " << oFilename << std::endl;
						oFilename.clear();
						continue;
					}

					try {
						fileWriter << image;
						fileWriter.close();
						std::cout << "File saved" << std::endl << std::endl;
					} catch (int e) {
						if (e == FAILED_WRITE_IMAGE) {
							std::cout << "Cannot write to file: " << oFilename << std::endl;
							oFilename.clear();
						}
					}
				}
				break;
			case '3':
				std::cout << "Good Bye!" << std::endl;
				break;
		}
	} while (choice != '3');
	return 0;
}