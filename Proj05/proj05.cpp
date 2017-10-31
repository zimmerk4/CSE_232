/*
 * Project 5: A program to encode and decode messages using Pangram key encryption.
 */

#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<string>
using std::string; using std::stoi; using std::to_string;
#include<sstream>
using std::ostringstream; using std::istringstream;
#include<iterator>
using std::distance; using std::back_inserter;
#include<algorithm>
using std::transform;
#include<cctype>

// whatever headers you need

// your functions here

string lower_and_strip(string s);
/*
 * Strips a string of all chars that are not letters. Returns string of letters in lowercase.
 */

int return_encoded_char(string key, string::size_type &start, char C);
/*
 * Encodes a char to an int using the pangram key and start parameter defined by the last character encoded.
 */

string encode(string message, string key);
/*
 * Encodes an entire string into ints using the pangram key and return_encoded_char() function
 */

char return_decoded_char(string key, string::size_type &start, int num);
/*
 * Decodes an int into a char using the pangram key and start parameter defined by the last character decoded.
 */

string decode(string encoded_text, string key);
/*
 * Decodes an entire string of integer values into chars using the pangram  key and return_decoded_char() function.
 */




int main (){
  cout << boolalpha;

  int test_case;
  cin >> test_case;

  switch (test_case){

  case 1 : {
    string line;
    cin.ignore(20, '\n');
    getline(cin, line);
    cout << lower_and_strip(line) << endl;
    break;
  } // of case 1

  case 2 : {
    string key;
    char C;
    int num;
    string::size_type start;
    cin.ignore(20, '\n');
    getline(cin, key);
    cin >> C;
    cin >> start;
    num = return_encoded_char (key, start, C); 
    cout << num << " " << start << endl;
    break;
  } // of case 2

  case 3 : {
    string key, line;
    string::size_type start=0;
    cin.ignore(20, '\n');
    getline(cin, key);
    getline(cin, line);
    cout << encode(line, key) << endl;
    break;
  } // of case 3   

  case 4 : {
    int num;    
    string key;
    char C;
    string::size_type start;
    cin.ignore(20, '\n');
    getline(cin, key);
    cin >> num;
    cin >> start;
    C = return_decoded_char (key, start, num);
    cout << C << " "<<start << endl;
    break;
  } // of case 4

  case 5 : {
    string key, line;
    string::size_type start=0;    
    cin.ignore(20, '\n');
    getline(cin, key);
    getline(cin, line);
    cout << decode(line, key) << endl;
    break;
  } // of case 5
    
  } // of switch

} // of main
  
string lower_and_strip(string s)
{
	string str_temp;

	for (auto c : s)
	{
		if (isalpha(c))  // Determines if char c is a letter and pushes it onto str_temp if so
		{
			str_temp.push_back(c);
		}
	}

	transform(str_temp.begin(), str_temp.end(), str_temp.begin(), ::tolower); // Iterates through str_temp and converts chars to lowercase in place
	return str_temp;
}

int return_encoded_char(string key, string::size_type& start, char C)
{
	int distance;

	if (key.find(C, start) <= key.length())  // Finds the chars that are between the start point and end of the key
	{
		distance = key.find(C, start) - start;  // Finds the distance between the char's index and the start point
		start = key.find(C, start);
		return distance;
	}
	else
	{
		if (key.find(C) <= key.length())  // Handles the wraparound case 
		{
			distance = key.length() - start + key.find(C);  // Finds distance between start and char with wraparound
			start = key.find(C, 0);
			return distance;
		}
		else  // Handles the char not found case
		{
			start = 0;
			return key.length() + 1;
		}
	}

}


string encode(string message, string key)
{
	string msg_lwr = lower_and_strip(message);
	string encoded_msg;
	string::size_type start = 0;

	for (auto c : msg_lwr)  // Encodes each character in the message using the return_encoded_char() function
	{
		encoded_msg += (to_string(return_encoded_char(key, start, c)) + " ");
	}
	return encoded_msg;
}

char return_decoded_char(string key, string::size_type & start, int num)
{
	char decoded_char;

	if (num <= key.length())  // Determines if the character is in the key
	{
		if (num + start <= key.length())  // Handles non-wraparound case
		{
			decoded_char = key.at(num + start);
			start = num + start;
			return decoded_char;
		}
		else  // Handles wraparound case
		{
			decoded_char = key.at(num + start - key.length());
			start = num + start - key.length();
			return decoded_char;
		}
	}
	else  // Handles char not in key
	{
		start = 0;
		return '_';
	}

}

string decode(string encoded_text, string key)
{
	string::size_type start = 0;
	string decoded_msg;
	string temp_str;

	for (auto c : encoded_text)  // Separates each encoded char from the next
	{
		if (c != ' ')
		{
			temp_str.push_back(c);  // Gathers encoded char's digits
		}
		else 
		{
			decoded_msg.push_back(return_decoded_char(key, start, stoi(temp_str))); // Gets char for the gathered encoded char when " " is hit in encoded_text
			temp_str = "";  // reset temp_str for next encoded char
		}
	}
	decoded_msg.push_back(return_decoded_char(key, start, stoi(temp_str)));  // To catch last encoded char
	return decoded_msg;
}
