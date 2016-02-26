#ifndef FIGURE_H
#define FIGURE_H

#include <string>

class Figure {
	protected:
		std::string color;
	public:
		Figure();
		Figure(std::string);
		std::string getColor();
		void setColor(std::string);
		virtual double area() = 0;
		void print();
};
#endif