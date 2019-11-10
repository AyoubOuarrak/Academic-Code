#include "Rational.hh"
#include <stdexcept>
#include <iostream>

int main() {
	/* fase 1 : creazione oggetti*/ 
	Rational r1(7, 2);
	Rational r2(9, 4);
	Rational r3(1, 3);

	std::cerr << "*** STAGE 1 : ***" << std::endl;

	std::cerr <<" R1: "<< r1 << std::endl;
	std::cerr <<" R2: "<< r2 << std::endl;
	std::cerr <<" R3: "<< r3 << std::endl;

	/* fase 2 : operazioni aritmentiche */
	std::cerr << "*** STAGE 2 : ***" << std::endl;

	r1.reset();
	r2.reset();
	r3.reset();
	
	try {
		r1 = r2 + r3;
		r2 = r3 + r1;
		r3 = r1 + r2;
		std::cerr <<" R2 + R3 = "<< r1 << std::endl;
		std::cerr <<" R3 + R1 = "<< r2 << std::endl;
		std::cerr <<" R1 + R2 = "<< r3 << std::endl;
	} 
	catch(...) {
		std::cerr << "eccezione : +";
	}

	r1.reset();
	r2.reset();
	r3.reset();
	
	try {
		r1 = r2 - r3;
		r2 = r3 - r1;
		r3 = r1 - r2;
		std::cerr <<" R2 - R3 = "<< r1 << std::endl;
		std::cerr <<" R3 - R1 = "<< r2 << std::endl;
		std::cerr <<" R1 - R2 = "<< r3 << std::endl;
	}
	catch(...) {
		std::cerr << "eccezione : -";
	}
	
	r1.reset();
	r2.reset();
	r3.reset();
	
	try {
		r1 = r2 * r3;
		r2 = r3 * r1;
		r3 = r1 * r2;
		std::cerr <<" R2 * R3 = "<< r1 << std::endl;
		std::cerr <<" R3 * R1 = "<< r2 << std::endl;
		std::cerr <<" R1 * R2 = "<< r3 << std::endl;
	}
	catch(...) {
		std::cerr << "eccezione : *";	
	}
	
	r1.reset();
	r2.reset();
	r3.reset();
	
	try {
		r1 = r2 / r3;
		r2 = r3 / r1;
		r3 = r1 / r2;
		std::cerr <<" R2 / R3 = "<< r1 << std::endl;
		std::cerr <<" R3 / R1 = "<< r2 << std::endl;
		std::cerr <<" R1 / R2 = "<< r3 << std::endl;
	}
	catch(...) {
		std::cerr << "eccezione : /" << std::endl;
	}


	std::cerr << "*** STAGE 3 : ***" << std::endl;

	r1.reset();
	r2.reset();
	r3.reset();
	
	try {
		r1 += r2;
		r2 += r3;
		r3 += r1;
		std::cerr <<" R1 += R2 => "<< r1 << std::endl;
		std::cerr <<" R2 += R3 => "<< r2 << std::endl;
		std::cerr <<" R3 += R1 => "<< r3 << std::endl;
	}
	catch(...) {
		std::cerr << "eccezione : +=" << std::endl;
	}
	
	r1.reset();
	r2.reset();
	r3.reset();
	
	try {
		r1 -= r2;
		r2 -= r3;
		r3 -= r1;
		std::cerr <<" R1 -= R2 => "<< r1 << std::endl;
		std::cerr <<" R2 -= R3 => "<< r2 << std::endl;
		std::cerr <<" R3 -= R1 => "<< r3 << std::endl;
	}
	catch(...) {
		std::cerr << "eccezione : -=" << std::endl;
	}
	
	r1.reset();
	r2.reset();
	r3.reset();
	
	try {
		r1 *= r2;
		r2 *= r3;
		r3 *= r1;
		std::cerr <<" R1 *= R2 => "<< r1 << std::endl;
		std::cerr <<" R2 *= R3 => "<< r2 << std::endl;
		std::cerr <<" R3 *= R1 => "<< r3 << std::endl;
	}
	catch(...) {
		std::cerr << "eccezione : *=" << std::endl;
	}

	r1.reset();
	r2.reset();
	r3.reset();
	
	try {
		r1 /= r2;
		r2 /= r3;
		r3 /= r2;
		std::cerr <<" R1 /= R2 => "<< r1 << std::endl;
		std::cerr <<" R2 /= R3 => "<< r2 << std::endl;
		std::cerr <<" R3 /= R1 => "<< r3 << std::endl;
	}
	catch(...) {
		std::cerr << "eccezione : /=" << std::endl;
	}
	
	/* fase 3 : incrementi/decrementi postfissi/decrementi */
	std::cerr << "*** STAGE 4 : ***" << std::endl;

	r1.reset();
	r2.reset();
	r3.reset();
	
	try {
		r1++;
		std::cerr << " R1++  => " << r1 << std::endl;

		r2++;
		std::cerr << " R2++  => " << r2 << std::endl;

		r3++;
		std::cerr << " R3++  => " << r3 << std::endl;
	}
	catch(...) {
		std::cerr << "eccezione : ++E" << std::endl;
	}
	
	r1.reset();
	r2.reset();
	r3.reset();
	
	try {
		++r1;
		std::cerr << " ++R1  => " << r1 << std::endl;

		++r2;
		std::cerr << " ++R2  => " << r2 << std::endl;

		++r3;
		std::cerr << " ++R3  => " << r3 << std::endl;
	}
	catch(...) {
		std::cerr << "eccezione : ++E" << std::endl;
	}
	

	/* fase 4 : operazioni booleane */
	std::cerr << "*** STAGE 5 : ***" << std::endl;

	r1.reset();
	r2.reset();
	r3.reset();
	
	if (r1 > r2)
		std::cerr << " R1 > R2 " << std::endl;
	if (r2 > r3)
		std::cerr << " R2 > R3 " << std::endl;
	if (r3 > r1)
		std::cerr << " R3 > R1 " << std::endl;

	if (r1 < r2)
		std::cerr << " R1 < R2 " << std::endl;
	if (r2 < r3)
		std::cerr << " R2 < R3 " << std::endl;
	if (r3 < r1)
		std::cerr << " R3 < R1 " << std::endl;

	if (r1 >= r2)
		std::cerr << " R1 >= R2 " << std::endl;
	if (r2 >= r3)
		std::cerr << " R2 >= R3 " << std::endl;
	if (r3 >= r1)
		std::cerr << " R3 >= R1 " << std::endl;

	if (r1 <= r2)
		std::cerr << " R1 <= R2 " << std::endl;
	if (r2 <= r3)
		std::cerr << " R2 <= R3 " << std::endl;
	if (r3 <= r1)
		std::cerr << " R3 <= R1 " << std::endl;

	if (r1 == r2)
		std::cerr << " R1 = R2 " << std::endl;
	if (r2 == r3)
		std::cerr << " R2 = R3 " << std::endl;
	if (r3 == r1)
		std::cerr << " R3 = R1" << std::endl;

	if (r1 != r2)
		std::cerr << " R1 != R2 " << std::endl;
	if (r2 != r3)
		std::cerr << " R2 != R3 " << std::endl;
	if (r3 != r1)
		std::cerr << " R3 != R1 " << std::endl;
}