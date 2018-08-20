#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
class ParsedLine
{
public:
	// These indexes are how subexpressions will be represented inside their parent expression's string
	// as well as the values to which they will be mapped.
	string graphIndex = "A";

	// Primary storage for expaned tree representation
	// Pairs will be of the format <string graphIndexValue, string subexpression>
	map<string, string> subs;

	// Constructor for the ParsedLine object, makes a call to extractNestedExpressions to populate subs
	// Objects will be a tree with nodes represented by map enteries and edges existing via reference
	ParsedLine(string raw);

	// Produces an index by which sub-expressions will be referenced
	// valid indexes will consist of a trimmed string of at least one capital letter
	string getGraphIndex();

	//Function that takes in formatted string -> no whitespace and all multiplication is represented by "*" characters rather than numbers next to parenthesis
	//Output is a map of identifiers to sub-expressions
	map<string, string> extractNestedExpressions(string raw);

	// Debug function for printing the value of the subs map
	void print();

	// Resolve function that will traverse the map in an appropriate order and resolve the expression in each entry's second value
	float resolve();

	// Helper function to resolve()
	// Takes a string containing the operatators for this tier(ops) and the subexpression to resolve(eq)
	string resolveHelper(string ops, string eq);
};

