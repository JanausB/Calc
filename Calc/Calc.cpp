// Calc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "stdafx.h"
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <string>		// std::string
#include <algorithm>	// 
using namespace std;

int fileInput(char* inFile);
int standardInput();

int main(int argc, char *argv[])
{
	if (argc >= 3){
		std::cerr << "Usage: \n"
				  << "To read from file: " << argv[0] << " inputFile.txt \n" 
				  << "To evaluate individual lines: " << argv[0] << std::endl;
	}
	else if (argc == 2)						//Multiple command line arguments, reading from file
		fileInput(argv[1]);
	else									//Prompting user for standard input
		standardInput();
	return 0;
}

int fileInput(char* inFile) {
	cout << "Reading from file: " << inFile << endl;
	ifstream ifs (inFile, ifstream::in);
	string temp = "";
	std::getline(ifs, temp);
	while (!temp.empty()) {
		temp.erase(remove_if(temp.begin(), temp.end(), isspace), temp.end());
		cout << temp;
		//Processing happens right here

		std::getline(ifs, temp);
	}
	standardInput();
	return 0;
}

int standardInput() {
	cout << "Reading from std::cin, input 'q' to quit." << endl;
	string temp = "";
	std::getline(cin, temp);
	while (!temp.empty() && temp != "q" && temp != "Q") {
		temp.erase(remove_if(temp.begin(), temp.end(), isspace), temp.end());
		cout << temp << endl;
		//Processing happens right here

		std::getline(cin, temp);
	}


	return 0;
}


class ParsedLine {
public:

};