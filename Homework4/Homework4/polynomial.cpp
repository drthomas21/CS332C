#include "polynomial.h"
#include <iostream>
#include <limits>

//Public functions
int Polynomial::getSize() {
	return this->size;
}
void Polynomial::operator-() {
	for (int i = 0; i < this->size; i++) {
		this->coefficients[i] *= -1;
	}
}

Polynomial Polynomial::operator-(const Polynomial& source) {
	Polynomial obj;
	int size = this->size > source.size ? this->size : source.size;
	obj.size = size;
	obj.coefficients = new double[size];
	for (int i = 0; i < size; i++) {
		double item1 = 0;
		double item2 = 0;
		if (i < this->size) {
			item1 = this->coefficients[i];
		}
		if (i < source.size) {
			item2 = source.coefficients[i];
		}
		obj.coefficients[i] = item1 - item2;
	}
	return obj;
}

Polynomial Polynomial::operator+(const Polynomial& source) {
	Polynomial obj;
	int size = this->size > source.size ? this->size : source.size;
	obj.size = size;
	obj.coefficients = new double[size];
	for (int i = 0; i < size; i++) {
		double item1 = 0;
		double item2 = 0;
		if (i < this->size) {
			item1 = this->coefficients[i];
		}
		if (i < source.size) {
			item2 = source.coefficients[i];
		}
		obj.coefficients[i] = item1 + item2;
	}
	return obj;
}

void Polynomial::operator=(const Polynomial& source) {
	this->size = source.size;
	if (this->coefficients != nullptr) {
		delete[] this->coefficients;
	}
	
	if (source.coefficients != nullptr) {
		this->coefficients = new double[this->size];
		for (int i = 0; i < this->size; i++) {
			this->coefficients[i] = source.coefficients[i];
		}
	}
}

void Polynomial::operator+=(const Polynomial& source) {
	Polynomial item = *this + source;
	this->size = item.size;
	if (this->coefficients != nullptr) {
		delete[] this->coefficients;
	}

	if (item.coefficients != nullptr) {
		this->coefficients = new double[this->size];
		for (int i = 0; i < this->size; i++) {
			this->coefficients[i] = item.coefficients[i];
		}
	}
}

void Polynomial::operator-=(const Polynomial& source) {
	Polynomial item = *this - source;
	this->size = item.size;
	if (this->coefficients != nullptr) {
		delete[] this->coefficients;
	}

	if (item.coefficients != nullptr) {
		this->coefficients = new double[this->size];
		for (int i = 0; i < this->size; i++) {
			this->coefficients[i] = item.coefficients[i];
		}
	}
}

bool Polynomial::operator ==(const Polynomial& source) {
	bool ret = this->size == source.size;
	if (ret && this->coefficients != nullptr && source.coefficients != nullptr) {
		for (int i = 0; ret && i < this->size; i++) {
			ret = this->coefficients[i] == source.coefficients[i];
		}
	} else if (ret && (this->coefficients != nullptr || source.coefficients != nullptr)) {
		ret = false;
	}

	return ret;
}

std::ostream &operator<<(std::ostream &output, const Polynomial &source) {
	if (source.coefficients != nullptr && source.size > 0) {
		for (int i = source.size-1; i >= 0; i--) {
			if (i > 0 && source.coefficients[i] != 0) {
				output << source.coefficients[i];
				if (i > 0) {
					output << "x";
				}
				if (i > 1) {
					output << "^";
				}
				if (i > 1) {
					output << i;
				}

				if (i > 0) {
					output <<  " +";
				}
				
				output << " ";
			}
			else if (i == 0) {
				output << source.coefficients[i];
			}
		}
	}	

	return output;
}

std::istream &operator>>(std::istream  &input, Polynomial &source) {
	if (source.coefficients == nullptr) {
		source.coefficients = new double[source.size];
	}

	for (int i = source.size-1; i >= 0; i--) {
		char value[100];
		input >> value;
		if (!atof(value)) {
			std::cout << "Invalid value" << std::endl;
			i++;
			continue;
		}
		if (input.eof()) {
			return input;
		}
		source.coefficients[i] = atof(value);
	}
	input.ignore(std::numeric_limits<int>::max(), '\n');

	return input;
}

Polynomial::Polynomial(int size) {
	this->size = size+1;
	this->coefficients = nullptr;
}

Polynomial::~Polynomial() {
	if (this->coefficients != nullptr) {
		delete[] this->coefficients;
	}
}

Polynomial::Polynomial(const Polynomial &source) {
	this->operator=(source);
}

Polynomial::Polynomial() {
	this->size = 0;
	this->coefficients = nullptr;
}