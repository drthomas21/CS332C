#include "ppmimage.h"
#include <string>
#include <iostream>
#include <cmath>
#include <stdint.h>

std::istream& operator>>(std::istream &input, PPMImage &source) {
	input >> source.magicNumber;
	input >> source.width;
	input >> source.height;
	input >> source.maxColor;

	if (source.colors != nullptr) {
		delete[] source.colors;
	}

	source.numOfChars = ceil(source.maxColor / pow(2, sizeof(unsigned char) * 8));
	source.colors = new unsigned char[static_cast<size_t>(source.width * source.height * source.numOfChars)];
	input >> source.colors;
}

std::ostream& operator<<(std::ostream &output, const PPMImage &source) {
	output << source.magicNumber << PPMImage::EOL;
	output << source.width << " " << source.height << PPMImage::EOL;
	output << source.maxColor << PPMImage::EOL;
	output << source.colors << PPMImage::EOL;
}

void PPMImage::hideData(const std::string &message) {
	std::string _message = message;
	_message.push_back('\0');
	unsigned int charSize = sizeof(unsigned char);

	if (this->width * this->height * this->numOfChars >= _message.size() * charSize) {
		size_t offset = this->numOfChars - 1;
		for (size_t i = 0; i < _message.size(); i++) {
			size_t shift = charSize;
			while (shift > 0) {
				shift--;

				offset += this->numOfChars;
				unsigned char binary = 1;
				unsigned char item = _message[i] & (binary << shift);
				this->colors[offset] = this->colors[offset] | item;
			}
		}
	} else {
		throw 201;
	}
}

std::string PPMImage::recoverData() {
	std::string message = "";
	unsigned int offset = this->numOfChars - 1;
	unsigned int size = this->width * this->height * this->numOfChars;

	
	unsigned char character = 0;
	unsigned char binaryChar = 0;
	while (character != '\0') {
		unsigned int shift = sizeof(unsigned char) * 8;
		binaryChar = 0;

		while (offset < size && shift > 0) {
			offset += this->numOfChars;
			shift--;

			unsigned char binary = 1;
			binaryChar = binaryChar | ((this->colors[offset] & binary) << shift);
		}
		
		if (offset >= size) {
			throw 202;
		}
		character = static_cast<unsigned char>(binaryChar);
		message.push_back(character);
	}
	
	return message;
}

void PPMImage::grayscale() {

}