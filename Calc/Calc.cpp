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
#include <map>
using namespace std;

int fileInput(char* inFile);
int standardInput();


class ParsedLine {
public:
	//These indexes are how subexpressions will be represented inside their parent expression
	//as well as the values to which they will be mapped
	string graphIndex = "A";
	map<string, string> subs;


	ParsedLine(string raw)
	{
		subs = extractNestedExpressions(raw);

	}

	string getGraphIndex() {
		string curr = graphIndex;
		if (graphIndex.back() == 'Z') {
			graphIndex.back() = 'A';
			graphIndex.append("A");
		}
		else {
			graphIndex.back()++;
		}
		return curr;
	}


	//Function that takes in formatted string - no whitespace and all multiplication is represented by "*" characters rather than numbers next to parenthesis
	//Output is a map of identifiers to subexpressions
	map<string, string> extractNestedExpressions(string raw) {
		map<string, string> subs;
		while (raw.length() > 1) {													//string has more than 1 expression to be evaluated
			size_t l_paren = raw.find_last_of("(");									//check for paren
			if (l_paren != string::npos) {											//paren exists, make sub
				string index = getGraphIndex();
				size_t r_paren = raw.find_first_of(")", l_paren);					//find matching right paren
				subs[index] = raw.substr(l_paren + 1, r_paren - l_paren - 1);
				raw.erase(l_paren, r_paren - l_paren + 1);							//replace with index
				raw.insert(l_paren, index);
			}
			else {																	//No parenthsis left to parse, evaluate as normal
				subs.insert(pair<string, string>(getGraphIndex(), raw));
				raw = "";
			}
		}
		return subs;
	}

	void print() {
		cout << "\nCurrent values of subs:" << endl;
		for (const auto &p : subs) {
			std::cout << "subs[" << p.first << "] = " << p.second << '\n';
		}
	}

	float resolve() {

	}

};

int fileInput(char* inFile) {
	cout << "Reading from file: " << inFile << endl;
	ifstream ifs (inFile, ifstream::in);
	string temp = "";
	while (std::getline(ifs, temp)) {
		temp.erase(remove_if(temp.begin(), temp.end(), isspace), temp.end());
		cout << temp;
		//Processing happens right here
		ParsedLine unprocessed(temp);
		unprocessed.print();
	}
	standardInput();
	return 0;
}

int standardInput() {
	cout << "Reading from std::cin, input 'q' to quit." << endl;
	string temp = "";
	std::getline(cin, temp);
	while (getline(cin, temp) && temp != "q" && temp != "Q") {
		temp.erase(remove_if(temp.begin(), temp.end(), isspace), temp.end());
		cout << temp << endl;
		//Processing happens right here
		ParsedLine unprocessed(temp);
		unprocessed.print();
		
	}
	return 0;
}





int main(int argc, char *argv[])
{
	if (argc >= 3) {
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