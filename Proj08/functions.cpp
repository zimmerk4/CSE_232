#include<iostream>
using std::cout; using std::endl;
#include<sstream>
#include<string>
using std::getline;
#include<cmath>
using std::sqrt; using std::pow;
#include "functions.h"
#include<exception>
using std::out_of_range;
#include<algorithm>
#include<iomanip>

string Node::to_string() const
{
	/*
		Returns a string of form label;(x,y) for a given node
	*/
	string str = "";
	str += this->label + ":(" + std::to_string(this->x) +"," + std::to_string(this->y) + ")";
	return str;
}

bool Node::equal_nodes(const Node &n)
{
	/*
		Determines in Node n's label is equal to calling node's label. Returns bool
	*/
	if (this->label == n.label)
	{
		return true;
	}
	else
	{
		return false;
	}
}

double Node::distance(const Node &n) const
{
	/*
		Finds and returns Euclidean distance between calling Node and Node n.
	*/
	double distance;
	distance = (sqrt(pow((this->x - n.x), 2) + pow((this->y - n.y), 2)));
		return distance;
}

Network::Network(ifstream &f)
{
	/*
		Reads a file and builds a map of Nodes from file contents.
	*/
	string line;
	string param;
	vector<string> params;

	while (std::getline(f, line))  // Gets line from file
	{
		std::istringstream s(line);
		while (std::getline(s, param, ' '))  // Gets space separated paramaters from line
		{
			params.push_back(param);
		}
		Node node = Node(stoi(params[0]), stoi(params[1]), params[2]);
		nodes[params[2]] = node;
		params.clear();
	}
}

string Network::to_string() const
{
	/*
		Returns a string consisting of Node.to_string() call on all Node in nodes.
	*/
	string str;

	for (auto node : nodes)
	{
		str += node.second.to_string() + ", ";
	}
	str.resize(str.size() - 2);
	return str;
}

Node Network::get_node(string s)
{
	/*
		Gets and returns a Node from nodes by its string label, s. Throws out_of_range 
		exception if s cannot located in nodes
	*/
	Node node;
	if (nodes.count(s) < 1)
		throw out_of_range("Node not found:" + s);
	else
		node = nodes[s];
	return node;
}

void Network::put_node(Node n)
{
	/*
		Adds Node n to nodes map in Network. {label:Node}
	*/
	nodes[n.label] = n;
}

bool Network::in_route(const Node &node)
{
	/*
		Determines if Node node is in calling Network's route vector. Returns true/false
	*/
	// Nifty way to find if element in vector but not all that readable
	return std::find(route.begin(), route.end(), node.label) != route.end();
}

Node Network::closest(Node &n)
{
	/*
		Finds and returns closest Node to n by calling Node.distance().
	*/
	string label_min = n.label;
	double checkval = std::numeric_limits<int>::max();
	for (auto node : nodes)
	{
		if (node.second.label != n.label && !in_route(node.second))
		{
			double distance = n.distance(node.second);
			if (distance < checkval)
			{
				checkval = distance;
				label_min = node.second.label;
			}
		}
	}
	Node ret_node = get_node(label_min);
	return ret_node;
}

string Network::calculate_route(const Node &start, const Node &finish)
{
	/*
		Finds the total distance and the route from start Node to finish. Returns a formatted
		string of the total distance and Node path.
	*/
	string route_str;
	Node prev_node = start;
	Node closest_node = start;
	double tot_dist = 0;
	while (closest_node.label != finish.label)
	{
		if (!in_route(closest_node))
		{
			route.push_back(closest_node.label);
			prev_node = closest_node;
			closest_node = closest(closest_node);
			tot_dist += prev_node.distance(closest_node);
		}
	}
	route.push_back(closest_node.label);  // Push back final node in route
	std::ostringstream out;
	out << std::setprecision(7) << tot_dist;  // Set max double precision to match output10 format
	route_str += out.str();
	route_str.resize(route_str.size() - 1);
	route_str += ": ";
	for (auto i : route)
		route_str += i + ",";
	route_str.resize(route_str.size() - 1);
	return route_str;
}
