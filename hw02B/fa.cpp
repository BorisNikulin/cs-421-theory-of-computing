#include <fstream>
#include <iostream>
#include <string>
using namespace std;

//------------------------------------------------
// CS421 File fa.cpp for HW2B DFA->Scanner Function
// Your name: **
//------------------------------------------------

// ** Change this to fit the HW2B specification - look for **
// ** Must have the same types of tracing couts as mytoken.
// ** Must complete the ** comments with RE

// ---------- DFAs follow -------------------------

// MYTOKEN DFA done by Rika Sensei has a sample
// This FA is for a b^+
bool mytoken(string s)
{
    int state = 0;
    int charpos = 0;

    cout << "Trying the mytoken machine..." << endl;

    while (s[charpos] != '\0') {
        cout << "current state: " << state << endl;
        cout << "character: " << s[charpos] << endl;

        if (state == 0 && s[charpos] == 'a')
            state = 1;
        else if (state == 1 && s[charpos] == 'b')
            state = 2;
        else if (state == 2 && s[charpos] == 'b')
            state = 2;
        else {
            cout << "I am stuck in state " << state << endl;
            return (false);
        }
        charpos++;
    } //end of while

    // where did I end up????
    if (state == 2)
        return (true); // end in a final state
    else
        return (false);
} // end of mytoken

// IDENT DFA
// This FA is for RE: **
bool ident_token(string s)
{
    // [*] -> 0
    int state = 0;
    for (char c : s) {
        switch (state) {
        case 0:
            // 0 -> 1 : a,b
            if (string("ab").find(c) != string::npos) {
                state = 1;
            } else {
                return false;
            }
            break;
        case 1:
            // 1 -> 1 : a,b,2,3,_
            if (string("ab23_").find(c) == string::npos) {
                return false;
            }
            break;
        }
    }

    // 1 -> [*]
    return state == 1;
} //end of ident

// REAL DFA
// This FA is for RE: **
bool real_token(string s)
{
    // [*] -> 0
    int state = 0;
    for (char c : s) {
        switch (state) {
        case 0:
            // 0 -> 1 : .
            if (c == '.') {
                state = 1;
            }
            // 0 -> 0 : 2,3
            else if (string("23").find(c) == string::npos) {
                return false;
            }
            break;
        case 1:
            // 1 -> 2 : 2,3
            if (string("23").find(c) != string::npos) {
                state = 2;
            } else {
                return false;
            }
            break;
        case 2:
            // 2 -> 2 : 2,3
            if (string("23").find(c) == string::npos) {
                return false;
            }
        }
    }

    // 2 -> [*]
    return state == 2;
} //end of real

//INT DFA
// This FA is for RE: **
bool integer_token(string s)
{
    // [*] -> 0
    int state = 0;
    for (char c : s) {
        switch (state) {
        case 0:
            // 0 -> 1 : 2,3
            if (string("23").find(c) != string::npos) {
                state = 1;
            } else {
                return false;
            }
            break;
        case 1:
            // 1 -> 1 : 2,3
            if (string("23").find(c) == string::npos) {
                return false;
            }
        }
    }

    // 1 -> [*]
    return state == 1;
} // end of int

// -----------------------------------------------------

enum tokentype {
    ERROR,
    MYTOKEN,
    IDENT,
    REAL,
    INT
};

fstream fin; // file stream to use

// Scanner sets the_type and w - TO BE COMPLETED **
tokentype scanner(string& w)
{

    // This goes through all machines one by one on the input string w

    cout << endl;
    cout << ".....Scanner was called..." << endl;

    fin >> w; // grab next word from fain.txt
    cout << ">>>>>Word is:" << w << endl;

    //if (mytoken(w)) {
    //return MYTOKEN;
    //}
    // check each FA against the lexeme
    if (ident_token(w)) {
        return IDENT;
    } else if (real_token(w)) {
        return REAL;
    } else if (integer_token(w)) {
        return INT;
    }

    // ** add other if-then's here in the right order to go through
    // ** all FAs one by one and set the_type to be IDENT, REAL or INT.

    //none of the FAs returned TRUE
    cout << ">>>>>Lexical Error: The string is not in my language" << endl;
    return ERROR;
} //the very end of scanner

// The test-driver -- NO NEED TO CHANGE THIS
int main(int argv, char* argc[])
{
    //  take file as command line argument
    //  if given
    if (argv != 2) {
        string fname;
        cout << "Enter the input file name:";
        cin >> fname;
        fin.open(fname.c_str(), fstream::in);
    } else {
        fin.open(argc[1], fstream::in);
    }

    string tokens[5] = { "ERROR", "MYTOKEN", "IDENT", "REAL", "INT" };
    tokentype thetype;
    string theword;

    while (true) // keep on going
    {
        thetype = scanner(theword); // the paramers will be set by Scanner
        if (theword == "EOF")
            break;

        cout << ">>>>>Type is:" << tokens[thetype] << endl;
    }

    cout << ">>>>>End of File encountered" << endl;
    fin.close();
} // end of main
