#include <shape.hpp>

#include <istream>
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<string>
#include <sstream>
#include <deque>
using namespace std;

//---------------------------------------
// CS421 File ll1.cpp for HW3A LL1 Table-Driven Parser
// Your name: **
//---------------------------------------

// Complete this to fit the HW3A specification - look for **
// Must have the same types of tracing couts as my demo program.

// Feel free to use a stack class or use a vector
// to implement your stack.  The stack will contain characters.

std::deque<char> derivation;
sjp::vector::ShapedArray<vector<char>, 3, 2>  M;  // the table of rules
					   // 3 rows for S, A, B
					   // 2 rows for 0, 1
	   // Each slot contains a rule's right side
	   // which is a vector of characters

//	------- conversion functions ------------------------


// to convert non-terms S, A, B to table rows 0, 1, 2
int toRow(char C)
{
	switch (C)
	{
		case 'S':
			return 0;
		case 'A':
			return 1;
		case 'B':
			return 2;
		default:
			throw;
	}
}

// to convert '0' and '1' to table columns 0 and 1
int toCol(char c)
{
	return c - '0';
}

// to convert row 0, 1, 2 to non-terms S, A and B
char toNonterm(int r)
{
	switch (r)
	{
		case 0:
			return 'S';
		case 1:
			return 'A';
		case 2:
			return 'B';
		default:
			throw;
	}
}


// ** Then complete the following functions.-----------------------------

// to display a rule's rhs which is in vector V
void displayVector(vector<char> V)
{
	for(char c : V)
	{
		cout << c << ' ';
	}
}

// to read in the rules into M, make sure ; is not stored
void readrules(istream& rulesIn)
{
	// simple state machine
	enum class State { READ_ROW, READ_COL, READ_CHAR };

	State state = State::READ_ROW;
	char c;
	int col;
	int row;
	vector<char> rhs;

	while(rulesIn >> c)
	{
		switch (c)
		{
			// break state machine
			case ';':
			{
				M(row, col) = rhs;
				rhs.clear();
				state = State::READ_ROW;
				break;
			}

			default:
			{
				switch (state)
				{
					case State::READ_ROW:
						row = toRow(c);
						state = State::READ_COL;
						break;

					case State::READ_COL:
						col = toCol(c);
						rhs.push_back(c);
						state = State::READ_CHAR;
						break;

					case State::READ_CHAR:
						rhs.push_back(c);
						break;
				}
				break;
			}
		}
	}

	if (state != State::READ_ROW)
	{
		cout << "Bad rules file" << endl;
		throw;
	}

	// For each line of "rules" (e.g. S  0 A 0 ;)
	// The first char of a line determines the row of M
	// The second char of a line determine the column of M
	// Note that each entry of M (the second char up to ;)
	// will be a vector representing
	// the right hand side of a rule (rhs)


	// ** Display the table nicely
	//	use toNonterm to show row labels (S, A, B)
	//	use displayVector for each content
	for (size_t row = 0; row < 3; ++row)
	{
		cout << toNonterm(row) << ":";
		for (size_t col = 0; col < 2; ++col)
		{
			for (char c : M(row, col))
			{
				cout << " " << c;
			}
			cout << ";";
		}
		cout << endl;
	}
}

//	pushes V contents to the stack
void addtostack(const vector<char>& V)
{
	// push in reverse order
	// as the target is a stack
	for (auto it = V.rbegin(); it != V.rend(); ++it)
	{
		derivation.push_front(*it);
	}

	// **  be careful of the order
	// because 1 0 0 means 1 will be at the top of the stack
}

void printStack()
{
	cout << "Stack\n";
	if (derivation.empty())
	{
		cout << "[ empty ]\n";
	}
	else
	{
		for (char c : derivation)
		{
			cout << c << "\n";
		}
	}
	cout << "--------------\n";
}

void check(istream& sentence)
{
	// ** push 'S' onto the stack to start
	derivation.push_front('S');

	// ** display the stack vertically from top to bottom
	//
	printStack();

	char c;
	while (sentence >> c)
	{
		cout << "current char is: " << c << "\n";

		// Based on ss[i] and
		//    the top of stack, update the stack:
		// ** note that empty stack will cause immediate failure
		// ** note that top of stack terminal and ss[i] mismatching
		//    will cause immediate failure
		// ** note that no entry in M for the top of stack (non-terminal)
		//    and ss[i] will cause immediate
		//    failure	(use toRow and toCol to look up M)
		// ** otherwise, addtoStack the M entry based on ss[i] and the top of stack

		if (derivation.empty())
		{
			cout << ">>Error - stack is empty. Reject!\n";
			return;
		}
		char top = derivation.front();
		derivation.pop_front();

		switch (top)
		{
			// if non terminal
			case 'S':
			case 'A':
			case 'B':
				addtostack(M(toRow(top), toCol(c)));
				// reset input stream
				sentence.putback(c);
				cout << "adding rhs of a rule to the stack\n\n";
				break;

			// if terminal
			case '0':
			case '1':
			default:
				if (c == top)
				{
					cout << "matched!\n\n";
				}
				else
				{
					cout << ">>Mismatch error. Reject!\n";
					return;
				}
				break;
		}

		printStack();
	} // end of string


	if (derivation.empty())
	{
		cout << ">>Accept!\n\n";
	}
	else
	{
		cout << ">>Reject! input too short\n";
	}
// ** Here, check for success for failure based on stack empty or not
}

string usage(const char* progName)
{
	string progNameStr(progName);
	return "Usage: \n"
		"\t" + progNameStr + "\n"
		"\t" + progNameStr + " <rule file> <sentence>\n";
}

int main(int argc, char* argv[])
{
	// take file name from args preferably
	std::ifstream inRules;
	std::istringstream sentence;

	if (argc == 1)
	{
		inRules.open("rules");

		string ss;
		cout << "Enter a string made of 0's and/or 1's: ";
		cin >> ss;

		sentence.str(ss);
	}

	if (argc == 3)
	{
		inRules.open(argv[1]);

		std::string words(argv[2]);
		sentence.str(words);
	}
	else if (argc != 1)
	{
		std::cout << usage(argv[0]);
		return 0;
	}

	readrules(inRules);  // M is filled and displayed
	inRules.close();

	check(sentence);

	return 0;
}
