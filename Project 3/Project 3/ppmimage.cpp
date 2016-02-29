#include "ppmimage.h"
#include <string>
#include <iostream>
#include <cmath>
#include <stdint.h>

std::istream& operator>>(std::istream &input, PPMImage &source) {
	input >> source.magicNumber >> source.width >> source.height >> source.maxColor;

	if (source.colors != nullptr) {
		delete[] source.colors;
	}

	source.colors = new unsigned char[source.getSize() ];
	char *_unsignedChars = new char[source.getSize()];
	input.seekg(source.getSize()*-1, input.end);
	input.read(_unsignedChars, source.getSize());
	for (size_t i = 0; i < source.getSize(); i++) {
		source.colors[i] = static_cast<unsigned char>(_unsignedChars[i]);
	}
	delete[] _unsignedChars;
	return input;
}

std::ostream& operator<<(std::ostream &output, const PPMImage &source) {
	output << source.magicNumber << PPMImage::EOL;
	output << source.width << " " << source.height << PPMImage::EOL;
	output << source.maxColor << PPMImage::EOL;
	for (size_t i = 0; i < source.getSize(); i++) {
		output << source.colors[i];
	}
	output << PPMImage::EOL;
	
	return output;
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
	size_t size = this->getSize();

	
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
		std::uint8_t *rgb = this->getRGB(i);

		if (rgb != nullptr) {
			std::uint8_t newRgb[3] = { 0,0,0 };
			double multiplier[3] = { .299 , .587, .114 };
			double colorValue = 0;

			for (size_t i = 0; i < 3; i++) {
				colorValue += (double)rgb[i] * multiplier[i];
			}

			for (size_t i = 0; i < 3; i++) {
				newRgb[i] = static_cast<std::uint8_t>(colorValue);
			}
			this->setRGB(i, newRgb);
			delete[] rgb;
		}
	}
}

void PPMImage::sepia() {
	for (size_t i = 0; i < this->getSize(); i += 3) {
		std::uint8_t *rgb = this->getRGB(i);

		if (rgb != nullptr) {
			std::uint8_t newRgb[3] = { 0,0,0 };

			double multiplier[3][3] = { 
				{ .393 , .769, .189 },
				{ .349 , .686, .168 },
				{ .272 , .534, .131 }
			};
			double colorValues[3] = { 0,0,0 };

			for (size_t i = 0; i < 3; i++) {
				for (size_t j = 0; j < 3; j++) {
					colorValues[i] += (double)rgb[j] * multiplier[i][j];
				}
			}

			for (size_t i = 0; i < 3; i++) {
				newRgb[i] = static_cast<std::uint8_t>(colorValues[i]);
			}
			this->setRGB(i, newRgb);
			delete[] rgb;
		}
	}
}

void PPMImage::negative() {
	for (size_t i = 0; i < this->getSize(); i += 3) {
		std::uint8_t *rgb = this->getRGB(i);

		if (rgb != nullptr) {
			std::uint8_t newRgb[3] = { 0,0,0 };
			unsigned int colorValues[3] = { 0,0,0 };

			for (size_t i = 0; i < 3; i++) {
				colorValues[i] += static_cast<unsigned int>(255 - rgb[i]);
			}

			for (size_t i = 0; i < 3; i++) {
				newRgb[i] = colorValues[i];
			}
			this->setRGB(i, newRgb);
			delete[] rgb;
		}
	}
}

size_t PPMImage::getSize() const {
	return static_cast<size_t>(this->width * this->height * 3);
}

std::uint8_t* PPMImage::getRGB(size_t index) {
	std::uint8_t *colors = nullptr;
	if (index % 3 == 0) {
		colors = new std::uint8_t[3];
		colors[0] = 0;
		colors[1] = 0;
		colors[2] = 0;

		for (size_t i = 0; i < 3; i++) {
			colors[i] = colors[i] | this->colors[i + index];
		}
	}

	return colors;
}

void PPMImage::setRGB(size_t index, std::uint8_t* rgb) {
	if (index % 3 == 0) {
		for (size_t i = 0; i < 3; i++) {
			this->colors[i + index] = rgb[i] | (this->colors[i + index] & 1);
		}
	}
}

PPMImage::PPMImage() {
	this->colors = nullptr;
	this->height = 0;
	this->width = 0;
	this->maxColor = 0;
	this->magicNumber = "P6";
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

	if (source.colors != nullptr) {
		this->colors = source.colors;
	}
	this->magicNumber = source.magicNumber;
	this->height = source.height;
	this->width = source.width;
	this->maxColor = source.maxColor;
	return *this;
}