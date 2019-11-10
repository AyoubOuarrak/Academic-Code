#ifndef RATIONAL_HH_GUARD
#define RATIONAL_HH_GUARD

#include <iostream>

class Rational {

private:
	long int num_;
	long int den_;

	bool check();
	void reduce();

public:
	Rational() : num_(0), den_(1) {}
	explicit Rational(long int num) : num_(num), den_(1) {}
	Rational(long int num, long int den);
	Rational(const Rational& r1) = default;		     
	~Rational() = default;							    

	Rational& operator=(const Rational& r1) = default; 

	Rational operator+(const Rational& r1) const;
	Rational operator*(const Rational& r1) const;
	Rational operator-(const Rational& r1) const;
	Rational operator/(const Rational& r1) const;

	inline Rational operator+=(const Rational& r1);
	inline Rational operator-=(const Rational& r1);
	inline Rational operator*=(const Rational& r1);
	inline Rational operator/=(const Rational& r1);

	inline const Rational& operator++();
	inline const Rational operator++(int);

	inline const Rational& operator--();
	inline const Rational operator--(int);

	inline Rational operator-();
	inline Rational operator+();

	inline bool operator>(const Rational& rhs) const;
	inline bool operator<(const Rational& rhs) const;
	inline bool operator<=(const Rational& rhs) const;
	inline bool operator>=(const Rational& rhs) const;
	inline bool operator==(const Rational& rhs) const;
	inline bool operator!=(const Rational& rhs) const;

	void print(std::ostream& os) const;
	
};

std::ostream& operator<<(const std::ostream& out, const Rational& r1);

#include "Rational_inlines.hh"

#endif /* RATIONAL_HH_GUARD */