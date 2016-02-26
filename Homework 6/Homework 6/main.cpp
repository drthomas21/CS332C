#include "circle.h"
#include "rectangle.h"
#include <time.h>
#include <cstdio>
#include <iostream>


int main() {
	srand(static_cast<unsigned int>(time(NULL)));

	const size_t SIZE = 20;
	const size_t COLOR_SIZE = 6;
	std::string colors[COLOR_SIZE] = { "red", "white", "yellow", "brown", "black", "orange" };
	Figure **list = new Figure*[SIZE];
	for (int i = 0; i < SIZE; i++) {
		std::string color = colors[rand() % COLOR_SIZE];
		double radius = rand() % 30 + 1;
		double h = rand() % 30 + 1;
		double w = rand() % 30 + 1;
		if (rand() % 2 == 0) {
			list[i] = new Circle(color,radius);
			std::cout << "Created Circle["<< i <<"]: With Color: " << list[i] ->getColor() << " and radius " << radius;
			std::cout << std::endl;
		} else {
			list[i] = new Rectangle(color,h,w);
			std::cout << "Created Rectangle[" << i << "]: With Color: " << list[i]->getColor() << " and height " << h << " and width " << w;
			std::cout << std::endl;
		}
	}

	std::cout << std::endl;
	std::cout << "The object with the greatest area ";
	
	size_t index = 0;
	double maxRadius = 0;
	for (size_t i = 0; i < SIZE; i++) {
		if (list[i]->area() > maxRadius) {
			index = i;
			maxRadius = list[i]->area();
		}
	}

	std::cout << "[" << index << "]: ";
	list[index]->print();
	return 0;
}