#include<iostream>
using std::ostream;
#include<fstream>
using std::ifstream;
#include<map>
using std::map;
#include<string>
using std::string;
#include<exception>

#include "functions.h"

FSA::FSA(string strt, string stp)
{
	map<string, map<string, string>> table;
	table_ = table;
	start_ = strt;
	finish_ = stp;
	state_ = strt;
}

FSA::FSA(ifstream &fin)
{
	string line;
	long line_num = 0;
	while (std::getline(fin, line))
	{
		if (line_num == 0)
		{
			start_ = line[0];
			finish_ = line[2];
			state_ = line[0];
		}
		else
		{
			table_[string(1,line[0])][string(1,line[2])] = string(1,line[4]);
		}
		++line_num;
	}

}

bool FSA::exists_state(string s)
/*
	Takes a string s and returns true if the state it represents exists in table_
*/
{
	if (table_.count(s) != 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void FSA::add_state(string s)
/*
	Adds state string s to table_ if it doesnt exist. Throws a domain_error if it does.
*/
{
	map<string, string> temp_map;
	if (exists_state(s))
	{
		throw std::domain_error(s + " already exists");
	}
	else
	{
		table_[s] = temp_map;
	}
}

void FSA::add_transition(string s1, string input, string s2)
/*
	Adds transition from state s1 to s2 via input. If s1 does not exist in table_ a domain error is thrown.
*/
{
	if (!exists_state(s1))
	{
		throw std::domain_error(s1 + " doesn't exist");
	}
	else
	{
		table_[s1][input] = s2;
	}
}

string FSA::transitions_to_string(string s)
/*
	Returns a string representation of the transitions stored in state s in table_. Throws a domain_error
	if s doesn't exist in table_.
*/
{
	string temp_str("");
	if (!exists_state(s))
	{
		throw std::domain_error(s + " doesn't exist");
	}
	else
	{
		temp_str += s + ": ";
		for (auto p : table_[s])
		{
			temp_str += "on " + p.first + " -> " + p.second + ", ";
		}
	}
	return temp_str.substr(0, temp_str.length() - 2);
}

string FSA::next(string s, string input)
/*
	Returns the next transition in state s given input. Throws a domain error if s not in table_
	or if input is not a valid transition from s.
*/
{
	if (!exists_state(s))
	{
		throw std::domain_error(s +" doesn't exist");
	}
	else if (table_[s].count(input) != 1)
	{
		throw std::domain_error(s + " has no transition on input " + input);
	}
	else
	{
		return table_[s][input];
	}
}

bool FSA::run(string input)
/*
	Calls next() for each char in input starting from state_ == start_ and returning true if state_ == finish.
	Prints each successfule transition.
*/
{
	for (auto c : input)
	{
		string str = string(1, c);
		state_ = next(state_, str);
		std::cout << "Got to:" + state_ + " on a " + str << std::endl;
	}
	if (state_ == finish_)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ostream & operator<<(ostream &out, FSA &fsa)
/*
	Overloaded << operator to print object of type FSA in a meaningful way. Calls transition_to_string
	 and displays the member data of the instance of FSA.
*/
{
	out << "Start:" + fsa.start_ + ", " + "Finish:" + fsa.finish_ + ", " + "Present:" + fsa.state_
		<< std::endl;
	for (auto state : fsa.table_)
	{
		out << fsa.transitions_to_string(state.first) << std::endl;
	}
	return out;
}
