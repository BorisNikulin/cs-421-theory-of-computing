#pragma once

#include <cstddef>

namespace sjp { namespace tmp {
	/** TMP class for multiplying a variadic template list of std::size_t.
	 *
	 *  FoldMult::value contains the result.
	 *  If there are no arguments the result is 1.
	 */
	// base case
	// when fold expressions are c++17 you roll your own
	template<std::size_t... Nums>
	struct FoldMult
	{
		/// Value of mulitplying the given template parameters or 1 if none.
		const static std::size_t value = 1;
	};

	// do not generate docs for template specialization helper
	/// \cond
	/** See FoldMult.
	 *
	 *  This is the recursive case.
	 */
	template<std::size_t Num, std::size_t... Nums>
	struct FoldMult<Num, Nums...>
	{
		const static std::size_t value = Num * FoldMult<Nums...>::value;
	};
	/// \endcond

} }
