// Calc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ParsedLine.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include "stdafx.h"

using namespace std;

// Method to read from standard input
int standardInput() 
{
	cout << "Reading from std::cin, input 'q' to quit.\n" << endl;
	string temp = "";
	while (getline(cin, temp) && temp != "q" && temp != "Q") 
	{
		temp.erase(remove_if(temp.begin(), temp.end(), isspace), temp.end());
		if (!temp.empty()) 
		{
			cout << "Processing Formatted Line:" << temp;
			// Create ParsedLine object that will deconstruct the line into a tree and store it
			ParsedLine unprocessed(temp);
			// Print the status of all nodes
			unprocessed.print();
			// Resolve the tree and output the result
			cout << "Solution is: " << unprocessed.resolve() << "\n" << endl;
			cout << "\n\nReading from std::cin, input 'q' to quit." << endl;
		}
	}
	return 0;
}

// Method to  read from file
int fileInput(char* inFile) 
{
	cout << "Reading from file: " << inFile << endl;
	ifstream ifs(inFile, ifstream::in);
	string temp = "";
	while (std::getline(ifs, temp)) 
	{
		temp.erase(remove_if(temp.begin(), temp.end(), isspace), temp.end());
		if (!temp.empty()) {
			cout << "Processing Formatted Line:" << temp;
			// Create ParsedLine object that will deconstruct the line into a tree and store it
			ParsedLine unprocessed(temp);
			// Print the status of all nodes
			unprocessed.print();
			// Resolve the tree and output the result
			cout << "Solution is: " << unprocessed.resolve() << "\n" << endl;
		}
	}
	cout << "File Processed, changing mode to manual input...\n" << endl;
	standardInput();
	return 0;
}


int main(int argc, char *argv[])
{
	if (argc >= 3) 
	{
		std::cerr << "Usage: \n"
			<< "To read from file: " << argv[0] << " inputFile.txt \n"
			<< "To evaluate individual lines: " << argv[0] << std::endl;
		string temp;
		getline(cin, temp);
		return -1;
	}
	else if (argc == 2)//Multiple command line arguments, reading from file
		fileInput(argv[1]);
	else // No args, default to cin
		standardInput();
	return 0;
}