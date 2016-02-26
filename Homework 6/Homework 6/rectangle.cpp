#include "rectangle.h"

double Rectangle::getH() {
	return this->h;
}

double Rectangle::getW() {
	return this->w;
}

void Rectangle::setH(double h) {
	this->h = h;
}

void Rectangle::setW(double w) {
	this->w = w;
}

double Rectangle::area() {
	return this->w * this->h;
}

Rectangle::Rectangle(): Figure(), h(0), w(0) { }
Rectangle::Rectangle(std::string color, double h, double w): Figure(color), h(h), w(w) { }