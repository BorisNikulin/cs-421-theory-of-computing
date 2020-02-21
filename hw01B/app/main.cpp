#include "binary_recognizer.h"
#include "generator_util.hpp"

#include <iostream>
#include <iterator>

int main()
{
	using namespace std;
	using namespace lang;

	cout << recognizer::binary("0101012") <<"\n";

	const char alphabet[] = "ac";
	generator::util::StringsFromAlphabet<const char*> allStrings(begin(alphabet), end(alphabet));
	int stringLength;

	do
	{
		auto lenAndIterPair = *allStrings;

		stringLength = get<0>(lenAndIterPair);
		auto lengthedStringsStart = get<1>(lenAndIterPair);
		auto lengthedStringsEnd = get<2>(lenAndIterPair);

		for(; lengthedStringsStart != lengthedStringsEnd; ++lengthedStringsStart)
		{
			cout << *lengthedStringsStart << endl;
		}
		++allStrings;
	} while(stringLength < 3);

	return 0;
}
