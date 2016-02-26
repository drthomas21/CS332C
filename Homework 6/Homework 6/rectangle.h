#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"
class Rectangle : public Figure {
private:
	double w, h;
public:
	Rectangle();
	Rectangle(std::string, double, double);
	double getH();
	void setH(double);
	double getW();
	void setW(double);
	double area();
};
#endif