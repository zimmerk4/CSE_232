#include "functions.h"
#include <iostream>
using std::cout; using std::cin; using std::endl; using std::getline;
#include <vector>
#include <string>
using std::basic_string; using std::to_string;
#include <algorithm>
using std::transform;
#include<cmath>
using std::sqrt;


string map_to_string(map<string, long>& m)
{
	/*
		Prints elements of map, m, as "string:long, " then removes trailing ", " from last element
	*/

	string str = "";
	for (auto pair : m)
	{
		str += pair.first + ":" + to_string(pair.second) + ", ";
	}
	str.erase(str.size()-2 );  // Removes trailing comma and space
	return str;
}

string vector_to_string(vector<pair<string, long>>& v)
{
	/*
	Prints pairs of vector v, as "string:long, " then removes trailing ", " from last element
	*/

	string str = "";
	for (auto pair : v)
	{
		str += pair.first + ":" + to_string(pair.second) + ", ";
	}
	str.erase(str.size() - 2);  // Removes trailing comma and space
	return str;
}

string clean_string(string w)
{
	/*
		Strips all chars other than alphabetic from string w. Returns str in lowercase
	*/

	string str = "";
	for (auto c : w)
	{
		if (c >= 0)  // Text files have non ascii chars, this filters them...
		{
			if (isalpha(c))
			{
				str += tolower(c);
			}
		}
	}
	return str;
}

vector<string> generate_ngrams(string w, size_t n)
{
	/*
		Builds n-grams from string w. N-gram defined as a susbstring of w of length n 
		for each character in w. ex. 2-gram  "foobar" = "fo" "oo" "ob" "ba" "ar"
	*/

	vector<string> v;
	//v.reserve()
	for (int i = 0; i <= (w.size()-n); ++i)
	{
		v.push_back(w.substr( i, n));
	}
	return v;
}

void process_line(map<string, long>& m, string line, size_t n)
{
	/*
		Calls clean_string() and generate_ngrams() to build a vector of ngrams. Takes the 
		vector of ngrams, adds each into a map and tracks their frequencies.
	*/
	line = clean_string(line);
	if (line != "")
	{
		vector<string> v = generate_ngrams(line, n);
		for (auto n_gram : v)
		{
			if (m.count(n_gram))  // Incriment frequency if in map
			{
				++m[n_gram];
			}
			else
			{
				m[n_gram] = 1;  // Add to map if not
			}
		}
	}
}

bool pair_string_lessthan(const pair<string, long>& p1, const pair<string, long>& p2)
{
	/*
		Returns true if the string of p1 is before the string of p2 in alphabetical order.
	*/
	return p1.first<p2.first;
}

bool pair_frequency_greaterthan(const pair<string, long>& p1, const pair<string, long>& p2)
{ 
	/*
		Returns true if the frequency of p1 is greater than p2.
	*/
	return p1.second>p2.second;
}

vector<pair<string, long>> top_n(map<string, long>& m, int num)
{
	/*
		Returns a vector with length num of the highest frequency ngrams in m. Ngrams with equal
		frequencies are sorted alphabetically.
	*/
	vector<pair<string, long>> v(num);
	vector<pair<string, long>> v_temp(m.size());
	pair<string, long> temp = { "" , 0 };

	// Sorts map into reverse alphabetical order
	for (int i = 0; i < v_temp.size(); ++i)
	{
		for (auto pair : m)
		{
			if (!pair_string_lessthan(pair, temp))
			{
				temp = pair;
			}
		}

		v_temp[i] = temp;
		m.erase(temp.first);  // Removes highest item in alphabetical order
		temp = { "", 0 };  // Reset temp to find next highest
	}
	
	for (int i = 0; i < num; ++i)
	{
		int index = 0;

		for (int n = v_temp.size(); n > 0; --n)  // Iterate backwards since in reverse alphabetical order
		{
			if (pair_frequency_greaterthan(v_temp[n-1], temp))
			{
				temp = v_temp[n-1];
				index = n-1;
			}
			
		}
		v[i] = temp;
		v_temp.erase(v_temp.begin() + index);  // Removes highest frequency from list
		temp = { "", 0 };  // Reset temp to find next highest
	}

	
	

	return v;
}

double ochiai(map<string, long>& m1, map<string, long>& m2)
{ 
	/*
		 the ochiai coefficient from maps m1 & m2 by building their intersection, map m3 and then comparing sizes as in the return statement.
	*/
	map<string, long> m3;  // Intersect of m1 & m2
	for (auto pair : m1)
	{
		if (m2.count(pair.first))
		{
			m3[pair.first] = 1;
		}
	}
	return (m3.size() / sqrt(m1.size() * m2.size()));
}

// Optional if I get to it
double ochiai2(map<string, long>& m1, map<string, long>& m2, int num)
{
	return 0.0;
}
