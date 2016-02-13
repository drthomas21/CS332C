#include "myset.h"
#include <vector>
#include <iostream>

//Public functions
const unsigned int BITSET_LIMIT = 32;

void MySet::insert(int num) {
	if (num >= static_cast<int>(BITSET_LIMIT * this->size)) {
		unsigned int* _list = this->bitset;
		size_t size = this->size;

		this->size = static_cast<size_t>(ceil(num / BITSET_LIMIT));
		this->bitset = new unsigned int[this->size];

		for (size_t i = 0; i < size; i++) {
			this->bitset[i] = _list[i];
		}
		delete[] _list;
		_list = nullptr;

		for (size_t i = size; i < this->size; i++) {
			this->bitset[i] = 0;
		}
	}

	size_t setIndex = static_cast<size_t>(floor(num / BITSET_LIMIT));
	size_t setOffset = static_cast<size_t>(num - (BITSET_LIMIT * setIndex));
	unsigned int item = 1 << static_cast<unsigned int>(num - (BITSET_LIMIT * setIndex));
	this->bitset[setIndex] = this->bitset[setIndex] | item;
}

void MySet::remove(int num) {
	if (num >= static_cast<int>(BITSET_LIMIT * this->size)) {
		return;
	}

	size_t setIndex = static_cast<size_t>(floor(num / BITSET_LIMIT));
	size_t setOffset = static_cast<size_t>(num - (BITSET_LIMIT * setIndex));
	unsigned int item = 1 << static_cast<unsigned int>(num - (BITSET_LIMIT * setIndex));
	this->bitset[setIndex] = this->bitset[setIndex] & ~item;
}

void MySet::operator=(const MySet &source) {
	this->size = source.size;
	if (this->bitset != nullptr) {
		delete[] this->bitset;
	}
	this->bitset = new unsigned int[this->size];
	for (size_t i = 0; i < source.size; i++) {
		this->bitset[i] = source.bitset[i];
	}
}
MySet MySet::operator+(const MySet &source) const {
	MySet newSet;
	size_t maxSize = this->size > source.size ? this->size : source.size;
	newSet.size = maxSize;
	newSet.bitset = new unsigned int[maxSize];

	for (size_t i = 0; i < maxSize; i++) {
		unsigned int item1 = 0;
		unsigned int item2 = 0;

		if (i < this->size) {
			item1 = this->bitset[i];
		}

		if (i < source.size) {
			item2 = source.bitset[i];
		}

		newSet.bitset[i] = item1 | item2;
	}
	return newSet;
}

MySet MySet::operator-(const MySet &source) const {
	MySet newSet;
	size_t maxSize = this->size > source.size ? this->size : source.size;
	newSet.size = maxSize;
	newSet.bitset = new unsigned int[maxSize];

	for (size_t i = 0; i < maxSize; i++) {
		unsigned int item1 = 0;
		unsigned int item2 = 0;

		if (i < this->size) {
			item1 = this->bitset[i];
		}

		if (i < source.size) {
			item2 = source.bitset[i];
		}

		newSet.bitset[i] = item1 & ~item2;
	}
	return newSet;
}

MySet MySet::operator&(const MySet &source) const {
	MySet newSet;
	size_t maxSize = this->size > source.size ? this->size : source.size;
	newSet.size = maxSize;
	newSet.bitset = new unsigned int[maxSize];

	for (size_t i = 0; i < maxSize; i++) {
		unsigned int item1 = 0;
		unsigned int item2 = 0;

		if (i < this->size) {
			item1 = this->bitset[i];
		}

		if (i < source.size) {
			item2 = source.bitset[i];
		}

		newSet.bitset[i] = item1 & item2;
	}
	return newSet;
}

bool MySet::operator==(const MySet &source) const {
	bool ret = this->size == source.size;
	if (ret) {
		for (size_t i = 0; i < this->size; i++) {
			ret = this->bitset[i] == source.bitset[i];
			if (!ret) {
				break;
			}
		}
	}
	return ret;
}

std::ostream& operator<<(std::ostream &output, const MySet &source) {
	output << "{";
	if (source.size > 0) {
		bool _pushedOne = false;
		for (size_t i = 0; i < source.size; i++) {
			for (int o = 0; o < BITSET_LIMIT; o++) {
				unsigned int shift = 1 << o;
				unsigned int diff = source.bitset[i] & shift;
				if (diff > 0) {
					if (_pushedOne) {
						output << ", ";
					}
					output << "x" << (i * BITSET_LIMIT + o);
					_pushedOne = true;
				}
			}
		}
	}
	output << "}";
	return output;
}

MySet::MySet() {
	this->size = 0;
	this->bitset = new unsigned int[this->size];
}

MySet::MySet(std::vector<int> &nums) {
	this->size = 3;
	this->bitset = new unsigned int[this->size];
	for (size_t i = 0; i < this->size; i++) {
		this->bitset[i] = 0;
	}
	
	for (std::vector<int>::iterator num = nums.begin(); num != nums.end(); ++num) {
		this->insert(*num);
	}
}

MySet::MySet(const MySet &source) {
	this->size = source.size;
	if (this->bitset != nullptr) {
		delete[] this->bitset;
	}
	this->bitset = new unsigned int[this->size];
	for (size_t i = 0; i < source.size; i++) {
		this->bitset[i] = source.bitset[i];
	}
}

MySet::~MySet() {
	delete[] this->bitset;
}