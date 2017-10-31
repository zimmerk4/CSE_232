
#include<iostream>
#include<cmath>


double fn(double x);

double integral(double x);

double trapezoid(double a, double b, long n);



int main()
{
	//std::cout << fn(1) <<std::endl;
	//std::cout << integral(1) <<std::endl;
	//std::cout << trapezoid(0, 1, 1) << std::endl;

	float tolerance;
	double guess_n;

	std::cout << "Tolerance: ";
	std::cin >> tolerance;
	std::cout << std::endl;
	std::cout << "Initial trapezoid count: ";
	std::cin >> guess_n;
	std::cout << std::endl;

	double diff = (integral(1) - integral(0)) - trapezoid(0, 1, guess_n);
	while (diff > tolerance)
	{
		std::cout << "Result: " << trapezoid(0, 1, guess_n) << ", traps: "<< guess_n << ", diff: " << diff << std::endl;
		guess_n *= 2;
		diff = (integral(1) - integral(0)) - trapezoid(0, 1, guess_n);
	}

	std::cout << "Trap count: " << guess_n << ", estimate: " << trapezoid(0, 1, guess_n) << "< exact: " << (integral(1) - integral(0));
	std::cout << ", tolerance: " << tolerance << std::endl;

    return 0;
}

double fn(double x)
{
	return -6*std::pow(x,2)+5*x+3;
}

double integral(double x)
{
	return -2 * std::pow(x, 3) + ((double)5 / 2)*std::pow(x, 2) + 3 * x;
}

double trapezoid(double a, double b, long n)
{
	//return ((b - a)*(fn(a) + fn(b))) / 2;
	double sum = 0;

	

	for (int i = 0; i <= n; i++)
	{
		if (i == 0)
			sum += fn(0);  // Adds in the f(x1) term
		else if (i == n)
			sum += fn(1);  // Adds in the f(N+1) term
		else
		{
			sum += 2 * fn((i * (b - a)) / n);  // Finds the (2f(x2)+2f(x2)...+2f(xN) terms)
		}
	}
	
	
	
	return (b - a) / (2 * n) * sum ;
}
