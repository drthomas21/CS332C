#ifndef PPMIMAGE_H
#define PPMIMAGE_H
#include <string>
#include <iostream>
#include <stdint.h>

class PPMImage {
private:
	std::string magicNumber;
	unsigned int width;
	unsigned int height;
	unsigned int maxColor;
	unsigned char* colors;
	std::uint8_t* getRGB(size_t);
	void setRGB(size_t, std::uint8_t*);

public:
	static const char EOL = '\n';
	static const int PREFIX_SIZE = 3;
	static const char MESSAGE_PREFIX[PREFIX_SIZE];
	PPMImage();
	PPMImage(const PPMImage&);
	~PPMImage();
	PPMImage operator=(const PPMImage&);

	friend std::istream& operator>>(std::istream&, PPMImage&);
	friend std::ostream& operator<<(std::ostream&, const PPMImage&);
	void hideData(const std::string&);
	std::string recoverData();
	void grayscale();
	void sepia();
	void negative();
	size_t getSize() const;
	
};
#endif