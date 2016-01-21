#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>

const std::string FILENAME = "./points_data.txt";
const int SIZE = 7;
struct Point3D {
	int x;
	int y;
	int z;
};

Point3D getNextPoint(std::ifstream &fileResc);
void displayPoints(const Point3D[],int);
void displayCommands();
void translate(const Point3D point, int amount);
void reflect(const Point3D, std::string);

int main() {
	Point3D points[SIZE];
	int input = -1;
	int size = SIZE;

	std::cout << "Welcome to Static Array" << std::endl;

	std::ifstream fileResc(FILENAME);
	if (!fileResc.good()) {
		std::cout << "There is an issue with opening the file at " << FILENAME << std::endl;
		exit(1);
	}
	
	//Get the points
	try {
		for (int i = 0; i < SIZE; i++) {
			points[i] = getNextPoint(fileResc);
		}
	} catch (int e) {
		std::cout << "Removed Invalid point from list" << e << std::endl;
		size--;
	}
	

	while (input != 0) {
		displayPoints(points,size);
		displayCommands();
		std::cin >> input;
		if (std::cin.fail()) {
			std::cout << "Invalid value" << std::endl;
			input = -1;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			continue;
		}
		
		int point = 0, amount = 0;
		std::string plane = "";
		switch (input) {
			case(1):				
				while (point == 0) {
					std::cout << "Input <point [1-" << size << "]> and <amount>" << std::endl;
					std::cin >> point >> amount;
					if (std::cin.fail()) {
						std::cout << "Invalid value" << std::endl;
						point = 0, amount = 0;
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<int>::max(), '\n');
						continue;
					}
					if (point < 1 || point > size) {
						point = 0;
					}
				}
			
			   translate(points[point-1], amount);
			   break;
			case(2) :
				while (point == 0 || plane.compare("") == 0) {
					std::cout << "Input <point [1-" << size << "]> and <plane>" << std::endl;
					std::cin >> point >> plane;
					if (std::cin.fail()) {
						std::cout << "Invalid value" << std::endl;
						point = 0, plane = "";
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<int>::max(), '\n');
						continue;
					}
					if (point < 1 || point > size) {
						point = 0;
					}
					if (plane.compare("xy") != 0 && plane.compare("yx") != 0 && plane.compare("xz") != 0 && plane.compare("zx") != 0 && plane.compare("zy") != 0 && plane.compare("yz") != 0) {
						plane = "";
					}
				}

				reflect(points[point-1], plane);
				break;

		}
	}
}

Point3D getNextPoint(std::ifstream &fileResc) {
	Point3D Instance = { 0 };
	int x, y, z;

	fileResc >> x >> y >> z;
	if (fileResc.fail()) {
		std::cout << "Failed to read line" << std::endl;
		throw 10;
	}

	Instance = { x,y,z };

	return Instance;
}

void displayPoints(const Point3D points[],int size) {
	std::cout << "Point:" << std::endl;
	for (int i = 0; i < size; i++) {
		std::cout << "\t" << (i + 1) << ") X = " << points[i].x << " Y = " << points[i].y << " Z = " << points[i].z << std::endl;
	}
}

void displayCommands() {
	std::cout
		<< "Commands:" << std::endl
		<< "\t1)translate" << std::endl
		<< "\t2)reflect" << std::endl
		<< "\t0)exit" << std::endl;
}

void translate(const Point3D point, int amount) {
	Point3D node = point;
	node.x = point.x + amount;
	node.y = point.y + amount;
	node.z = point.z + amount;
	
	std::cout << "Translated Point: X = " << node.x << " Y = " << node.y << " Z = " << node.z << std::endl;
}

void reflect(const Point3D point, std::string plane) {
	Point3D node = point;

	if (plane.compare("xy") == 0 || plane.compare("yx") == 0) {
		node.z = point.z*-1;
	} else if (plane.compare("xz") == 0 || plane.compare("zx") == 0) {
		node.y = point.y*-1;
	} else if (plane.compare("zy") == 0 || plane.compare("yz") == 0) {
		node.x = point.x*-1;
	}

	std::cout << "Reflected Point: X = " << node.x << " Y = " << node.y << " Z = " << node.z << std::endl;
}