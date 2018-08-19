// Calc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "stdafx.h"
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <string>		// std::string
#include <algorithm>	// 
#include <array>
#include <vector>
using namespace std;

int fileInput(char* inFile);
int standardInput();
int PL_constructor(string raw);

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
	while (std::getline(ifs, temp)) {
		temp.erase(remove_if(temp.begin(), temp.end(), isspace), temp.end());
		cout << temp;
		//Processing happens right here
		PL_constructor(temp);
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
		PL_constructor(temp);
		std::getline(cin, temp);
	}


	return 0;
}

//Prototype constructor for the Parsed Line Class

int PL_constructor(string raw) {
	cout << "Calling PL_con" << endl;
	vector<string> subs;
	int asciiVal = 65;
	while (raw.length() > 3) {											//string has more than 1 expression to be evaluated
		cout << "\nCurrent value of raw: " << raw << "\nCurrent values of subs:";
		for (auto i : subs)
			std::cout << i << " ";
		cout << endl;
		size_t l_paren = raw.find_last_of("(");									//check for paren
		if (l_paren != string::npos) {											//paren exists, make sub
			size_t r_paren = raw.find_first_of(")", l_paren);					//find matching right paren
			subs.push_back(raw.substr(l_paren+1, r_paren - l_paren  - 1));		//add this sub to subs vector

			raw.erase(l_paren, r_paren - l_paren + 1);							//replace with var
			string asciiChar(1, char(asciiVal++));						
			raw.insert(l_paren, asciiChar);
		}
		else {																	//No parenthsis left to parse, evaluate as normal
			subs.push_back(raw);
			raw = "";

		}
	}
	cout << "\nCurrent value of raw: " << raw << "\nCurrent values of subs:";
	for (auto i : subs)
		std::cout << i << " ";
	cout << endl;
	return 1;
};

//Prototype expression evaluator function 
//string evaluateExpression(string raw) {
//	array<char, 4> validOperators = {'*', '/', '+', '-'};
//	string::size_type position;
//
//	for (int i = 1; i < 4; i++) {
//		while ((position = raw.find_first_of(validOperators[i])) != string::npos) {
//			float left = stof(raw.substr(0, position - 1));
//			float right = stof(raw.substr(position + 1, raw.back()));
//			cout << "Left and right: " << left << ", " << right << endl;
//		}
//	}
//	return "";
//};





class ParsedLine {
public:



private:

};