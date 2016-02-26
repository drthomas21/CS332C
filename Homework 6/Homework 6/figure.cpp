#include "figure.h"
#include <iostream>

void Figure::print() {
	std::cout << "The color of the object is " << this->color << " and the area is " << this->area() << std::endl;
}

std::string Figure::getColor() {
	return this->color;
}

void Figure::setColor(std::string color) {
	this->color = color;
}

Figure::Figure():color("white") { }
Figure::Figure(std::string color):color(color) { }