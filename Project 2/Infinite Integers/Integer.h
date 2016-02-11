#ifndef INTEGER_H
#define INTEGER_H
#include <string>
#include <iostream>

namespace project {
	class Integer {
		private:
			std::string number;
			bool isPositive;
		public:
			Integer();
			Integer(const Integer& const);
			Integer(const Integer* const);
			Integer(int);
			Integer(long);
			Integer(long long);
			Integer(std::string);
			Integer(char*);

			Integer operator =(Integer);
			Integer operator =(Integer&);
			Integer operator =(Integer*);

			Integer operator +(const Integer&) const;
			Integer operator -(const Integer&) const;
			Integer operator *(const Integer&) const;
			Integer operator +=(const Integer&) const;
			Integer operator -=(const Integer&) const;
			Integer operator *=(const Integer&) const;

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

			friend std::ostream& operator <<(std::ostream& outputStream, const Integer&);
			friend std::istream& operator >>(std::istream& inputStream, Integer&);
	};
}
#endif