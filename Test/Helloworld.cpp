#include <iostream>
#include <string>

using namespace std;


int main() {
    cout << "Hello, World!" << endl;
    string input;
    cout << "Input characters to print to screen: ";
    getline(cin,input);
    cout << input << endl;
    return 0;
}
