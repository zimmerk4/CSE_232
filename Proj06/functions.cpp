#include "functions.h"
#include <iostream>
#include <string>
using std::string;  using std::getline;
#include <vector>
using std::cout; using std::cin; using std::endl;
using std::vector;

vector<vector<int>> readImage(int col, int row)
{
	vector<vector<int>> image(row, vector<int>(col));
	string line = "";
	cin.ignore();  // Clears \n left in stream from cin in main so getline will return line
	for (int i=0; i<row; ++i)
	{
		getline(cin, line);
		//vector<int> temp;  // Spaceholder vector to be added to image
		//image.push_back(temp);
		int index = 0;
		for (auto c : line)  // Reads chars from getline string 
		{	
			if (c != ' ')  // Catches all non space characters and stores them in row vector
			{
				image[i][index] = (c - 48);
				++index;
				//image[i].push_back(c-48);  //pushes int value that char c represents
			}
		}
	}
	return image;
}

void printImage(vector<vector<int>> image)
{
	for (auto row : image)
	{
		for (auto col : row)
		{
			cout << col;
		}
		cout << endl;
	}
}

int countHoles(vector<vector<int>> image)
{
	int int_corners = 0;
	int ext_corners = 0;
	for (int i = 0; i < image.size() - 1; ++i)
	{
		for (int n = 0; n < image[i].size() - 1; ++n)
		{
			//cout << image[i][n];
			int pixel_sum = image[i][n] + image[i][n + 1] + image[i + 1][n] + image[i + 1][n + 1];
			if (pixel_sum == 1)
				++int_corners;
			else if(pixel_sum == 3)
				++ext_corners;
		}
		//cout << endl;
	}
	return (ext_corners - int_corners) / 4;
}
