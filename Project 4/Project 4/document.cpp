#include "document.h"
#include <set>
#include <string>
#include <regex>
#include <algorithm>
#include <iostream>

const std::set<std::string> Document::getSet() {
	return this->characters;
}

void Document::addToSet(const std::string word) {
	std::regex regex("^[^A-Za-z0-9]*([A-Za-z0-9]+)[^A-Za-z0-9]*$");
	std::smatch matches;
	if (std::regex_match(word, matches, regex)) {
		std::string _word = matches[1].str();
		std::transform(_word.begin(), _word.end(), _word.begin(), ::tolower);
		this->characters.insert(_word);
	}
}

double Document::similarity(const std::set<std::string> &query) {
	std::set<std::string> matches;
	
	if (query.size() < this->characters.size()) {
		for (std::set<std::string>::iterator item = query.begin(); item != query.end(); item++) {
			if (this->characters.find(*item) != this->characters.end()) {
				matches.insert(*item);
			}
		}
	} else {
		for (std::set<std::string>::iterator item = this->characters.begin(); item != this->characters.end(); item++) {
			if (query.find(*item) != query.end()) {
				matches.insert(*item);
			}
		}
	}

	return ((double)matches.size()) / (sqrt(query.size()) * sqrt(this->characters.size()));	
}

std::istream& operator>>(std::istream &input, Document &source) {
	std::cout << "Reading file..." << std::endl;
	while (!input.eof()) {
		std::string word;
		input >> word;
		source.addToSet(word);
	}
	return input;
}

Document::Document() { }
Document::Document(const Document &source) :characters(source.characters) { }
Document Document::operator=(const Document &source) {
	this->characters = source.characters;
	return *this;
}