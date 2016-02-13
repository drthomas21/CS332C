#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>

class Polynomial {
	private:
		double *coefficients;
		int size;

	public:
		Polynomial();
		Polynomial(int);
		~Polynomial();
		Polynomial(const Polynomial&);
		int getSize();
		void operator-();
		Polynomial operator-(const Polynomial&);
		Polynomial operator+(const Polynomial&);
		void operator=(const Polynomial&);
		void operator+=(const Polynomial&);
		void operator-=(const Polynomial&);
		bool operator ==(const Polynomial&);
		friend std::ostream &operator<<(std::ostream &output, const Polynomial&);
		friend std::istream &operator>>(std::istream  &input, Polynomial&);
};

#endif