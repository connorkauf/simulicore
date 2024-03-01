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

#ifndef CLA3P_DNS_XXMATRIX_HPP_
#define CLA3P_DNS_XXMATRIX_HPP_

#include <string>

#include "cla3p/dense/dns_xxobject.hpp"
#include "cla3p/generic/guard.hpp"
#include "cla3p/virtuals/virtual_object.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

namespace prm { template <typename T_Int> class PxMatrix; }

/*-------------------------------------------------*/
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief The dense matrix class.
 */
template <typename T_Scalar, typename T_Matrix>
class XxMatrix : public XxObject<T_Scalar,T_Matrix> {

	private:
		using T_RScalar = typename TypeTraits<T_Scalar>::real_type;
		using T_Vector = typename TypeTraits<T_Matrix>::vector_type;

	public:

		// no copy
		XxMatrix(const XxMatrix<T_Scalar,T_Matrix>&) = delete;
		XxMatrix<T_Scalar,T_Matrix>& operator=(const XxMatrix<T_Scalar,T_Matrix>&) = delete;

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
		 * Constructs a general (nr x nc) matrix with uninitialized values.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] pr The matrix property.
		 */
		explicit XxMatrix(uint_t nr, uint_t nc, const Property& pr = defaultProperty());

		/**
		 * @brief The move constructor.
		 *
		 * Constructs a matrix with the contents of `other`, `other` is destroyed.
		 */
		XxMatrix(XxMatrix<T_Scalar,T_Matrix>&& other) = default;

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
		XxMatrix<T_Scalar,T_Matrix>& operator=(XxMatrix<T_Scalar,T_Matrix>&& other) = default;

		/**
		 * @brief Matrix entry operator.
		 * @param[in] i The row index of the requested entry.
		 * @param[in] j The column index of the requested entry.
		 * @return A reference to the (i,j)-th element of `(*this)`.
		 */
		T_Scalar& operator()(uint_t i, uint_t j);

		/**
		 * @copydoc cla3p::dns::XxMatrix::operator()(uint_t i, uint_t j)
		 */
		const T_Scalar& operator()(uint_t i, uint_t j) const;

		/**
		 * @brief The value setter operator.
		 *
		 * Sets all entries of `(*this)` to a single value.@n
		 * Imaginary part of diagonal is set to zero for Hermitian cases.@n
		 * Diagonal is set to zero for Skew cases.
		 *
		 * @param[in] val The value to be set.
		 */
		void operator=(T_Scalar val);

		/** @} */

		/** 
		 * @name Arguments
		 * @{
		 */

		/**
		 * @brief The matrix rows.
		 * @return The number of rows in `(*this)`.
		 */
		uint_t nrows() const;

		/**
		 * @brief The matrix columns.
		 * @return The number of columns in `(*this)`.
		 */
		uint_t ncols() const;

		/**
		 * @brief The matrix leading dimension.
		 * @return The leading dimension of `(*this)` (column-major: ld() @f$ \geq @f$ nrows()).
		 */
		uint_t ld() const;

		/**
		 * @brief The matrix property.
		 * @return The property that characterizes `(*this)`.
		 */
		const Property& prop() const;

		/** @} */

		/** 
		 * @name Public Member Functions
		 * @{
		 */

		/**
		 * @brief Prints matrix information.
		 * @param[in] msg Set a header identifier.
		 */
		std::string info(const std::string& msg = "") const;

		/**
		 * @brief Virtually transposes a matrix.
		 */
		VirtualMatrix<T_Matrix> transpose() const;

		/**
		 * @brief Virtually conjugate-transposes a matrix.
		 */
		VirtualMatrix<T_Matrix> ctranspose() const;

		/**
		 * @brief Virtually conjugates a matrix.
		 */
		VirtualMatrix<T_Matrix> conjugate() const;

		/**
		 * @brief Converts a matrix to general.
		 * @return A copy of `(*this)` with general property.
		 */
		T_Matrix general() const;

		/**
		 * @brief Converts `(*this)` to general in-place.
		 */
		void igeneral();

		/**
		 * @brief Permutes a general matrix.
		 *
		 * Creates a permuted copy `P*(*this)*Q` of `(*this)`.
		 *
		 * @param[in] P The left side permutation matrix.
		 * @param[in] Q The right side permutation matrix.
		 * @return The matrix `P*(*this)*Q`.
		 *
		 * @see permuteLeft(), permuteRight(), permuteMirror()
		 * @see ipermuteLeftRight(), ipermuteLeft(), ipermuteRight(), ipermuteMirror()
		 */
		T_Matrix permuteLeftRight(const prm::PxMatrix<int_t>& P, const prm::PxMatrix<int_t>& Q) const;

		/**
		 * @brief Permutes the rows of a general matrix.
		 *
		 * Creates a permuted copy `P*(*this)` of `(*this)`.
		 *
		 * @param[in] P The left side permutation matrix.
		 * @return The matrix `P*(*this)`.
		 *
		 * @see permuteLeftRight(), permuteRight(), permuteMirror()
		 * @see ipermuteLeftRight(), ipermuteLeft(), ipermuteRight(), ipermuteMirror()
		 */
		T_Matrix permuteLeft(const prm::PxMatrix<int_t>& P) const;

		/**
		 * @brief Permutes the columns of a general matrix.
		 *
		 * Creates a permuted copy `(*this)*Q` of `(*this)`.
		 *
		 * @param[in] Q The right side permutation matrix.
		 * @return The matrix `(*this)*Q`.
		 *
		 * @see permuteLeftRight(), permuteLeft(), permuteMirror()
		 * @see ipermuteLeftRight(), ipermuteLeft(), ipermuteRight(), ipermuteMirror()
		 */
		T_Matrix permuteRight(const prm::PxMatrix<int_t>& Q) const;

		/**
		 * @brief Permutes a matrix symmetrically.
		 *
		 * Creates a permuted copy `P*(*this)*P^T` of `(*this)`.
		 *
		 * @param[in] P The left and right side permutation matrix.
		 * @return The matrix `P*(*this)*P^T`.
		 *
		 * @see permuteLeftRight(), permuteLeft(), permuteRight()
		 * @see ipermuteLeftRight(), ipermuteLeft(), ipermuteRight(), ipermuteMirror()
		 */
		T_Matrix permuteMirror(const prm::PxMatrix<int_t>& P) const;

		/**
		 * @brief Permutes a general matrix in-place.
		 *
		 * Replaces `(*this)` with `P*(*this)*Q`.
		 *
		 * @param[in] P The left side permutation matrix.
		 * @param[in] Q The right side permutation matrix.
		 *
		 * @see permuteLeftRight(), permuteLeft(), permuteRight(), permuteMirror()
		 * @see ipermuteLeft(), ipermuteRight(), ipermuteMirror()
		 */
		void ipermuteLeftRight(const prm::PxMatrix<int_t>& P, const prm::PxMatrix<int_t>& Q);

		/**
		 * @brief Permutes the rows of a general matrix in-place.
		 *
		 * Replaces `(*this)` with `P*(*this)`.
		 *
		 * @param[in] P The left side permutation matrix.
		 *
		 * @see permuteLeftRight(), permuteLeft(), permuteRight(), permuteMirror()
		 * @see ipermuteLeftRight(), ipermuteRight(), ipermuteMirror()
		 */
		void ipermuteLeft(const prm::PxMatrix<int_t>& P);

		/**
		 * @brief Permutes the columns of a general matrix in-place.
		 *
		 * Replaces `(*this)` with `(*this)*Q`.
		 *
		 * @param[in] Q The right side permutation matrix.
		 *
		 * @see permuteLeftRight(), permuteLeft(), permuteRight(), permuteMirror()
		 * @see ipermuteLeftRight(), ipermuteLeft(), ipermuteMirror()
		 */
		void ipermuteRight(const prm::PxMatrix<int_t>& Q);

		/**
		 * @brief Permutes a matrix symmetrically in-place.
		 *
		 * Replaces `(*this)` with `P*(*this)*P^T`.
		 *
		 * @param[in] P The left and right side permutation matrix.
		 *
		 * @see permuteLeftRight(), permuteLeft(), permuteRight(), permuteMirror()
		 * @see ipermuteLeftRight(), ipermuteLeft(), ipermuteRight()
		 */
		void ipermuteMirror(const prm::PxMatrix<int_t>& P);

		/**
		 * @brief Gets a submatrix with content copy.
		 *
		 * Gets a copy of a (ni x nj) block of `(*this)`, starting at (ibgn, jbgn).
		 *
		 * @param[in] ibgn The row index that the requested part begins.
		 * @param[in] jbgn The column index that the requested part begins.
		 * @param[in] ni The number of rows of the requested block.
		 * @param[in] nj The number of columns of the requested block.
		 * @return A matrix with content copy of `(*this)[ibgn:ibgn+ni,jbgn:jbgn+nj]`.
     *
     * @see rblock(), setBlock()
		 */
		T_Matrix block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @brief Gets a submatrix with content reference.
		 *
		 * Gets a (ni x nj) matrix that references contents of `(*this)`, starting at (ibgn, jbgn).
		 *
		 * @param[in] ibgn The row index that the requested part begins.
		 * @param[in] jbgn The column index that the requested part begins.
		 * @param[in] ni The number of rows of the requested block.
		 * @param[in] nj The number of columns of the requested block.
		 * @return A matrix with content reference to `(*this)[ibgn:ibgn+ni,jbgn:jbgn+nj]`.
     *
     * @see block(), setBlock()
		 */
		T_Matrix rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

		/**
		 * @brief Gets a guarded submatrix with content reference.
		 *
		 * Gets a (ni x nj) guarded matrix that references contents of `(*this)`, starting at (ibgn, jbgn).
		 *
		 * @param[in] ibgn The row index  that the requested part begins.
		 * @param[in] jbgn The column index that the requested part begins.
		 * @param[in] ni The number of rows of the requested block.
		 * @param[in] nj The number of columns of the requested block.
		 * @return A guarded matrix with content reference to `(*this)[ibgn:ibgn+ni,jbgn:jbgn+nj]`.
		 *
     * @see block(), rblock(), setBlock()
		 */
		Guard<T_Matrix> rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @brief Sets a submatrix.
		 *
		 * Copies the contents of `src` to `(*this)[ibgn:ibgn+src.nrows(),jbgn:jbgn+src.ncols()]`.
		 *
		 * @param[in] ibgn The row index that src will be placed.
		 * @param[in] jbgn The column index that src will be placed.
		 * @param[in] src The matrix to be placed.
		 *
     * @see block(), rblock()
		 */
		void setBlock(uint_t ibgn, uint_t jbgn, const XxMatrix<T_Scalar,T_Matrix>& src);

		/**
		 * @brief Gets a matrix column with content copy.
		 *
		 * Gets a copy of the j-th column of the matrix.
		 *
		 * @param[in] j The column index requested.
		 * @return A vector with content copy of `(*this)[0:nrows(),j:j+1]`.
		 *
     * @see rcolumn()
		 */
		T_Vector column(uint_t j) const;

		/**
		 * @brief Gets a matrix column with content reference.
		 *
		 * Gets a vector that references contents of `(*this)` at column j.
		 *
		 * @param[in] j The column index requested.
		 * @return A vector with content reference to `(*this)[0:nrows(),j:j+1]`.
		 *
     * @see column()
		 */
		T_Vector rcolumn(uint_t j);

		/**
		 * @brief Gets a matrix column with content reference.
		 *
		 * Gets guarded a vector that references contents of `(*this)` at column j.
		 *
		 * @param[in] j The column index requested.
		 * @return A guarded vector with content reference to `(*this)[0:nrows(),j:j+1]`.
		 *
     * @see column()
		 */
		Guard<T_Vector> rcolumn(uint_t j) const;

		/** @} */

		/** 
		 * @name Creators/Generators
		 * @{
		 */

		/**
		 * @brief Creates a matrix.
		 *
		 * Creates a (nr x nc) matrix with uninitialized values.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] pr The matrix property.
		 * @return The newly created matrix.
		 */
		static T_Matrix init(uint_t nr, uint_t nc, const Property& pr = defaultProperty());

		/**
		 * @brief Creates a matrix with random values in (lo,hi).
		 *
		 * Creates a (nr x nc) matrix with random values.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] pr The matrix property.
		 * @param[in] lo The smallest value of each generated element.
		 * @param[in] hi The largest value of each generated element.
		 * @return The newly created matrix.
		 */
		static T_Matrix random(uint_t nr, uint_t nc, const Property& pr = defaultProperty(), 
				T_RScalar lo = T_RScalar(0), T_RScalar hi = T_RScalar(1));

		/**
		 * @brief Creates a matrix from aux data.
		 *
		 * Creates a (nr x nc) matrix from bulk data.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] vals The array containing the matrix values in column-major ordering.
		 * @param[in] ldv The leading dimension of the vals array.
		 * @param[in] bind Binds the data to the matrix, the matrix will deallocate vals on destroy using i_free().
		 * @param[in] pr The matrix property.
		 * @return The newly created matrix.
		 */
		static T_Matrix wrap(uint_t nr, uint_t nc, T_Scalar *vals, uint_t ldv, bool bind, const Property& pr = defaultProperty());

		/**
		 * @brief Creates a matrix guard from aux data.
		 *
		 * Creates a (nr x nc) matrix from bulk data.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] vals The array containing the matrix values in column-major ordering.
		 * @param[in] ldv The leading dimension of the vals array.
		 * @param[in] pr The matrix property.
		 * @return The newly created guard.
		 */
		static Guard<T_Matrix> wrap(uint_t nr, uint_t nc, const T_Scalar *vals, uint_t ldv, const Property& pr = defaultProperty());

		/** @} */

};

/*-------------------------------------------------*/
} // namespace dns
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_XXMATRIX_HPP_
