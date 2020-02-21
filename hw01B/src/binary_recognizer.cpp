#include "binary_recognizer.h"

#include <string>
#include <algorithm>

namespace lang { namespace recognizer {
	auto binary(const std::string& str) -> bool
	{
		return
			std::all_of(str.begin(), str.end(),
				[](char c)
				{
					return c == '0' || c == '1';
				}
			);
	}
} }
