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

		Integer newInt;

		int maxLength = this->number.length() > source.number.length() ? this->number.length() : source.number.length();
		std::string sourceStr = source.number;
		std::string selfStr = this->number;

		while (selfStr.length() != maxLength) {
			selfStr.insert(0, "0");
		}

		while (sourceStr.length() != maxLength) {
			sourceStr.insert(0, "0");
		}

		int remainder = 0;
		for (int i = maxLength - 1; i >= 0; i--) {
			int item1 = selfStr[i] - 0;
			int item2 = sourceStr[i] - 0;

			int n = item1 + item2 + remainder;

			remainder = floor(n / 10);
			newInt.number.insert(0, std::to_string(n % 10));
		}

		if (remainder > 0) {
			newInt.number.insert(0, std::to_string(remainder));
		}

		return newInt;
	}

	Integer Integer::operator-(const Integer &source) const {
		// 30 - (-10) == 30 + 10
		if (this->isPositive != source.isPositive) {
			return (*this) + source;
		}

		Integer newInt;
		int maxLength = this->number.length() > source.number.length() ? this->number.length() : source.number.length();
		std::string sourceStr = source.number;
		std::string selfStr = this->number;
		int carryover = 0;

		while (selfStr.length() != maxLength) {
			selfStr.insert(0, "0");
		}

		while (sourceStr.length() != maxLength) {
			sourceStr.insert(0, "0");
		}


		if (*this > source) {
			for (int i = maxLength - 1; i >= 0; i--) {
				int item1 = selfStr[i] - 0;
				int item2 = sourceStr[i] - 0;
				int n = 0;

				if (item1 < item2 || (carryover == 1 && item1 == item2)) {
					carryover = 1;
					item1 += 10;
				} else {
					item1 -= 1;
					carryover = 0;
				}
				newInt.number.insert(0, std::to_string(item1 - item2));
			}
		} else {
			for (int i = maxLength - 1; i >= 0; i--) {
				int item1 = selfStr[i] - 0;
				int item2 = sourceStr[i] - 0;
				int n = 0;
				if (item1 > item2 || (carryover == 1 && item1 == item2)) {
					carryover = 1;
					item2 += 10;
				} else {
					item2 -= 1;
					carryover = 0;
				}
				newInt.number.insert(0, std::to_string(item2 - item1));
			}
		}					

		return newInt;
	}

	Integer Integer::operator*(const Integer &source) const {
		Integer newInt;
		newInt.isPositive = this->isPositive == source.isPositive;
		int _temp = this->number.length() + source.number.length() - 1;
		for (int i = 0; i < _temp; i++) {
			newInt.number.push_back('0');
		}
		int remander = 0;

		for (int i = this->number.length() - 1; i >= 0; i--) {
			int offset = this->number.length() - (i + 1);

			for (int j = source.number.length() - 1; j >= 0; j--) {
				int item1 = newInt.number[offset + j];
				int item2 = this->number[i];
				int item3 = source.number[j];
				item1 += item2*item3 + remander;
				remander = floor(item1 / 10);
				newInt.number[offset + j] = Integer::digits[item1 % 10];
			}
		}
	}

	void Integer::operator+=(const Integer &source) {
		Integer newInt = *this + source;
		this->number.clear();
		for (int i = 0; i < newInt.number.length(); i++) {
			this->number.push_back(newInt.number[i]);
		}
	}

	void Integer::operator-=(const Integer &source) {
		Integer newInt = *this - source;
		this->number.clear();
		for (int i = 0; i < newInt.number.length(); i++) {
			this->number.push_back(newInt.number[i]);
		}
	}

	void Integer::operator*=(const Integer &source) {
		Integer newInt = *this * source;
		this->number.clear();
		for (int i = 0; i < newInt.number.length(); i++) {
			this->number.push_back(newInt.number[i]);
		}
	}

	bool Integer::operator>(const Integer &source) const {
		bool ret = this->number.length() > source.number.length();
		if (!ret && this->number.length() == source.number.length()) {
			for (int i = 0; i < this->number.length(); i++) {
				ret = (this->number[i] - 0) <(source.number[i] - 0);
				if (ret) {
					break;
				}
			}
			ret = !ret;
		}

		return ret;
	}

	bool Integer::operator<(const Integer &source) const {
		bool ret = this->number.length() < source.number.length();
		if (!ret && this->number.length() == source.number.length()) {
			for (int i = 0; i < this->number.length(); i++) {
				ret = (this->number[i] - 0) >(source.number[i] - 0);
				if (ret) {
					break;
				}
			}
			ret = !ret;
		}

		return ret;
	}

	bool Integer::operator>=(const Integer &source) const {
		bool ret = this->number.length() > source.number.length();
		if (!ret && this->number.length() == source.number.length()) {
			for (int i = 0; i < this->number.length(); i++) {
				ret = (this->number[i] - 0) < (source.number[i] - 0);
				if (!ret) {
					break;
				}
			}
			ret = !ret;
		}

		return ret;
	}

	bool Integer::operator<=(const Integer &source) const {
		bool ret = this->number.length() < source.number.length();
		if (!ret && this->number.length() == source.number.length()) {
			for (int i = 0; i < this->number.length(); i++) {
				ret = (this->number[i] - 0) >(source.number[i] - 0);
				if (ret) {
					break;
				}
			}
			ret = !ret;
		}

		return ret;
	}

	bool Integer::operator==(const Integer &source) const {
		bool ret = this->number.length() == source.number.length();
		if (ret) {
			for (int i = 0; i < this->number.length(); i++) {
				ret = (this->number[i] - 0) == (source.number[i] - 0);
				if (!ret) {
					break;
				}
			}
		}

		return ret;
	}

	bool Integer::operator!=(const Integer &source) const {
		bool ret = this->number.length() != source.number.length();
		if (!ret) {
			for (int i = 0; i < this->number.length(); i++) {
				ret = (this->number[i] - 0) == (source.number[i] - 0);
				if (!ret) {
					break;
				}
			}
			ret = !ret;
		}

		return ret;
	}

	Integer Integer::operator++(int nill) {
		Integer _Instance = Integer(this);
		*this += Integer(1);
		return _Instance;
	}

	Integer Integer::operator++() {		
		*this += Integer(1);
		Integer _Instance = Integer(this);
		return _Instance;
	}

	Integer Integer::operator--(int nill) {
		Integer _Instance = Integer(this);
		*this -= Integer(1);
		return _Instance;
	}

	Integer Integer::operator--() {
		*this -= Integer(1);
		Integer _Instance = Integer(this);
		return _Instance;
	}

	int Integer::operator[](int index) {
		if (index < 0 || index >= this->number.length()) {
			return -1;
		}

		return this->number[index]-0;
	}

	std::ostream &operator<<(std::ostream &outputStream, const Integer &source) {
		outputStream << source.number;
	}

	std::istream &operator>>(std::istream &inputStream, Integer &source) {
		char buffer[100];
		do {
			inputStream >> buffer;

		}
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