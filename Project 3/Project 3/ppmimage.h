#ifndef PPMIMAGE_H
#define PPMIMAGE_H
#include <string>
#include <iostream>

class PPMImage {
private:
	std::string magicNumber;
	unsigned int width;
	unsigned int height;
	unsigned int maxColor;
	unsigned char* colors;
	unsigned int numOfChars;
public:
	static const char EOL = '\n';
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
};
#endif