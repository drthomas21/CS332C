#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

const std::string FILENAME = "./points_data.txt";
const int SIZE = 7;
struct Point3D {
	int x;
	int y;
	int z;
};

std::ifstream getFileStream();
Point3D getNextPoint(std::ifstream &fileResc);
void displayPoints(const Point3D[]);
void displayCommands();
void translate(const Point3D point, int amount);
void reflect(const Point3D, std::string);

int main() {
	Point3D points[SIZE];
	int input = -1;

	std::cout << "Welcome to Static Array" << std::endl;

	std::ifstream fileResc= getFileStream();
	if (!fileResc.good()) {
		std::cout << "There is an issue with opening the file at " << FILENAME << std::endl;
		exit(1);
	}
	
	//Get the points
	for (int i = 0; i < SIZE; i++) {
		points[i] = getNextPoint(fileResc);
	}

	while (input != 0) {
		displayPoints(points);
		displayCommands();
		std::cin >> input;
		if (std::cin.fail()) {
			std::cout << "Invalid value" << std::endl;
			input = -1;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			continue;
		}
		
		int point = NULL, amount = NULL;
		std::string plane = "";
		switch (input) {
			case(1):				
				while (point == NULL || amount == NULL) {
					std::cout << "Input <point [1-" << SIZE << "]> and <amount>" << std::endl;
					std::cin >> point >> amount;
					if (std::cin.fail()) {
						std::cout << "Invalid value" << std::endl;
						point = NULL, amount = NULL;;
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<int>::max(), '\n');
						continue;
					}
					if (point < 1 || point > SIZE) {
						point = NULL;
					}
				}
			
			   translate(points[point-1], amount);
			   break;
			case(2) :
				while (point == NULL || plane.compare("") == 0) {
					std::cout << "Input <point [1-" << SIZE << "]> and <plane>" << std::endl;
					std::cin >> point >> plane;
					if (std::cin.fail()) {
						std::cout << "Invalid value" << std::endl;
						point = NULL, plane = "";
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<int>::max(), '\n');
						continue;
					}
					if (point < 1 || point > SIZE) {
						point = NULL;
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

std::ifstream getFileStream() {
	std::ifstream fileResc(FILENAME);
	return fileResc;
		
}

Point3D getNextPoint(std::ifstream &fileResc) {
	Point3D Instance = { NULL, NULL, NULL };
	int x = NULL , y = NULL, z = NULL;
	try {
		fileResc >> x >> y >> z;
		if (x && y && z) {
			Instance = { x,y,z };
		}
	} catch (int e) {
		std::cout << "Failed to read line" << std::endl;
	}

	return Instance;
}

void displayPoints(const Point3D points[]) {
	std::cout << "Point:" << std::endl;
	for (int i = 0; i < SIZE; i++) {
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