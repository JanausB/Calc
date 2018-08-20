#include "stdafx.h"
#include "ParsedLine.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

// Constructor for the ParsedLine object, makes a call to extractNestedExpressions to populate subs
// Objects will be a tree with nodes represented by map enteries and edges existing via reference
ParsedLine::ParsedLine(string raw)
{
	subs = extractNestedExpressions(raw);
}

// Produces an index by which sub-expressions will be referenced
// valid indexes will consist of a trimmed string of at least one capital letter
string ParsedLine::getGraphIndex()
{
	string curr = graphIndex;
	// Add additional "digit" once Z is reached
	if (graphIndex.back() == 'Z') {
		graphIndex.back() = 'A';
		graphIndex.append("A");
	}
	else {
		graphIndex.back()++;
	}
	return curr;
}

	//Function that takes in formatted string -> no whitespace and all multiplication is represented by "*" characters rather than numbers next to parenthesis
	//Output is a map of identifiers to sub-expressions
map<string, string> ParsedLine::extractNestedExpressions(string raw)
{
	map<string, string> subs;
	// while raw has more than 1 expression to be evaluated
	while (raw.length() > 1)
	{
		size_t l_paren = raw.find_last_of("(");
		// Check for a left paren, if exists, find right and extract contents between
		if (l_paren != string::npos)
		{
			string index = getGraphIndex();
			size_t r_paren = raw.find_first_of(")", l_paren);
			// Save content in map to index
			subs[index] = raw.substr(l_paren + 1, r_paren - l_paren - 1);
			raw.erase(l_paren, r_paren - l_paren + 1);
			// Replace contents with the index
			raw.insert(l_paren, index);
		}
		else
		{
			//No parentheses left to parse, this is the final / root node
			subs.insert(pair<string, string>(getGraphIndex(), raw));
			//Clear raw to exit the loop
			raw = "";
		}
	}
	return subs;
}

// Debug function for printing the value of the subs map
void ParsedLine::print()
{
	cout << "\nString has been processed, printing sub-expressions:" << endl;
	for (const auto &p : subs)
	{
		std::cout << "subs[" << p.first << "] = " << p.second << '\n';
	}
}

// Resolve function that will traverse the map in an appropriate order and resolve the expression in each entry's second value
float ParsedLine::resolve()
{
	// Tiers of operators, allows the addition of custom operators w/ open lowercase letter namespace
	// Additional values to edit for custom operators: resolveHelper-> string allOperators & resolveHelper-> switch (eq[opPos])
	string t3 = "^";
	string t2 = "*/";
	string t1 = "+-";
	// Via the method in which subs is populated, inner-most nested subexpressions are higher in the sequential map order than their parents
	// Thus resolving subs' elements in order correctly evaluates the expression
	//DEBUG:
	cout << "Resolving subexpression values:" << endl;
	for (auto itr = subs.begin(); itr != subs.end(); ++itr)
	{
		// DEBUG: 
		cout << "subs[" << itr->first << "] = " << itr->second;
		// Call resolveHelper for each tier of operators
		string eq = itr->second;
		eq = resolveHelper(t3, eq);
		eq = resolveHelper(t2, eq);
		eq = resolveHelper(t1, eq);
		// DEBUG: 
		cout << " = " << eq << endl;
		itr->second = eq;
	}
	// After resolution finishes, the last element of subs is a solved root
	return stof(subs.rbegin()->second);
}


// Helper function to resolve()
// Takes a string containing the operatators for this tier(ops) and the subexpression to resolve(eq)
string ParsedLine::resolveHelper(string ops, string eq)
{
	// string of all valid operators- used for bound seeking
	string allOperators = "^*/+-";
	// While a valid operator of this tier exists in eq to resolve
	while (eq.find_first_of(ops) != string::npos)
	{
		// Position of operator to be evaluated this loop
		string::size_type opPos = eq.find_first_of(ops);

		// Right bound of the right arg
		string::size_type rightArgRightBound = eq.find_first_of(allOperators, opPos + 1);
		if (rightArgRightBound == string::npos)
			rightArgRightBound = eq.length();

		// Left bound of the left arg
		string::size_type leftArgLeftBound = 0;
		string::size_type peek = eq.find_first_of(allOperators, leftArgLeftBound);
		while (peek != string::npos && peek < opPos)
		{
			leftArgLeftBound = peek + 1;
			peek = eq.find_first_of(allOperators, leftArgLeftBound);
		}

		// Resolve the left arg to either a float or its precomputed value
		float lvalf;
		string lval = eq.substr(leftArgLeftBound, opPos - leftArgLeftBound);
		if (subs.find(lval) != subs.end())
			lvalf = stof(subs[lval]);
		else
			lvalf = stof(lval);
		// Resolve the right arg to either a float or its precomputed value
		float rvalf;
		string rval = eq.substr(opPos + 1, rightArgRightBound - 1);
		if (subs.find(rval) != subs.end())
			rvalf = stof(subs[rval]);
		else
			rvalf = stof(rval);

		// Evaluate operator via switch and replace the previous subexpression region with 
		float val;
		switch (eq[opPos])
		{
		case '+':
			val = lvalf + rvalf;
			break;
		case '-':
			val = lvalf - rvalf;
			break;
		case '*':
			val = lvalf * rvalf;
			break;
		case '/':
			val = lvalf / rvalf;
			break;
		case '^':
			val = powf(lvalf, rvalf);
			break;
		}
		string replacer = to_string(val);
		eq.replace(leftArgLeftBound, rightArgRightBound - leftArgLeftBound, replacer);
	}
	return eq;
}
