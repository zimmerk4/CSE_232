#include<iostream>
using std::cout; using std::cin; using std::endl;
using std::boolalpha;
#include<cmath>
using std::sqrt; using std::ceil; using std::round; using std::pow;
#include<string>
using std::string; using std::stol; using std::to_string; 
#include <algorithm>
using std::reverse;
// add whatever header stuff you need, delete anything you don't
// up to you


bool is_prime(long n);

bool is_semiprime(long n);

long reverse_num(long n);

bool is_palindrome(long n);

bool is_emirp(long n);

bool is_emirpimes(long n);

int main() {
	cout << boolalpha;

	int test_case;
	cin >> test_case;

	switch (test_case) {

	case 1: {
		long num;
		while (cin >> num)
			cout << num << ":" << is_prime(num) << endl;
		break;
	} // of case 1

	case 2: {
		long num;
		while (cin >> num)
			cout << num << ":" << reverse_num(num) << endl;
		break;
	} // of case 2

	case 3: {
		long num;
		while (cin >> num)
			cout << num << ":" << is_palindrome(num) << endl;
		break;
	} // of case 3   

	case 4: {
		long num;
		while (cin >> num)
			cout << num << ":" << is_emirp(num) << endl;
		break;
	} // of case 4

	case 5: {
		long num;
		while (cin >> num)
			cout << num << ":" << is_semiprime(num) << endl;
		break;
	} // of case 5

	case 6: {
		long num;
		while (cin >> num)
			cout << num << ":" << is_emirpimes(num) << endl;
		break;
	} // of case 6    

	} // of switch
} // of main


bool is_prime(long n)
/*
Standard prime number finding algorithm. Relies on the fact that any prime greater than 3 is of
the form 6k+1. Only searches between 5 and sqrt(n) to save time. Hard checks for primes up
to 5 and excludes 1. From proj03
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


bool is_semiprime(long n)
/*
Finds subprime numbers by checking that they contain precisely 2 prime factors. Multiplicites of 
factors is accounted for. e.g. 2x2x5=20. 2 and 5 are prime but 20 is not subprime. Returns true 
if semiprime.
*/
{
	int count = 0;  // Keeps count of number of prime factors
	for (long i = 2; i < n ; ++i)   
	{
		if (!(n % i) && is_prime(i))
		{
			//cout << "is prime factor: " << i << "; " << endl;
			for (int c = 2; pow(i, c) <= n; ++c)
			{
				//cout << "i to the: " << c << " is: " << pow(i, c) << endl;
				// Ensures multiplicities of i don't evenly divide n
				if ((pow(i, c) <= n ) && !(n % (long)pow(i, c)))
				{
					++count;
				}
			}
			++count;
			//cout << "count is: " << count << "\n" << endl;
		}
	}
	if (count == 2)
		return true;
	else
		return false;
}

long reverse_num(long n)
/*
Takes a long, n, converts it to a string, removes trailing 0's, reverses, and returns reversed
number.
*/
{
	long reverse_n;
	string str_n;

	str_n = to_string(n);	
	while(str_n.back() == '0')  // Removes all trailing zeros (VS and windows did not display leading zeros. This is a precaution)
		str_n.pop_back();
	reverse(str_n.begin(), str_n.end());
	reverse_n = stol(str_n);

	return reverse_n;
}

bool is_palindrome(long n)
/*
Function to check if long n is palindrome. Takes long, converts it to a reverse string calling
reverse_num() and then checks this against the string representation of n. Returns true if palindrome.
*/
{
	long palindrome_n = reverse_num(n);
	if (to_string(n) == to_string(palindrome_n))
		return true;
	else
		return false;
}

bool is_emirp(long n)
/*
Checks if both long n and its reverse are prime and not palindromic. Returns true if emirp
*/
{
	if (is_prime(n) && is_prime(reverse_num(n)) && !is_palindrome(n))
		return true;
	else
		return false;
}

bool is_emirpimes(long n)
/*
Determines if both a number and its reverse are unique primes. Palindromic primes are excluded. Utilizes the reverse_num(), is_semiprime(), and is_palindrome() functions. Returns true if emirpimes
*/
{
	if (is_semiprime(n) && is_semiprime(reverse_num(n)) && !is_palindrome(n))
		return true;
	else
		return false;
}


