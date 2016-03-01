#include "ppmimage.h"
#include <string>
#include <iostream>
#include <cmath>
#include <stdint.h>

#define FAILED_READ_IMAGE 101
#define FAILED_WRITE_IMAGE 102
#define FAILED_MESSAGE_TOO_LAGER 201
#define FAILED_MESSAGE_NOT_FOUND 202

const char PPMImage::MESSAGE_PREFIX[PPMImage::PREFIX_SIZE] = { 'M','s','g' };

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
		source.colors[i] =_unsignedChars[i];
	}
	delete[] _unsignedChars;
	return input;
}

std::ostream& operator<<(std::ostream &output, const PPMImage &source) {
	output << source.magicNumber << PPMImage::EOL;
	output << source.width << " " << source.height << PPMImage::EOL;
	output << source.maxColor << PPMImage::EOL;
	
	char *_unsignedChars = new char[source.getSize()];
	for (size_t i = 0; i < source.getSize(); i++) {
		_unsignedChars[i] = source.colors[i];
	}

	output.write(_unsignedChars, source.getSize());
	
	delete[] _unsignedChars;
	return output;
}

void PPMImage::hideData(const std::string &message) {
	std::string _message = message;
	unsigned int charSize = sizeof(unsigned char) * 8;

	if (this->getSize() >= (_message.size() + PPMImage::PREFIX_SIZE + 1) * charSize) {
		size_t offset = 0;
		size_t shift = charSize;
		for (size_t i = 0; i < PPMImage::PREFIX_SIZE; i++) {
			shift = charSize;
			while (shift > 0) {
				shift--;
				std::uint8_t binary = 1;
				unsigned char item = PPMImage::MESSAGE_PREFIX[i] & (binary << shift);
				this->colors[offset] = this->colors[offset] >> 1;
				this->colors[offset] = this->colors[offset] << 1;
				this->colors[offset] = this->colors[offset] | (item >> shift);
				offset += 1;
			}
		}

		for (size_t i = 0; i < _message.size(); i++) {
			shift = charSize;
			while (shift > 0) {
				shift--;
				std::uint8_t binary = 1;
				unsigned char item = _message[i] & (binary << shift);
				this->colors[offset] = this->colors[offset] >> 1;
				this->colors[offset] = this->colors[offset] << 1;
				this->colors[offset] = this->colors[offset] | (item >> shift);
				offset += 1;				
			}
		}

		shift = charSize;
		while (shift > 0) {
			shift--;
			this->colors[offset] = this->colors[offset] & ~(1);
			offset += 1;
		}
	} else {
		throw FAILED_MESSAGE_TOO_LAGER;
	}
}

std::string PPMImage::recoverData() {
	std::string message = "";
	size_t offset = 0;
	size_t size = this->getSize();
	unsigned int charSize = sizeof(unsigned char) * 8;
	
	unsigned char character = 0;
	std::uint8_t binaryString = 0;
	while (true) {
		size_t shift = charSize;
		binaryString = 0;

		while (offset < size && shift > 0) {
			shift--;

			std::uint8_t binary = 1;
			binaryString = binaryString | ((this->colors[offset] & binary) << shift);
			offset += 1;
		}
		
		if (offset >= size) {
			throw FAILED_MESSAGE_NOT_FOUND;
		}
		
		character = binaryString;
		message.push_back(character);
		if (binaryString == 0) {
			break;
		}

		if (message.length() == PPMImage::PREFIX_SIZE && message.compare(PPMImage::MESSAGE_PREFIX) != 0) {
			throw FAILED_MESSAGE_NOT_FOUND;
		}
	}
	
	if (message.length() < PPMImage::PREFIX_SIZE || message.length() >= PPMImage::PREFIX_SIZE && message.substr(0,3).compare(PPMImage::MESSAGE_PREFIX) != 0) {
		throw FAILED_MESSAGE_NOT_FOUND;
	}
	message = message.substr(3);
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

			colorValue = colorValue < this->maxColor ? colorValue : this->maxColor;

			for (size_t j = 0; j < 3; j++) {
				newRgb[j] = static_cast<std::uint8_t>(colorValue);
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
				colorValues[i] = colorValues[i] < this->maxColor ? colorValues[i] : this->maxColor;
			}

			for (size_t i = 0; i < 3; i++) {
				newRgb[i] = static_cast<std::uint8_t>(colorValues[i]);;
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
			rgb[i] = rgb[i] >> 1;
			rgb[i] = rgb[i] << 1;
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