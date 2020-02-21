#include "binary_recognizer.h"
#include "generator_util.hpp"

#include <iostream>
#include <iterator>
#include <string>

int main()
{
	using namespace std;
	using namespace lang;

	while(true)
	{
		string in;
		getline(cin, in);
		string output = recognizer::binary(in) ? "Yes in L" : "No not in L";
		cout << output << "\n";
	}

	return 0;
}
