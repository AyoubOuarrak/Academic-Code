#include "Rational.hh"
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <string>

Rational::Rational(long int num , long int den) {
	if (den == 0)
		throw std::invalid_argument("denominatore nullo");

	num_ = num;
	den_ = den;
	
	try {
		reduce();
	}
	catch(const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		throw;
	}
}

Rational 
Rational::operator+(const Rational& r1) const {
	Rational r;
	
	r.num_ = (this->num_ * r1.den_) + (r1.num_ * this->den_);
	r.den_ = this->den_ * r1.den_;
	
	try {
		r.reduce();
	}
	catch(const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		throw;
	}

	assert(r.check());
	return r;
}

Rational 
Rational::operator*(const Rational& r1) const {
	Rational r;
	
	r.num_ = this->num_ * r1.num_;
	r.den_ = this->den_ * r1.den_;
	
	try {
		r.reduce();
	}
	catch(const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		throw;
	}

	assert(r.check());
	return r;
}

Rational 
Rational::operator-(const Rational& r1) const {
	Rational r;
	
	r.num_ = (this->num_ * r1.den_) - (r1.num_ * this->den_);
	r.den_ = this->den_ * r1.den_;
	
	try {
		r.reduce();
	}
	catch(const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		throw;
	}

	assert(r.check());
	return r;
}

Rational 
Rational::operator/(const Rational& r1) const {
	Rational r;
	
	r.num_ = this->num_ * r1.den_;
	r.den_ = this->den_ * r1.num_;
	
	try {
		r.reduce();
	}
	catch(const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		throw;
	}

	assert(r.check());
	return r;
}

void Rational::reduce() {
    long int loop;
    long int largest;
    long int gcd = 1;

    largest = (num_ > den_) ? num_ : den_;

    for (loop = 2; loop <= largest; ++loop) {
        if (((num_ % loop) == 0L) && ((den_ % loop) == 0L))
        	gcd = loop;
    }

    num_ /= gcd;
    den_ /= gcd;

    if (den_ < 0) {
    	den_ = -den_;
    	num_ = -num_;
    }

    if (den_ == 0)
    	throw std::invalid_argument("denominatore nullo");
}

void Rational::print(std::ostream& os) const {
	char separator = '/';

	if (den_ == 1) {
		os << num_ 
		   << std::endl;
	}
	else {
		os << num_       
	   << separator 
       << den_       
	   << std::endl;
	}
}

bool Rational::check() {
#ifndef NDEBUG
	std::string error = "violata invariante : ";
#endif

#ifndef NDEBUG
	if (den_ == 0) {
		std::cerr << error
			      << "denominatore nullo" 
			      << std::endl;
		return false;
	}
#endif


#ifndef NDEBUG
	if (num_ > 0 && den_ < 0) {
		std::cerr << error
			      << "numeratore positivo, denominatore negativo" 
			      << std::endl;
		return false;
	}
#endif

#ifndef NDEBUG
    if (num_ < 0 && den_ < 0) {
    	std::cerr << error
			      << "numeratore negativo, denominatore negativo" 
			      << std::endl;
		return false;
	}
#endif
	return true;
}