#include<iostream>
#include<cmath>
using std::cout; using std::cin; using std::endl;
using std::boolalpha;
// add any other includes you like.

// functions go here

bool is_prime(long n);

bool is_powerful(long n);

bool is_perfect_power(long n);

bool is_achilles(long n);


// main is below. You cannot modify main
int main (){
  cout << boolalpha;

  int test_case;
  cin >> test_case;

  switch (test_case){

  case 1 : {
    long num;
    while (cin >> num)
      cout << num << ":" << is_prime(num) << endl;
    break;
  } // of case 1

  case 2 : {
    long num;
    while (cin >> num)
      cout << num << ":" << is_powerful(num) << endl;
    break;
  } // of case 2

  case 3 : {
    long num;
    while (cin >> num)
      cout << num << ":" << is_perfect_power(num) << endl;
    break;
  } // of case 3   

  case 4 : {
    long num;
    while (cin >> num)
      cout << num << ":" << is_achilles(num) << endl;
    break;
  } // of case 4
    
  } // of switch
} // of main
    
bool is_prime(long n)
/*
  Standard prime number finding algorithm. Relies on the fact that any prime greater than 3 is of 
  the form 6k+1. Only searches between 5 and sqrt(n) to save time. Hard checks for primes up
  to 5 and excludes 1.
*/
{
	if (n <= 1)
		return false;
	else if (n == 2)
		return true;
	else if (n == 3)
		return true;
	else if (n % 2 == 0)
		return false;
	else if (n % 3 == 0)
		return false;

	long long i = 5;
	while (i*i <= n)
	{
		if (n % i == 0 || n % (i + 2) == 0)
			return false;
		i += 6;
	}
	return true;
}

bool is_powerful(long n)
/*
  Function to check if number is powerful. Takes a long int input, n, checks if all prime factors
  evenly divide into n, and returns bool true or false accordingly.
*/
{
	if (is_prime(n))
		return false;
	else if (n-1 <= 2)
		return false;
	else
	{
		long long i = 2;
		while (i <= n-1)
		{
			if (!(n % i) && is_prime(i))  // checks if n evenly divisible by i and if i is prime
			{
				//cout << "got prime factor " << i << " of " << n << endl;

				if ((n % (i*i)))  // Checks if n not evenly divisible by square of prime factor
					return false;
			}
			i ++;
		}
		return true;  // Returns true after all squared prime factors checked
	}
}

bool is_perfect_power(long n)
/*
  Function to test if a long int n is a perfect power such that an int m to the integer power k 
  exists that is equal to n. Returns a bool true/false accordingly. The algorithm uses 
  bruteforce case checking with optimization to only check bases up to sqrt(n) and only bases
  that evenly divide n.
*/
{
	for (long i = 2; i*i <= n; i ++)  // Sets the base, m, of the test
	{
		if (!(n % i))  // Checks to make sure base evenly divides n
		{
			for (long c = 2; std::pow(i, c) <= n; c++)  // Iterates through powers k
			{
				if (std::pow(i, c) == n)
					return true;
			}
		}
	}
	return false;
}

bool is_achilles(long n)
/*
  Utilizes the is_powerful() and is_perfect_power() functions to test if long n is an Achilles
  number. n must be powerful but not a perfect power.
*/
{
	if(is_powerful(n) && !is_perfect_power(n))
		return true;
	return false;
}
