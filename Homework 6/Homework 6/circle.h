#ifndef CIRCLE_H
#define CIRCLE_H

#include "figure.h"
class Circle : public Figure {
private:
	double radius;
public:
	Circle();
	Circle(std::string, double);
	double getRadius();
	void setRadius(double);
	double area();
};
#endif