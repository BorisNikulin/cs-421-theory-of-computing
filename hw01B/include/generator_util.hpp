#pragma once

#include <string>
#include <tuple>
#include <iterator>
#include <cmath>

namespace lang { namespace generator { namespace util {
	/**
	 * Forward iterator class that using a given alphabet
	 * generates iterators that enumerate all possible strings of a certain length.
	 *
	 * AlphaIter is recomended to be a random access iterator for faster acess of symbols.
	 */
	template<typename AlphaIter>
	class StringsFromAlphabet
	{
		public:
			class StringsFromAlphabetForLength;

			using value_type =
				std::tuple<
					int,
					StringsFromAlphabetForLength,
					StringsFromAlphabetForLength
				>;
			using difference_type = void;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::forward_iterator_tag;

			/**
			 * Forward iterator that generates all strings
			 * of a certain length from a given length and alphabet.
			 */
			class StringsFromAlphabetForLength
			{
				public:
					using value_type = std::string;
					using difference_type = void;
					using pointer = value_type*;
					using reference = value_type&;
					using iterator_category = std::forward_iterator_tag;

				private:
					const AlphaIter alphaBegin;
					const int alphaLen;
					const int strLen;
					int strId;

				public:
					StringsFromAlphabetForLength(const AlphaIter begin, int alphaLength, int stringLength, int strId = 0)
						: alphaBegin(begin), alphaLen(alphaLength), strLen(stringLength), strId(strId)
					{}

					/**
					 * Increment the iterator to generate the next string.
					 */
					auto operator++() -> StringsFromAlphabetForLength&;
					/**
					 * Use the current state of the iterator to generate a string
					 * based on thee given alhpabet and length.
					 */
					auto operator*() -> value_type;

					auto operator!=(const StringsFromAlphabetForLength& other) -> bool
					{ return strId != other.strId; }
			};

		private:
			const AlphaIter alphaIterBegin;
			//const AlphaIter alphaIterEnd;
			const int alphaLength;

			int strLen;

			auto endLengthedIter() -> StringsFromAlphabetForLength
			{ return StringsFromAlphabetForLength(alphaIterBegin, alphaLength, strLen,  std::pow(alphaLength, strLen)); }


		public:
			StringsFromAlphabet(const AlphaIter begin, const AlphaIter end, int startStringLength = 0)
				: alphaIterBegin(begin),
					//alphaIterEnd(end),
					alphaLength(std::distance(begin, end) - 1),
					strLen(startStringLength)
			{}

			/**
			 * Increments the length of strings
			 * this iterator will provide iterator for.
			 */
			auto operator++() -> StringsFromAlphabet&;

			/**
			 * Aquires the length of strings
			 * and two iterators that generate
			 * all srings of the set length.
			 *
			 * The iterators represeent a range
			 * and are used as standard forward iterators.
			 */
			auto operator*() -> value_type;
	};

	template<typename AlphaIter>
	auto StringsFromAlphabet<AlphaIter>::operator++() -> StringsFromAlphabet&
	{
		++strLen;
		return *this;
	}

	template<typename AlphaIter>
	auto StringsFromAlphabet<AlphaIter>::operator*() -> value_type
	{
		return std::make_tuple(
			strLen,
			StringsFromAlphabetForLength(alphaIterBegin, alphaLength, strLen),
			endLengthedIter()
		);
	}

	template<typename AlphaIter>
	auto StringsFromAlphabet<AlphaIter>::StringsFromAlphabetForLength::operator++()
	-> StringsFromAlphabetForLength&
	{
		++strId;
		return *this;
	}

	template<typename AlphaIter>
	auto StringsFromAlphabet<AlphaIter>::StringsFromAlphabetForLength::operator*()
	-> value_type
	{
		int strIdCopy = strId;

		std::string str;
		str.reserve(strLen);

		for(int i = 0; i < strLen; ++i)
		{
			auto alphaIter = alphaBegin;
			std::advance(alphaIter, strId % alphaLen);
			str.push_back(*alphaIter);
			strId /= alphaLen;
		}

		strId = strIdCopy;
		return str;
	}
} } }
