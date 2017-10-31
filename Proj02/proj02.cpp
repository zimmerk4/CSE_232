// proj02.cpp

#include <iostream>


long gcd(long, long);

long phi(long);

int main()
{
	int wait;
	long int_1, int_2, int_3;
	std::cin >> int_1 >> int_2 >> int_3;

	if (int_1 < 1 || int_2 < 1 || int_3 < 1) {
		std::cout << "Error" << std::endl;

	}
	else if (int_1 > int_2) {
		std::cout << gcd(int_2, int_1) << std::endl;
		std::cout << phi(int_3) << std::endl;
	}
	else if (int_1 < int_2) {
		std::cout << gcd(int_1, int_2) << std::endl;
		std::cout << phi(int_3) << std::endl;
	}
}

long gcd(long a, long b) {

	/*
	  Calculates the gcd of two positive integers. Ints may be entered in any order. 
	  An error will be given if negative ints provided. Utilizes Euclid's algorithm to calculate
	  the gcd. Returns the gcd.
	*/

	long r = 100;  // r initialized to arbitrarily number higher than 0
	long q;
	while (r > 0) {  
		q = b / a;  
		r = b % a;
		b = a;
		a = r;
		//std::cout << "q is: " << q << std::endl;
		//std::cout << "b is: " << b << std::endl;
		//std::cout << "r is: " << r << std::endl;	
	}
	return b;
}

long phi(long number ) {

	/*
	  Calcualates the totient of a given number. It finds the relative primes between 1 and
	  the given integer, outputs them, and returns the total number of relative primes. 
	  Utilizes the gcd() function to calculate relative primes.
	*/

	long totient = 0;
	for (int i = 1; i <= number; i++) {
		if (gcd(i, number) == 1) {
			std::cout << i << " ";
			totient++;
		}
	}
	std::cout <<std::endl;
	return totient;
}
