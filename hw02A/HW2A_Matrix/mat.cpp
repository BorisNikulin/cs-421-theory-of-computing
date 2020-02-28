#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

//--------------------------------------
// CS421 File mat.cpp for HW2A Matrix Practice
// Your name: **
//--------------------------------------

// the following can be changed and the rest of the code should work
int const R = 3;  // number of rows
int const C = 4;  // number of columns
int const VM = 3; // table entry (vector) length

vector<char>  T[R][C];  // 3 rows and 4 columns table for now 

// ------------------ Functions --------------------------------

int convert(char x)
{ 
  ** do a formula to convert a to 0, b to 1, c to 2 etc.
} 

int readTable()
{  int row, col;  // row and col numbers
   char col_c;     // column indicator
   ifstream fin ("lines.txt", ios::in);
 
  // Read in the file into T
   while (fin >> row) // next line of file
     {
       fin >> col_c; col = convert(col_c);  // convert to a slot number
       vector<char> v;  // a vector to fill
       char c; // one char from the file

       // ** Fill v with chars from the file (there are VM chars)
       // ** Put  v in T[row][col]
     }//end of while
}

// Displays a vector or "---" if the vector is empty
void showVector(vector<char> v)
{ if (v.size() == 0)  // empty entry
    for (int i = 1; i <= VM; i++) cout << "- ";
  else
    // show the content of v separated by blanks (e.g. "a b c")
}

// Displays T as a table, separating entries with "|" 
void displayTable()
{
  // ** display T nicely labeled with row numbers (col numbers not needed)
  //    by calling showVector 
}


// Driver
int main()
{
  cout << "Reading table from lines.txt..." << endl;
  readTable(); 
  displayTable();  
}//the end
