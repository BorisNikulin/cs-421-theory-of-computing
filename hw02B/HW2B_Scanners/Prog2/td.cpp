#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

//--------------------------------------
// CS421 File td.cpp for HW2B Table-Driven Scanner
// Your name: **
//--------------------------------------

// Complete this to fit the HW2B specification - look for **
// Must have the same types of tracing couts as my demo program.


// info on each DFA
struct info
{
  string name;  // token name
  int startstate;
  int finalstate;
};

info DFAs[4];     // store up to 4 dfas' start and final

int  TRS[10][4];  // store all trs's - states 0-9 and chars a b c d -- all dfas transitions are in here 

// ----- utility functions -----------------------

int readTables()
{  

   ifstream fin ("trs.txt", ios::in);
   ifstream fin2 ("dfas.txt", ios::in);
   // ** Read in the files into TRS and DFAs
   // ** Return how many DFAs were read
}

void displayTables(int numDFAs)
{
  // ** display DFAs nicely labeled
  // ** display TRS nicely labeled
}

bool accept(info dfa, string word)
{
  // ** Does the dfa accept the word?
  // Start with the start state of the DFA and
  // look up the next state in TRS for each char in word.
  // At the end of the word, make sure you are in the 
  // final state of the DFA.
  // Use a formula to convert chars to TRS col numbers.
}


int main()
{
  cout << "This is a table driven scanner. Needs trs.txt and dfas.txt." << endl;
  cout << "States are 0 to 9 and chars are a to d" << endl;

  int numDFA = readTables(); // how many DFAs were read
  displayTables(numDFA);     // DISPLAY TABLES
  cout << ".....done reading tables...." << endl;

  string word;
  while(true)
    { cout << "@@Enter a string: " ;
      cin >> word;
      // ** try the DFAs one by one and see 
      //      if the word is accepted
      //      if so, display the word and the token name
      // ** if no DFA does, generate a lexical error message.
      cout << "do control-C to quit" << endl;
    }

}//the end
