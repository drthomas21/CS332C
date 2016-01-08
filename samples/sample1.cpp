#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

int main() {
	srand(time(NULL));

	int numberOfLanguages;
	cout << "Hello reader.\n" << "Welcome to C++.\n";

	for(int i =0; i < 10; i++) {
		cout << rand() << endl;
	}
	return 0;
}
