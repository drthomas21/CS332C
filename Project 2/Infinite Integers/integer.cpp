#include "integer.h"
#include <math.h>
#include <limits>

//Public functions
const unsigned int ASCII_TO_INT_OFFSET = 48;
size_t Integer::length() const {
	return this->number.length();
}

Integer Integer::operator=(const Integer &source) {
	this->isPositive = source.isPositive;
	this->number = source.number;
	return *this;
}

Integer Integer::operator+(const Integer &source) const {
	//30 + (-10) == 30 - 10
	if (this->isPositive != source.isPositive) {
		Integer _source(source);
		_source.isPositive = !_source.isPositive;
		return (*this) - _source;
	}

	Integer newInt;
	newInt.number = "";
	newInt.isPositive = this->isPositive;

	size_t maxLength = this->number.length() > source.number.length() ? this->number.length() : source.number.length();
	std::string sourceStr = source.number;
	std::string selfStr = this->number;

	while (selfStr.length() < maxLength) {
		selfStr.insert(0, "0");
	}

	while (sourceStr.length() < maxLength) {
		sourceStr.insert(0, "0");
	}

	int remainder = 0;
	size_t i = maxLength;	
	while (i > 0) {
		i--;

		int item1 = selfStr[i] - ASCII_TO_INT_OFFSET;
		int item2 = sourceStr[i] - ASCII_TO_INT_OFFSET;

		int n = item1 + item2 + remainder;

		remainder = static_cast<int>(floor(n / 10));
		newInt.number.insert(0, std::to_string(n % 10));
	}	

	if (remainder > 0) {
		newInt.number.insert(0, std::to_string(remainder));
	}

	return newInt;
}

Integer Integer::operator-(const Integer &source) const {
	// 30 - (-10) == 30 + 10
	Integer _source(source);
	
	_source.isPositive = !_source.isPositive;
	
	if (this->isPositive == _source.isPositive) {
		return (*this) + _source;
	}

	Integer newInt;
	newInt.number = "";

	size_t maxLength = this->number.length() > _source.number.length() ? this->number.length() : _source.number.length();
	std::string sourceStr = _source.number;
	std::string selfStr = this->number;
	int carryover = 0;

	while (selfStr.length() < maxLength) {
		selfStr.insert(0, "0");
	}

	while (sourceStr.length() < maxLength) {
		sourceStr.insert(0, "0");
	}


	Integer _this(*this);
	_this.isPositive = _source.isPositive = true;
	if (_this > _source) {
		newInt.isPositive = this->isPositive;
		size_t i = maxLength;
		while (i > 0) {
			i--;

			int item1 = selfStr[i] - ASCII_TO_INT_OFFSET;
			int item2 = sourceStr[i] - ASCII_TO_INT_OFFSET;
			int n = 0;

			if (item1 < item2 || (carryover > 0 && item1 == item2)) {
				if (carryover > 0) {
					item1 -= 1;
				}
				carryover = 1;
				item1 += 10;
			} else if(carryover > 0) {
				item1 -= carryover;
				carryover = 0;
			}
			newInt.number.insert(0, std::to_string((item1 - item2) % 10));
		}
	} else {
		newInt.isPositive = !source.isPositive;
		size_t i = maxLength;
		while (i > 0) {
			i--;

			int item1 = selfStr[i] - ASCII_TO_INT_OFFSET;
			int item2 = sourceStr[i] - ASCII_TO_INT_OFFSET;
			int n = 0;
			if (item1 > item2 || (carryover > 0 && item1 == item2)) {
				if (carryover > 0) {
					item2 -= 1;
				}
				carryover = 1;
				item2 += 10;
			} else if (carryover > 0) {
				item2 -= carryover;
				carryover = 0;
			}
			newInt.number.insert(0, std::to_string((item2 - item1) % 10));
		}
	}


	return newInt;
}

Integer Integer::operator*(const Integer &source) const {
	Integer newInt;
	newInt.number = "";
	newInt.isPositive = this->isPositive == source.isPositive;
	unsigned int shift = 1;
	for (size_t i = 0; i < (this->number.length() + source.number.length()); i++) {
		newInt.number.push_back('0');
	}
	int remainder = 0;

	size_t i = this->number.length();
	while (i > 0) {
		i--;

		size_t j = source.number.length();
		while (j > 0) {
			j--;
			
			int item1 = newInt.number[i + j + shift] - ASCII_TO_INT_OFFSET;
			int item2 = this->number[i] - ASCII_TO_INT_OFFSET;
			int item3 = source.number[j] - ASCII_TO_INT_OFFSET;
			item1 += item2*item3 + remainder;
			remainder = static_cast<int>(floor(item1 / 10));
			newInt.number[i + j + shift] = Integer::digits[static_cast<size_t>(item1 % 10)];
		}

		while (remainder > 0) {
			j--;

			int item1 = newInt.number[i + j + shift] - ASCII_TO_INT_OFFSET;
			item1 += remainder;
			remainder = static_cast<int>(floor(item1 / 10));
			newInt.number[i + j + shift] = Integer::digits[static_cast<size_t>(item1 % 10)];
		}
	}

	

	return newInt;
}

void Integer::operator+=(const Integer &source) {
	Integer newInt = *this + source;
	this->isPositive = newInt.isPositive;
	this->number = "";
	for (size_t i = 0; i < newInt.number.length(); i++) {
		this->number.push_back(newInt.number[i]);
	}
}

void Integer::operator-=(const Integer &source) {
	Integer newInt = *this - source;
	this->isPositive = newInt.isPositive;
	this->number = "";
	for (size_t i = 0; i < newInt.number.length(); i++) {
		this->number.push_back(newInt.number[i]);
	}
}

void Integer::operator*=(const Integer &source) {
	Integer newInt = *this * source;
	this->isPositive = newInt.isPositive;
	this->number = "";
	for (size_t i = 0; i < newInt.number.length(); i++) {
		this->number.push_back(newInt.number[i]);
	}
}

bool Integer::operator>(const Integer &source) const {
	// -3 > -5 == 3 < 5
	if (this->isPositive == false && source.isPositive == false) {
		Integer _source(source);
		Integer _this(*this);

		_source.isPositive = true;
		_this.isPositive = true;

		return _this < _source;
	} else if (this->isPositive != source.isPositive) {
		return this->isPositive;
	}

	//Removes fluff
	Integer _source(source);
	Integer _this(*this);

	bool ret = _this.number.length() > _source.number.length();
	if (!ret && _this.number.length() == _source.number.length()) {
		for (size_t i = 0; i < _this.number.length(); i++) {
			ret = (_this.number[i] - ASCII_TO_INT_OFFSET) >(_source.number[i] - ASCII_TO_INT_OFFSET);
			if (ret) {
				break;
			}

			ret = (_this.number[i] - ASCII_TO_INT_OFFSET) < (_source.number[i] - ASCII_TO_INT_OFFSET);
			if (ret) {
				ret = !ret;
				break;
			} else {
				ret = false;
			}
		}
	}

	return ret && _this.isPositive == _source.isPositive;
}

bool Integer::operator<(const Integer &source) const {
	// -3 < -5 == 3 > 5
	if (this->isPositive == false && source.isPositive == false) {
		Integer _source(source);
		Integer _this(*this);

		_source.isPositive = true;
		_this.isPositive = true;

		return _this > _source;
	} else if (this->isPositive != source.isPositive) {
		return !this->isPositive;
	}

	//Removes fluff
	Integer _source(source);
	Integer _this(*this);

	bool ret = _this.number.length() < _source.number.length();
	if (!ret && _this.number.length() == _source.number.length()) {
		for (size_t i = 0; i < _this.number.length(); i++) {
			ret = (_this.number[i] - ASCII_TO_INT_OFFSET) >(_source.number[i] - ASCII_TO_INT_OFFSET);
			if (ret) {
				ret = !ret;
				break;
			}

			ret = (_this.number[i] - ASCII_TO_INT_OFFSET) < (_source.number[i] - ASCII_TO_INT_OFFSET);
			if (ret) {
				break;
			} else {
				ret = false;
			}
		}
	}

	return ret && _this.isPositive == _source.isPositive;
}

bool Integer::operator>=(const Integer &source) const {
	// -3 >= -5 == 3 <= 5
	if (this->isPositive == false && source.isPositive == false) {
		Integer _source(source);
		Integer _this(*this);

		_source.isPositive = true;
		_this.isPositive = true;

		return _this <= _source;
	} else if (this->isPositive != source.isPositive) {
		return this->isPositive;
	}

	//Removes fluff
	Integer _source(source);
	Integer _this(*this);

	bool ret = _this.number.length() > _source.number.length();
	if (!ret && _this.number.length() == _source.number.length()) {
		for (size_t i = 0; i < _this.number.length(); i++) {
			ret = (_this.number[i] - ASCII_TO_INT_OFFSET) > (_source.number[i] - ASCII_TO_INT_OFFSET);
			if (ret) {
				break;
			}

			ret = (_this.number[i] - ASCII_TO_INT_OFFSET) < (_source.number[i] - ASCII_TO_INT_OFFSET);
			if (ret) {
				ret = !ret;
				break;
			} else {
				ret = true;
			}
		}
	}

	return ret;
}

bool Integer::operator<=(const Integer &source) const {
	// -3 <= -5 == 3 >= 5
	if(this->isPositive == false && source.isPositive == false) {
		Integer _source(source);
		Integer _this(*this);

		_source.isPositive = true;
		_this.isPositive = true;

		return _this >= _source;
	} else if (this->isPositive != source.isPositive) {
		return !this->isPositive;
	}
	//Removes fluff
	Integer _source(source);
	Integer _this(*this);

	bool ret = _this.number.length() < _source.number.length();
	if (!ret && _this.number.length() == _source.number.length()) {
		for (size_t i = 0; i < _this.number.length(); i++) {
			ret = (_this.number[i] - ASCII_TO_INT_OFFSET) >(_source.number[i] - ASCII_TO_INT_OFFSET);
			if (ret) {
				ret = !ret;
				break;
			}

			ret = (_this.number[i] - ASCII_TO_INT_OFFSET) < (_source.number[i] - ASCII_TO_INT_OFFSET);
			if (ret) {				
				break;
			} else {
				ret = true;
			}
		}
	}

	return ret;
}

bool Integer::operator==(const Integer &source) const {
	if (this->isPositive != source.isPositive) {
		return false;
	}

	//Removes fluff
	Integer _source(source);
	Integer _this(*this);

	bool ret = _this.number.length() == _source.number.length();
	if (ret) {
		for (size_t i = 0; i < _this.number.length(); i++) {
			ret = (_this.number[i] - ASCII_TO_INT_OFFSET) == (_source.number[i] - ASCII_TO_INT_OFFSET);
			if (!ret) {
				break;
			}
		}
	}

	return ret;
}

bool Integer::operator!=(const Integer &source) const {
	if (this->isPositive != source.isPositive) {
		return true;
	}

	//Removes fluff
	Integer _source(source);
	Integer _this(*this);

	bool ret = _this.number.length() != _source.number.length();
	if (!ret) {
		for (size_t i = 0; i < _this.number.length(); i++) {
			ret = (_this.number[i] - ASCII_TO_INT_OFFSET) != (_source.number[i] - ASCII_TO_INT_OFFSET);
			if (ret) {
				break;
			}
		}
	}

	return ret;
}

Integer Integer::operator++(int nill) {
	Integer _Instance = Integer(*this);
	*this += Integer(1);
	return _Instance;
}

Integer Integer::operator++() {
	*this += Integer(1);
	Integer _Instance = Integer(*this);
	return _Instance;
}

Integer Integer::operator--(int nill) {
	Integer _Instance = Integer(*this);
	*this -= Integer(1);
	return _Instance;
}

Integer Integer::operator--() {
	*this -= Integer(1);
	Integer _Instance = Integer(*this);
	return _Instance;
}

int Integer::operator[](int index) {
	size_t idx = static_cast<size_t>(index);
	if (idx >= this->number.length()) {
		return -1;
	}

	return this->number[idx] - ASCII_TO_INT_OFFSET;
}

std::ostream &operator<<(std::ostream &outputStream, const Integer &source) {
	outputStream << (source.isPositive ? "" : "-");
	std::string formatted = source.number;
	while (formatted.length() > 1 && formatted[0] == '0') {
		formatted.erase(0, 1);
	}
	outputStream << formatted;

	return outputStream;
}

std::istream &operator>>(std::istream &inputStream, Integer &source) {
	std::string buffered;
	
	buffered = "";
	source.number = "";
	inputStream >> buffered;

	size_t offset = 0;
	if (buffered.length() > 0 && buffered[0] == '-') {
		source.isPositive = false;
		offset++;
	}

	for (size_t i = offset; i < buffered.length(); i++) {
		switch (buffered[i]) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				source.number.push_back(buffered[i]);
				break;
			case '\0':
			default:
				i = buffered.length();
				break;
		}
	}

	if (source.number.empty()) {
		source.number = "0";
	}

	return inputStream;
}

//Constructors
Integer::Integer() :number("0"), isPositive(true) { }

Integer::Integer(const Integer &source) : number(source.number), isPositive(source.isPositive) {
	std::string formatted = this->number;
	while (formatted.length() > 1 && formatted[0] == '0') {
		formatted.erase(0, 1);
	}
	this->number = formatted;
}

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
	if (num.length() > 0) {
		this->isPositive = true;
		this->number = num;
		if (num[0] == '-') {
			this->isPositive = false;
			this->number = num.substr(1);
		}
	} else {
		this->isPositive = true;
		this->number = "0";
	}

	std::string formatted = this->number;
	while (formatted.length() > 1 && formatted[0] == '0') {
		formatted.erase(0, 1);
	}
	this->number = formatted;	
}

Integer::Integer(char* num, int size) {
	if (size > 0) {
		this->isPositive = true;
		this->number = num;
		if (num[0] == '-' && size > 1) {
			this->isPositive = false;
			num++;
			this->number = num;
		} else if (num[0] == '-' && size == 1) {
			this->isPositive = true;
			this->number = "0";
		}

		std::string formatted = this->number;
		while (formatted.length() > 1 && formatted[0] == '0') {
			formatted.erase(0, 1);
		}
		this->number = formatted;
	}
	
}

Integer::~Integer() {
	this->number.clear();
}
