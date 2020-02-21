#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//--------------------------------------
// CS421 File mat.cpp for HW2A Matrix Practice
// Your name: **
//--------------------------------------

// the following can be changed and the rest of the code should work
int const R = 3; // number of rows
int const C = 4; // number of columns
int const VM = 3; // table entry (vector) length

vector<char> T[R][C]; // 3 rows and 4 columns table for now

// ------------------ Functions --------------------------------

/** Converts character to distance from ascii leter 'a'.
 *
 * This makes 'a' 0 and 'b' 1 and so on.
 */
int convert(char x)
{
	return x - 'a';
}

/** Reads a space separated table according to predefined format
 */
void readTable()
{
	int row, col; // row and col numbers
	char col_c; // column indicator
	ifstream fin("lines.txt", ios::in);

	// Read in the file into T
	while (fin >> row) // next line of file
	{
		fin >> col_c;
		col = convert(col_c); // convert to a slot number
		vector<char> v; // a vector to fill
		char c; // one char from the file

		// ** Fill v with chars from the file (there are VM chars)
		for (int i = 0; i < VM; ++i)
		{
			fin >> c;
			v.push_back(c);
		}

		// ** Put  v in T[row][col]
		T[row][col] = v;
	} // end of while
}

/** Displays a vector as a space separated list or "- - -" if empty
 */
void showVector(vector<char> v)
{
	if (v.size() == 0) // empty entry
		for (int i = 1; i <= VM; i++)
		{
			cout << "- ";
		}
	else
	{
		for (char c : v)
		{
			cout << c << " ";
		}
	}
	// show the content of v separated by blanks (e.g. "a b c")
}

// Displays T as a table, separating entries with "|"
void displayTable()
{
	for (size_t i = 0; i < R; ++i)
	{
		cout << i;
		for (size_t j = 0; j < C; ++j)
		{
			cout << "| ";
			showVector(T[i][j]);
		}
		cout << '\n';
	}
}

// Driver
int main()
{
	cout << "Reading table from lines.txt..." << endl;
	readTable();
	displayTable();
} // the end
