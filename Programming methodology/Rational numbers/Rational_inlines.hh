#ifndef Rational_INLINES_HH
#define Rational_INLINES_HH

inline Rational 
Rational::operator+=(const Rational& r1) {
	*this = *this + r1;
	return *this;
}


inline Rational 
Rational::operator-=(const Rational& r1) {
	*this =*this - r1;
	return *this;
}

inline Rational 
Rational::operator*=(const Rational& r1) {
	*this = *this * r1;
	return this->operator*(r1);
}

inline Rational 
Rational::operator/=(const Rational& r1) {
	*this = *this / r1;
	return *this;
}

inline const Rational
Rational::operator++(int){
	Rational backup = *this;
	num_ += den_;

	return backup;
}

inline const Rational& 
Rational::operator++(){
	num_ += den_;

	return *this;
}

inline const Rational 
Rational::operator--(int) {
	Rational backup = *this;
	num_ -= den_;

	return backup;
}

inline const Rational& 
Rational::operator--() {
	num_ -= den_;

	return *this;
}

inline Rational
Rational::operator-() {
	num_ = -num_;

	return *this;
}

inline Rational
Rational::operator+() {
	return *this;
}

inline bool 
Rational::operator<(const Rational& rhs) const {
	return (num_ * rhs.den_) < (rhs.num_ * den_);
}

inline bool 
Rational::operator>(const Rational& rhs) const {
	return rhs < *this;
}

inline bool 
Rational::operator<=(const Rational& rhs) const {
	return !(rhs < *this);	
}

inline bool 
Rational::operator>=(const Rational& rhs) const {
	return (num_ * rhs.den_) == (rhs.num_ * den_);
}

inline bool  
Rational::operator==(const Rational& rhs) const {
	return (this->num_ == rhs.num_) && (this->den_ == rhs.den_);
}

inline bool 
Rational::operator!=(const Rational& rhs) const {
	return !(*this == rhs);	
}

inline std::ostream& 
operator<<(std::ostream& os, const Rational& r1) {
	r1.print(os);
	return os;
}
#endif /* Rational_INLINES_HH */