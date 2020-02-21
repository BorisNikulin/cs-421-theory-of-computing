#pragma once

#include <string>

namespace lang { namespace recognizer {
	/**
	 * Recognizes strings of the form "[01]*".
	 */
	auto binary(const std::string& str) -> bool;
} }
