/*
 * Program to calculate amount of greenhouse gasses produced when given mpg of vehicle and miles driven in a year.
 */

#include <iostream>
#include <iomanip>

double CalcLbsGas( double mpg, double miles );

int main() {
    double mpg;
    double miles;

    std::cin >> mpg >> miles;
    std::cout << std:: fixed << std:: setprecision(2);
    std::cout << CalcLbsGas( mpg, miles ) << std::endl;
    std::cout << CalcLbsGas( mpg, miles ) - CalcLbsGas( mpg + 1, miles ) << std::endl;  // increment mpg by 1 find diff
    std::cout << CalcLbsGas( mpg, miles ) - CalcLbsGas( mpg + 5, miles ) << std::endl;  // increment mpg by 5 find diff

    return 0;
}

double CalcLbsGas( double mpg, double miles ){
    double  kghgRatio = 100/98.65;  // CO2 times this ratio equals ghg released
    double  kavgCarEmission = 19.6;  //lbs of ghg per gallon of fuel burned
    double gals = miles/mpg;
    double lbs_ghg = gals * kavgCarEmission * kghgRatio;

    return lbs_ghg;
}
