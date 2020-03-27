#pragma once

#include "tmp.hpp"

#include <array>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace sjp { namespace vector {
	/** Indexes a flat sequence as if multidimensional.
	 *
	 *  Providing an index for all dimensions
	 *  gives an equivalent index for a 1 dimensional sequence.
	 *
	 *  \tparam Dims list of dimmensions from outer to inner
	 *  	with at least one dimension
	 */
	template<std::size_t... Dims>
	struct Shape
	{
		/** Number of in bounds indexes.
		 *
		 *  In other words, the raw number of elements
		 *  an underlying 1 dimensional sequence would need
		 *  to support being indexed with such a Shape.
		 */
		const static std::size_t size;

		/** Index into the dimensions returning an index.
		 *
		 *  Not bounds checked.
		 *
		 *  \param indexes indexes into dimensions in the same order as Dims
		 */
		std::size_t operator()(decltype(Dims)... indexes);


		/** Index into the dimensions returning an index.
		 *
		 *  Is bounds checked.
		 *
		 *  \param indexes indexes into dimensions in the same order as Dims
		 */
		std::size_t at(decltype(Dims)... indexes);
	};

	// do not generate documentation for template specializations
	/// \cond
	/** Base case of Shape where indexing operations return the index.
	 *
	 *  \tparam SingleDim the single dimension of this Shape
	 */
	template<std::size_t SingleDim>
	struct Shape<SingleDim>
	{
		const static std::size_t size = SingleDim;

		std::size_t operator()(std::size_t index)
		{
			return index;
		}

		std::size_t at(std::size_t index)
		{
			if(index < 0 || index >= SingleDim)
			{
				throw std::out_of_range("shape index out of range");
			}
			return operator()(index);
		}
	};

	/** Recursive case of Shape where indexing operations return a lower dimensional Shape.
	 *
	 *  \tparam OuterDim outer dimension that is also used for bounds checking
	 *  \tparam InnerDim inner dimension
	 *  \tparam Rest the rest of the dimensions
	 */
	template<std::size_t OuterDim, std::size_t InnerDim, std::size_t... RestDims>
	struct Shape<OuterDim, InnerDim, RestDims...>
	{
		const static std::size_t size = sjp::tmp::FoldMult<OuterDim, InnerDim, RestDims...>::value;

		template<typename... IndexTypes, typename = typename std::enable_if<sizeof...(IndexTypes) == sizeof...(RestDims)>::type>
		std::size_t operator()(std::size_t outerIndex, std::size_t innerIndex, IndexTypes... indexes)
		{
			return outerIndex * sjp::tmp::FoldMult<InnerDim, RestDims...>::value
				+ Shape<InnerDim, RestDims...>()(innerIndex, indexes...);
		}

		template<typename... IndexTypes, typename = typename std::enable_if<sizeof...(IndexTypes) == sizeof...(RestDims)>::type>
		std::size_t at(std::size_t outerIndex, std::size_t innerIndex, IndexTypes... indexes)
		{
			std::size_t index = operator()(outerIndex, innerIndex, indexes...);
			std::size_t rawSize = sjp::tmp::FoldMult<OuterDim, InnerDim, RestDims...>::value;
			if(index < 0 || index >= rawSize)
			{
				throw std::out_of_range("shape index out of range");
			}
			return index;
		}
	};
	/// \endcond

	/** Wrapper around std::array whose indexing operations are multidimensional.
	 *
	 *  Indexing is done accoding to provided dimensions which induces a Shape.
	 *
	 *  \tparam Dims list of dimmensions from outer to inner
	 *  	with at least one dimension
	 */
	template<typename T, std::size_t... Dims>
	class ShapedArray
	{
		public:
			using ArrayType = std::array<T, Shape<Dims...>::size>;
			Shape<Dims...> shape;

		private:
			ArrayType array;

		public:
			//template<typename... ArrayArgTypes>
			//ShapedArray(ArrayArgTypes&&... arrayArgs) : array(std::forward<ArrayArgTypes>(arrayArgs)...)
			//{}

			ShapedArray(ArrayType array = {}) : array(array)
			{}


			/** Shaped bound checked access to array.
			 *
			 *  \see Shape.at()
			 *
			 *  \returns reference to indexed element
			 */
			template<typename... IndexTypes>
			typename ArrayType::reference at(IndexTypes... indexes)
			{
				return array[shape.at(indexes...)];
			}

			/** Shaped non-bound checked access to array.
			 *
			 *  \see Shape.operator()()
			 *
			 *  \returns reference to indexed element
			 */
			template<typename... IndexTypes>
			typename ArrayType::reference operator()(IndexTypes... indexes)
			{
				return array[shape(indexes...)];
			}

			/** Direct access to underlying array
			 *
			 *  \returns reference to backing 1 dimensional array
			 */
			template<typename... IndexTypes>
			ArrayType& data(IndexTypes... indexes)
			{
				return array;
			}

			/** Returns the number of elements
			 */
			const std::size_t size()
			{
				return shape.size;
			}
	};
} }
