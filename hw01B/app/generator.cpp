#include "binary_recognizer.h"
#include "generator_util.hpp"

#include <iostream>
#include <iomanip>
#include <iterator>
#include <cstdlib>
#include <stdexcept>

int main(int argv, char* argc[])
{
	using namespace std;
	using namespace lang;

	int maxStringLength;
	const char alphabet[] = "012";
	generator::util::StringsFromAlphabet<const char*> allStrings(begin(alphabet), end(alphabet));
	int stringLength;
	float stringsRecognized = 0;
	float stringsTotal = 0;

	if(argv == 2)
	{
		try
		{
			maxStringLength = stoi(argc[1]);
		}
		catch(invalid_argument& e)
		{
			cout << "Please provide a valid integer.";
			return 0;
		}
	}
	else
	{
		cout << "One must provide one integer as an argument for the maximum length of strings to generate.\n";
		return 0;
	}

	do
	{
		auto lenAndIterPair = *allStrings;

		stringLength = get<0>(lenAndIterPair);
		auto lengthedStringsStart = get<1>(lenAndIterPair);
		auto lengthedStringsEnd = get<2>(lenAndIterPair);

		for(; lengthedStringsStart != lengthedStringsEnd; ++lengthedStringsStart)
		{
			string str = *lengthedStringsStart;
			if(recognizer::binary(str))
			{
				cout << setw(maxStringLength) << str << ": Yes in L\n";
				++stringsRecognized;
			}
			++stringsTotal;
		}
		++allStrings;
	} while(stringLength < maxStringLength);

	cout << setprecision(3)
		<< "Recognized " << stringsRecognized / stringsTotal << "% of strings"
		<< " (" << stringsRecognized << "/" << stringsTotal << ")\n";

	return 0;
}
