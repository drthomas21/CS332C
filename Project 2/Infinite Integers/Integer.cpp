#include "Integer.h"
#include <math.h>

namespace project {
	//Public functions
	Integer Integer::operator=(Integer source) {
		this->isPositive = source.isPositive;
		this->number = source.number;
		return *this;
	}

	Integer Integer::operator=(Integer &source) {
		this->isPositive = source.isPositive;
		this->number = source.number;
		return *this;
	}

	Integer Integer::operator=(Integer *source) {
		this->isPositive = source->isPositive;
		this->number = source->number;
		return *this;
	}

	Integer Integer::operator+(const Integer &source) const {
		//30 + (-10) == 30 - 10
		if (this->isPositive != source.isPositive) {
			return (*this) - source;
		}

		Integer *newInt = new Integer(this);

		int maxLength = newInt->number.length() > source.number.length() ? newInt->number.length() : source.number.length();
		std::string sourceStr = source.number;

		while (newInt->number.length() != maxLength) {
			newInt->number.insert(0, "0");
		}

		while (sourceStr.length() != maxLength) {
			sourceStr.insert(0, "0");
		}

		int remainder = 0;
		for (int i = maxLength - 1; i >= 0; i--) {
			char item1[] = { newInt->number[i] };
			char item2[] = { sourceStr[i] };

			int n = atoi(item1) + atoi(item2) + remainder;

			remainder = n / 10;

			std::string item3 = std::to_string(n % 10);
			newInt->number[i] = item3[0];
		}

		if (remainder > 0) {
			newInt->number.insert(0, std::to_string(remainder));
		}

		return *newInt;
	}

	Integer Integer::operator-(const Integer &source) const {
		// 30 - (-10) == 30 + 10
		if (this->isPositive != source.isPositive) {
			return (*this) + source;
		}

		Integer *newInt = new Integer(this);

		int maxLength = newInt->number.length() > source.number.length() ? newInt->number.length() : source.number.length();
		std::string sourceStr = source.number;

		while (newInt->number.length() != maxLength) {
			newInt->number.insert(0, "0");
		}

		while (sourceStr.length() != maxLength) {
			sourceStr.insert(0, "0");
		}

		int remainder = 0;
		for (int i = maxLength - 1; i >= 0; i--) {
			char item1[] = { newInt->number[i] };
			char item2[] = { sourceStr[i] };

			int n = atoi(item1) + atoi(item2) + remainder;

			remainder = n / 10;

			std::string item3 = std::to_string(n % 10);
			newInt->number[i] = item3[0];
		}

		if (remainder > 0) {
			newInt->number.insert(0, std::to_string(remainder));
		}

		return *newInt;
	}
	
	//Constructors
	Integer::Integer() :number("0"), isPositive(true){ }

	Integer::Integer(const Integer &source) : number(source.number), isPositive(source.isPositive) { }

	Integer::Integer(const Integer *source) : number(source->number), isPositive(source->isPositive) { }

	Integer::Integer(int num) {
		this->isPositive = true;
		if (num < 0) {
			this->isPositive = false;
			num *= -1;
		}
		this->number = std::to_string(num);
	}

	Integer::Integer(long num) {
		this->isPositive = true;
		if (num < 0) {
			this->isPositive = false;
			num *= -1;
		}
		this->number = std::to_string(num);
	}

	Integer::Integer(long long num) {
		this->isPositive = true;
		if (num < 0) {
			this->isPositive = false;
			num *= -1;
		}
		this->number = std::to_string(num);
	}

	Integer::Integer(std::string num) {
		this->isPositive = true;
		this->number = num;
		if (num[0] == '-') {
			this->isPositive = false;
			this->number = num.substr(1);
		}
	}

	Integer::Integer(char* num) {
		this->isPositive = true;
		this->number = num;
		if (num[0] == '-') {
			this->isPositive = false;
			num++;
			this->number = num;
		}
	}
}