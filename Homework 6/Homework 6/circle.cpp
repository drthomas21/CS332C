#include "circle.h"
#include <math.h>

const double PI = 3.141592653589793238463;
double Circle::getRadius() {
	return this->radius;
}

void Circle::setRadius(double radius) {
	this->radius = radius;
}

double Circle::area() {
	return PI * pow(this->radius, 2.0);
}

Circle::Circle() :Figure(), radius(0) { }
Circle::Circle(std::string color, double radius) : Figure(color), radius(radius) { }