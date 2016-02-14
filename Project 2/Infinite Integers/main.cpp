#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>
#include "integer.h"

int main() {
	srand(static_cast<unsigned int>(time(NULL)));	

	std::cout << "Positive Nums" << std::endl;
	Integer obj0;
	std::cout << "Ojbect 0 - Empty: " << obj0 << std::endl;

	std::string _temp1 = "12345";
	Integer obj1(_temp1);
	std::cout << "Object 1 - String: " << _temp1 << " object: "<< obj1 << std::endl;

	int _temp2 = 12345;
	Integer obj2(_temp2);
	std::cout << "Ojbect 2 - Int:" << _temp2 << " object: " << obj2 << std::endl;

	long _temp3 = 123456789;
	Integer obj3(_temp3);
	std::cout << "Ojbect 3 - Long:" << _temp3 << " object: " << obj3 << std::endl;

	long long _temp4 = 123456789;
	Integer obj4(_temp4);
	std::cout << "Ojbect 4 - Long Long:" << _temp4 << " object: " << obj4 << std::endl;

	char _temp5[100] = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
	Integer obj5(_temp5,100);
	std::cout << "Ojbect 5 - char*:" << _temp5 << " object: " << obj5 << std::endl;

	Integer obj6(obj5);
	std::cout << "Ojbect 6 - Copy:" << " object: " << obj6 << std::endl;

	//-----------------------------------
	std::cout << std::endl;

	std::cout << "Negative Nums" << std::endl;
	std::string _temp11 = "-12345";
	Integer obj11(_temp11);
	std::cout << "Object 11 - String: " << _temp11 << " object: " << obj11 << std::endl;

	int _temp12 = -12345;
	Integer obj12(_temp12);
	std::cout << "Ojbect 12 - Int:" << _temp12 << " object: " << obj12 << std::endl;

	long _temp13 = -123456789;
	Integer obj13(_temp13);
	std::cout << "Ojbect 3 - Long:" << _temp13 << " object: " << obj13 << std::endl;

	long long _temp14 = -123456789;
	Integer obj14(_temp14);
	std::cout << "Ojbect 4 - Long Long:" << _temp14 << " object: " << obj14 << std::endl;

	char _temp15[100] = "-12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678";
	Integer obj15(_temp15,100);
	std::cout << "Ojbect 5 - char*:" << _temp15 << " object: " << obj15 << std::endl;

	Integer obj16(obj15);
	std::cout << "Ojbect 6 - Copy:" << obj16 << std::endl;

	//-------------------------------------

	Integer userObj1;
	std::cout << "Input a really large number: ";
	std::cin >> userObj1;
	std::cout << std::endl << "Your input: " << userObj1 << std::endl;

	Integer userObj2;
	std::cout << "Add a number to it: ";
	std::cin >> userObj2;
	std::cout << std::endl << userObj1;
	userObj1 += userObj2;
	std::cout << " + " << userObj2 << " = " << userObj1 << std::endl;

	Integer userObj3;
	std::cout << "Subtract a number to it: ";
	std::cin >> userObj3;
	std::cout << std::endl << userObj1;
	userObj1 -= userObj3;
	std::cout << " - " << userObj3 << " = " << userObj1 << std::endl;

	Integer userObj4;
	std::cout << "Multiply it by a number: ";
	std::cin >> userObj4;
	std::cout << std::endl << userObj1;
	userObj1 *= userObj4;
	std::cout << " x " << userObj4 << " = " << userObj1 << std::endl;

	//------------------------------------
	std::cout << std::endl;

	for (int i = 0; i < 10; i++) {
		Integer a(rand());
		Integer b(rand());

		int choice = rand() % 3;
		if (choice == 0) {
			std::cout << a << " + " << b << " = ";
			Integer c = a + b;
			std::cout << c << std::endl;
		} else if(choice == 1) {
			std::cout << a << " - " << b << " = ";
			Integer c = a - b;
			std::cout << c << std::endl;
		} else {
			std::cout << a << " x " << b << " = ";
			Integer c = a * b;
			std::cout << c << std::endl;
		}
	}

	//------------------------------------
	std::cout << std::endl;

	Integer obj30(rand());
	std::cout << "Object 30 - Normal: " << obj30 << std::endl;
	obj30++;
	std::cout << "Object 30 - Post Inc: " << obj30 << std::endl;
	++obj30;
	std::cout << "Object 30 - Pre Inc: " << obj30 << std::endl;
	obj30--;
	std::cout << "Object 30 - Post Desc: " << obj30 << std::endl;
	--obj30;
	std::cout << "Object 30 - Pre Desc: " << obj30 << std::endl;

	//------------------------------------
	std::cout << std::endl;

	for (int i = 0; i < 20; i++) {
		Integer a(rand() % 5);
		Integer b(rand() % 5);

		std::cout << "Is " << a << " > " << b << "? " << (a > b ? "Is Greater" : (a < b ? "Is Lesser" : (a == b ? "Is Equal" : "Epic Failure")));
		std::cout << "Is " << a << " >= " << b << "? " << (a >= b ? "Is Greater Or Equal" : (a <= b ? "Is Lesser Or Equal" : "Epic Failure"));
		std::cout << "Is " << a << " != " << b << "? " << (a != b ? "Not Same" : (a == b ? "The Same" : "Epic Failure"));
		std::cout << std::endl;
	}

	//------------------------------------
	std::cout << std::endl;
	
	Integer obj40(rand());
	std::cout << "Object 40 - Normal: " << obj40 << std::endl;
	for (size_t i = 0; i < obj40.length(); i++) {
		std::cout << "Object 40 - Char at " << i << ": " << obj40[i] << std::endl;
	}
	std::cout << std::endl;
	size_t i = 0;
	int value = 0;
	while ((value = obj40[i]) != -1) {
		std::cout << "Object 40 - Loop - Char at " << i << ": " << value << std::endl;
		i++;
	}
}