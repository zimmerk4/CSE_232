/*
 * Lab01
 * Takes user input for days after 12/30/16 and returns the distance of New Horizons craft from earth. Returns both km
 * and miles as well as radio communication times.
 */


#include <iostream>
#include <iomanip>

int main() {
    // Constants

    int input;
    int kAuToKm = 149598000;
    int kAuToMiles = 92955800;
    double kStartingAu = 37.33;
    double kVelocityKm = 14.33;  // km/s
    double kVelocityMi = 8.9;  // mi/s
    int kSecondsInDay = (60*60*24);
    int kSpeedOfLight = 299792458;  // m/s

    //Gather input

    std:: cout << "Please input days past 12/30/16 and press Enter: " << std:: endl;
    std:: cin >> input;

    // Do math on input

    double km = ( input * kSecondsInDay * kVelocityKm ) + ( kStartingAu * kAuToKm );
    double miles = ( input * kSecondsInDay * kVelocityMi ) + ( kStartingAu * kAuToMiles );
    double au = km / kAuToKm;
    double radio_time = ( 2 * km / ( kSpeedOfLight / 1000 )) / 3600;

    // Format and display input

    std:: cout << std:: fixed;
    std:: cout << std:: setprecision(2);
    std:: cout << au << std:: endl;
    std:: cout << km << std:: endl;
    std:: cout << miles << std:: endl;
    std:: cout << radio_time << std:: endl;

    return 0;
}
