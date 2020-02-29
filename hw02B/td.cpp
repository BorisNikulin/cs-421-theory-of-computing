#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

//--------------------------------------
// CS421 File td.cpp for HW2B Table-Driven Scanner
// Your name: **
//--------------------------------------

// Complete this to fit the HW2B specification - look for **
// Must have the same types of tracing couts as my demo program.

// info on each DFA
struct info {
	string name; // token name
	int startstate;
	int finalstate;
};

/** Reads \ref info from input stream.
 */
istream& operator>>(istream& is, info& info)
{
	is >> info.name
		>> info.startstate
		>> info.finalstate;
	return is;
}

// DFA meta info
vector<info> DFAs;

// flat array with shape length/4 x 4
vector<int> TRS; // store all trs's - states 0-9 and chars a b c d -- all dfas transitions are in here

// ----- utility functions -----------------------

/** Indexes into transitions via a state id and char in [abcd].
 *
 * Does not do a bounds check.
 *
 * \param state start state of transiton
 * \param c character to supply to transition
 *
 * \returns index into transition table to find next state
 */
int shapedIndex(int state, char c)
{
	return state * 4 + c - 'a';
}

/** Converts transition table size to number of transitions.
 */
size_t numTransitions(size_t size)
{
	return size / 4;
}

void readTables(int argv, char** argc)
{
	ifstream trsIn;
	ifstream dfasIn;

	if(argv == 3)
	{
		trsIn.open(argc[1], ios::in);
		dfasIn.open(argc[2], ios::in);
	}
	else
	{
		trsIn.open("trs.txt", ios::in);
		dfasIn.open("dfas.txt", ios::in);
	}

	info infoIn;
	while(dfasIn >> infoIn)
	{
		DFAs.push_back(infoIn);
	}

	int states[4];
	while(trsIn >> states[0] >> states[1] >> states[2] >> states[3])
	{
		TRS.push_back(states[0]);
		TRS.push_back(states[1]);
		TRS.push_back(states[2]);
		TRS.push_back(states[3]);
	}
}

void displayTables()
{
	// ** display DFAs nicely labeled
	int stateDigits = floor(log10(numTransitions(TRS.size()) - 1)) + 1;

	// header
	cout << "      " << setw(stateDigits) << ' ' << "  "
		<< setw(stateDigits) << 'a' << ' '
		<< setw(stateDigits) << 'b' << ' '
		<< setw(stateDigits) << 'c' << ' '
		<< setw(stateDigits) << 'd' << " \n";

	for(size_t i = 0; i < numTransitions(TRS.size()); ++i)
	{
		cout << "State " << setw(stateDigits) << i << ": ";

		for(char c = 'a'; c <= 'd'; ++c)
		{
			int resultState = TRS[shapedIndex(i, c)];
			if(resultState != -1)
			{
				cout << setw(stateDigits) << resultState << " ";
			}
			else
			{
				cout << setw(stateDigits) << ' ' << ' ';
			}
		}

		cout << '\n';
	}

	cout << '\n';

	// ** display TRS nicely labeled
	for(info info : DFAs)
	{
		cout << left << setw(16) << info.name << ' '
			<< setw(stateDigits) << info.startstate << ' '
			<< setw(stateDigits) << info.finalstate
			<< '\n';
	}
}

bool accept(info dfa, string word)
{
	// ** Does the dfa accept the word?
	// Start with the start state of the DFA and
	// look up the next state in TRS for each char in word.
	// At the end of the word, make sure you are in the
	// final state of the DFA.
	// Use a formula to convert chars to TRS col numbers.

	int state = dfa.startstate;
	auto strIt = word.begin();

	while (state != -1 && strIt != word.end())
	{
		// only accept chars in our lang
		if (string("abcd").find(*strIt) == string::npos)
		{
			return false;
		}

		state = TRS[shapedIndex(state, *strIt)];
		++strIt;
	}

	return state == dfa.finalstate;
}

int main(int argv, char* argc[])
{
	cout << "This is a table driven scanner. Needs trs.txt and dfas.txt." << endl;
	cout << "States are 0 to 9 and chars are a to d" << endl;

	readTables(argv, argc); // how many DFAs were read
	displayTables(); // DISPLAY TABLES
	cout << ".....done reading tables...." << endl;

	string word;
	while (true) {
		cout << "@@Enter a string: ";
		cin >> word;

		bool accepted = false;
		auto dfaIt = DFAs.begin();

		while (!accepted && dfaIt != DFAs.end())
		{
			if(accept(*dfaIt, word))
			{
				cout << "Found token " << dfaIt->name << '\n';
				accepted = true;
			}

			++dfaIt;
		}

		if(!accepted)
		{
			cout << "Lexical Error!\n";
		}

		cout << "do control-C to quit" << endl;
	}

} //the end
