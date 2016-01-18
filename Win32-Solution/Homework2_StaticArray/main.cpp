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

int main() {
	Point3D points[SIZE];
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

void translate() {

}

void reflect() {

}