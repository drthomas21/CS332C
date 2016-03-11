#include "document.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

#ifndef _WIN32
#include <boost/regex.hpp>
#endif

#ifdef _WIN32
#include <regex>
#endif

int main() {
	Document document;
	std::string filename;
	std::ifstream fileReader;
	std::set<std::string> query;
	std::string line;
	std::string word;

	do {
		std::cout << "Enter a document you want to query: ";
		std::cin >> filename;
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');

		fileReader.open(filename, std::ios::in);
		if (!fileReader.is_open()) {
			std::cout << "Failed to open file at: " << filename << std::endl;
			filename.clear();
			continue;
		}
	} while (filename.empty());
	
	fileReader >> document;

	std::cout << "Enter a query: ";
	std::getline(std::cin, line);
	std::istringstream stream(line);
	while (stream >> word) {
		std::regex regex("^[^A-Za-z0-9]*([A-Za-z0-9]+)[^A-Za-z0-9]*$");
		std::smatch matches;
		if (std::regex_match(word, matches, regex)) {
			std::string _word = matches[1].str();
			std::transform(_word.begin(), _word.end(), _word.begin(), ::tolower);
			query.insert(_word);
		}		
	}

	std::cout << std::endl << "The similarity between the query and document is: " << document.similarity(query) << std::endl;
	return 0;
}
