#ifndef INTEGER_H
#define INTEGER_H
#include <string>
#include <iostream>

class Integer {
private:
	const char digits[10] = { '0','1','2','3','4','5','6','7','8','9' };
	std::string number;
	bool isPositive;
public:
	~Integer();
	Integer();
	Integer(const Integer&);
	Integer(int);
	Integer(long);
	Integer(long long);
	Integer(std::string);
	Integer(char*, int);

	Integer operator =(const Integer&);

	Integer operator +(const Integer&) const;
	Integer operator -(const Integer&) const;
	Integer operator *(const Integer&) const;
	void operator +=(const Integer&);
	void operator -=(const Integer&);
	void operator *=(const Integer&);

	size_t length() const;

	bool operator >(const Integer&) const;
	bool operator <(const Integer&) const;
	bool operator >=(const Integer&) const;
	bool operator <=(const Integer&) const;
	bool operator ==(const Integer&) const;
	bool operator !=(const Integer&) const;

	Integer operator ++(int);
	Integer operator ++();
	Integer operator --(int);
	Integer operator --();

	int operator[](int);

	friend std::ostream& operator <<(std::ostream&, const Integer&);
	friend std::istream& operator >>(std::istream&, Integer&);
};
#endif