#ifndef MYSET_H
#define MYSET_H
#include <vector>
#include <ostream>

class MySet {
private:	
	unsigned int* bitset;
	size_t size;
public:
	MySet();
	~MySet();
	MySet(std::vector<int>&);
	MySet(const MySet&);

	void insert(int);
	void remove(int);
	void operator=(const MySet&);
	MySet operator+(const MySet&) const;
	MySet operator-(const MySet&) const;
	MySet operator&(const MySet&) const;
	bool operator==(const MySet&) const;
	friend std::ostream& operator<<(std::ostream&, const MySet&);
};
#endif