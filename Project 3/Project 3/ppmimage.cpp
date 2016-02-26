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

	source.colors = new unsigned char[source.getSize() ];
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

	if (this->getSize() >= _message.size() * charSize) {
		size_t offset = 0;
		for (size_t i = 0; i < _message.size(); i++) {
			size_t shift = charSize;
			while (shift > 0) {
				shift--;

				offset += 1;
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
	unsigned int offset = 0;
	unsigned int size = this->getSize();

	
	unsigned char character = 0;
	unsigned char binaryChar = 0;
	while (character != '\0') {
		unsigned int shift = sizeof(unsigned char) * 8;
		binaryChar = 0;

		while (offset < size && shift > 0) {
			offset += 1;
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
	for (size_t i = 0; i < this->getSize(); i += 3) {
		unsigned int *rgb = this->getRGB(i);

		if (rgb != nullptr) {
			unsigned int newRgb[3] = { 0,0,0 };
			double multiplier[3] = { .299 , .587, .114 };
			unsigned int colorValue = 0;

			for (size_t i = 0; i < 3; i++) {
				colorValue += static_cast<unsigned int>(rgb[i] * multiplier[i]);
			}

			for (size_t i = 0; i < 3; i++) {
				int binary = rgb[i] & 1;
				newRgb[i] = colorValue;
				newRgb[i] = newRgb[i] | binary;
			}
			this->setRGB(i, newRgb);
			delete[] rgb;
		}
	}
}

void PPMImage::sepia() {
	for (size_t i = 0; i < this->getSize(); i += 3) {
		unsigned int *rgb = this->getRGB(i);

		if (rgb != nullptr) {
			unsigned int newRgb[3] = { 0,0,0 };

			double multiplier[3][3] = { 
				{ .393 , .769, .189 },
				{ .349 , .686, .168 },
				{ .272 , .534, .131 }
			};
			unsigned int colorValues[3] = { 0,0,0 };

			for (size_t i = 0; i < 3; i++) {
				for (size_t j = 0; j < 3; j++) {
					colorValues[i] += static_cast<unsigned int>(rgb[j] * multiplier[i][j]);
				}
			}

			for (size_t i = 0; i < 3; i++) {
				int binary = rgb[i] & 1;
				newRgb[i] = colorValues[i];
				newRgb[i] = newRgb[i] | binary;
			}
			this->setRGB(i, newRgb);
			delete[] rgb;
		}
	}
}

void PPMImage::negative() {
	for (size_t i = 0; i < this->getSize(); i += 3) {
		unsigned int *rgb = this->getRGB(i);

		if (rgb != nullptr) {
			unsigned int newRgb[3] = { 0,0,0 };
			unsigned int colorValues[3] = { 0,0,0 };

			for (size_t i = 0; i < 3; i++) {
				colorValues[i] += static_cast<unsigned int>(255 - rgb[i]);
			}

			for (size_t i = 0; i < 3; i++) {
				int binary = rgb[i] & 1;
				newRgb[i] = colorValues[i];
				newRgb[i] = newRgb[i] | binary;
			}
			this->setRGB(i, newRgb);
			delete[] rgb;
		}
	}
}

size_t PPMImage::getSize() {
	return static_cast<size_t>(this->width * this->height);
}

unsigned int* PPMImage::getRGB(size_t index) {
	unsigned int *colors = nullptr;
	if (index % 3 == 0) {
		colors = new unsigned int[3];
		colors[0] = 0;
		colors[1] = 0;
		colors[2] = 0;

		for (size_t i = 0; i < 3; i++) {
			colors[i] = colors[i] | this->colors[i + index];
		}
	}

	return colors;
}

void PPMImage::setRGB(size_t index, unsigned int* rgb) {
	if (index % 3 == 0) {
		for (size_t i = 0; i < 3; i++) {
			this->colors[i + index] = rgb[i] & (1 >> sizeof(unsigned int) - sizeof(char));			
		}
	}
}

PPMImage::PPMImage() {

}
PPMImage::PPMImage(const PPMImage& source) {
	if (this->colors != nullptr) {
		delete[] this->colors;
	}

	this->colors = source.colors;
	this->magicNumber = source.magicNumber;
	this->height = source.height;
	this->width = source.width;
	this->maxColor = source.maxColor;

}
PPMImage::~PPMImage() {
	delete[] this->colors;
}
PPMImage PPMImage::operator=(const PPMImage& source) {
	if (this->colors != nullptr) {
		delete[] this->colors;
	}

	this->colors = source.colors;
	this->magicNumber = source.magicNumber;
	this->height = source.height;
	this->width = source.width;
	this->maxColor = source.maxColor;
}