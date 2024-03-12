/*
 * Copyright 2023-2024 Connor C. Kaufman (connor.kaufman.gh@outlook.com)
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CLA3P_COO_XXMATRIX_HPP_
#define CLA3P_COO_XXMATRIX_HPP_

/**
 * @file
 */

#include <ostream>
#include <string>
#include <vector>

#include "cla3p/types.hpp"
#include "cla3p/generic/matrix_meta.hpp"
#include "cla3p/generic/tuple.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace coo {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief The sparse matrix class (coordinate format).
 */
template <typename T_Int, typename T_Scalar, typename T_Matrix>
class XxMatrix : public MatrixMeta {

	private:
		using T_CscMatrix = typename TypeTraits<T_Matrix>::csc_type;

	public:
		using index_type = T_Int;
		using value_type = T_Scalar;

	public:

		// no copy
		XxMatrix(const XxMatrix<T_Int,T_Scalar,T_Matrix>&) = delete;
		XxMatrix<T_Int,T_Scalar,T_Matrix>& operator=(const XxMatrix<T_Int,T_Scalar,T_Matrix>&) = delete;

		virtual const T_Matrix& self() const = 0;

		/** 
		 * @name Constructors
		 * @{
		 */

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty matrix.
		 */
		explicit XxMatrix();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Creates a (nr x nc) matrix with reserved space for nz values.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] nz The number of matrix non zeros (estimation).
		 * @param[in] pr The matrix property.
		 */
		explicit XxMatrix(uint_t nr, uint_t nc, uint_t nz, const Property& pr = defaultProperty());

		/**
		 * @brief The move constructor.
		 *
		 * Constructs a matrix with the contents of `other`, `other` is destroyed.
		 */
		XxMatrix(XxMatrix<T_Int,T_Scalar,T_Matrix>&& other) = default;

		/**
		 * @brief Destroys the matrix.
		 */
		~XxMatrix();

		/** @} */

		/** 
		 * @name Operators
		 * @{
		 */

		/**
		 * @brief The move assignment operator.
		 *
		 * Replaces the contents of `(*this)` with those of `other`, `other` is destroyed.
		 */
		XxMatrix<T_Int,T_Scalar,T_Matrix>& operator=(XxMatrix<T_Int,T_Scalar,T_Matrix>&& other) = default;

		/**
		 * @brief The csc copy assignment operator.
		 *
		 * Creates a csc-formatted copy of (*this) using the default settings.
		 *
		 * @see toCsc()
		 */
		operator T_CscMatrix() const;

		/** @} */

		/** 
		 * @name Arguments
		 * @{
		 */

		/**
		 * @brief The number of matrix non-zero elements.
		 * @return The number of non-zero elements in `(*this)`.
		 */
		uint_t nnz() const;

		/** @} */

		/** 
		 * @name Public Member Functions
		 * @{
		 */

		/**
		 * @brief Clears the object.
		 *
		 * Deallocates owned data and resets all members.
		 */
		void clear();

		/**
		 * @brief Reserve space for tuple insertion.
		 * @param[in] nz The number of elements to be reserved.
		 */
		void reserve(uint_t nz);

		/**
		 * @brief Inserts a tuple into the matrix.
		 *
		 * Inserts the element tuple.val() in position {tuple.row(), tuple.col()}
		 *
		 * @param[in] tuple The tuple to be inserted.
		 */
		void insert(const Tuple<T_Int,T_Scalar>& tuple);

		/**
		 * @brief Inserts a triplet into the matrix.
		 *
		 * Inserts the element v in position {i, j}
		 *
		 * @param[in] i The row index of the entry.
		 * @param[in] j The column index of the entry.
		 * @param[in] v The value of the entry.
		 */
		void insert(T_Int i, T_Int j, T_Scalar v);

		/**
		 * @brief Prints matrix information.
		 * @param[in] msg Set a header identifier.
		 */
		std::string info(const std::string& msg = "") const;

		/**
		 * @brief Prints the contents of the object to a string.
		 * @param[in] nsd The number of significant digits.
		 * @return The string containing the formatted numerical values of the matrix.
		 */
		std::string toString(uint_t nsd = 3) const;

		/**
		 * @brief Converts matrix to Compressed Sparse Column format.
		 * @param[in] duplicatePolicy Sets the policy for duplicated entries.
		 * @return The csc-formatted matrix.
		 */
		typename TypeTraits<T_Matrix>::csc_type toCsc(dup_t duplicatePolicy = dup_t::Sum) const;

		/** @} */

		/** 
		 * @name Creators/Generators
		 * @{
		 */

		/**
		 * @brief Creates a matrix.
		 *
		 * Creates a (nr x nc) matrix with reserved space for nz values.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] nz The number of matrix non zeros (estimation).
		 * @param[in] pr The matrix property.
		 * @return The newly created matrix.
		 */
		static T_Matrix init(uint_t nr, uint_t nc, uint_t nz, const Property& pr = defaultProperty());

		/** @} */

	private:

		using TupleVec = std::vector<Tuple<T_Int,T_Scalar>>;

		TupleVec m_tuples;

		TupleVec& tupleVec();
		const TupleVec& tupleVec() const;
};

/*-------------------------------------------------*/
} // namespace coo
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup module_index_stream_operators
 * @brief Writes to os the contents of mat.
 */
template <typename T_Int, typename T_Scalar, typename T_Matrix>
std::ostream& operator<<(std::ostream& os, const cla3p::coo::XxMatrix<T_Int,T_Scalar,T_Matrix>& mat)
{
	os << mat.toString();
	return os;
}

#endif // CLA3P_COO_XXMATRIX_HPP_
