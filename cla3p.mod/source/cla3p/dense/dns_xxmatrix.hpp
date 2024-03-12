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

/**
 * @file
 */

#include <string>

#include "cla3p/generic/matrix_meta.hpp"
#include "cla3p/generic/guard.hpp"
#include "cla3p/dense/dns_xxobject.hpp"
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
class XxMatrix : public MatrixMeta, public XxObject<T_Scalar> {

	private:
		using T_RScalar = typename TypeTraits<T_Scalar>::real_type;
		using T_Vector = typename TypeTraits<T_Matrix>::vector_type;

	public:

		explicit XxMatrix();
		explicit XxMatrix(uint_t nr, uint_t nc, const Property& pr);
		~XxMatrix();

		virtual const T_Matrix& self() const = 0;

		XxMatrix(XxMatrix<T_Scalar,T_Matrix>&&);
		XxMatrix<T_Scalar,T_Matrix>& operator=(XxMatrix<T_Scalar,T_Matrix>&&);

		/**
		 * @name Operators
		 * @{
		 */

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
		 * @brief Unary minus operator.
		 *
		 * Negates the matrix.
		 *
		 * @return The result of the operation `-(*this)`.
		 */
		T_Matrix operator-() const;

		/** @} */

		/** 
		 * @name Arguments
		 * @{
		 */

		/**
		 * @brief The matrix leading dimension.
		 * @return The leading dimension of `(*this)` (column-major: ld() @f$ \geq @f$ nrows()).
		 */
		uint_t ld() const;

		/** @} */

		/**
		 * @name Public Member Functions
		 * @{
		 */

		/**
		 * @brief Clears the matrix.
		 *
		 * Deallocates owned data and resets all members.
		 */
		void clear();

		/**
		 * @brief Fills the matrix with a value.
		 *
		 * Sets all entries of the matrix to a single value.@n
		 * Imaginary part of diagonal is set to zero for Hermitian cases.@n
		 * Diagonal is set to zero for Skew cases.
		 *
		 * @param[in] val The value to be set.
		 */
		void fill(T_Scalar val);

		/**
		 * @brief Copies a matrix.
		 * @return A deep copy of `(*this)`.
		 */
		T_Matrix copy() const;

		/**
		 * @brief Shallow-copies a matrix.
		 * @return A shallow copy of `(*this)`, `(*this)` is unchanged.
		 */
		T_Matrix rcopy();

		/**
		 * @brief Shallow-copies an immutable matrix.
		 * @return A guard shallow copy of `(*this)`.
		 */
		Guard<T_Matrix> rcopy() const;

		/**
		 * @brief Moves a matrix.
		 * @return A shallow copy of `(*this)`, `(*this)` is destroyed.
		 */
		T_Matrix move();

		/**
		 * @brief Prints matrix information.
		 * @param[in] header Set a header identifier.
		 */
		std::string info(const std::string& header = "") const;

		/**
		 * @brief Prints the contents of the matrix.
		 * @param[in] nsd The number of significant digits (for real/complex types only, otherwise ignored).
		 */
		void print(uint_t nsd = 3) const;

		/**
		 * @brief Prints the contents of the matrix to a string.
		 * @param[in] nsd The number of significant digits (for real/complex types only, otherwise ignored).
		 * @return The string containing the formatted numerical values of the matrix.
		 */
		std::string toString(uint_t nsd = 3) const;

		/**
		 * @brief Multiplies the matrix by a scalar.
		 * @param[in] val The scaling coefficient.
		 */
		void iscale(T_Scalar val);

		/**
		 * @brief Virtually transposes a matrix.
		 * @return A virtual matrix object that represents the transposed matrix.
		 */
		VirtualMatrix<T_Matrix> transpose() const;

		/**
		 * @brief Virtually conjugate-transposes a matrix.
		 * @return A virtual matrix object that represents the conjugate-transposed matrix.
		 */
		VirtualMatrix<T_Matrix> ctranspose() const;

		/**
		 * @brief Virtually conjugates a matrix.
		 * @return A virtual matrix object that represents the conjugated matrix.
		 */
		VirtualMatrix<T_Matrix> conjugate() const;

		/**
		 * @brief Conjugates the matrix in-place.
		 *
		 * Negates the imaginary part of the elements of the matrix.
		 */
		void iconjugate();

		/**
		 * @brief The 1-norm.
		 * @return The 1-norm of `(*this)`.
		 */
		T_RScalar normOne() const;

		/**
		 * @brief The infinite norm.
		 * @return The infinite norm of `(*this)`.
		 */
		T_RScalar normInf() const;

		/**
		 * @brief The maximum norm.
		 * @return The maximum norm of `(*this)`.
		 */
		T_RScalar normMax() const;

		/**
		 * @brief The Frobenius norm.
		 * @return The Frobenius norm of `(*this)`.
		 */
		T_RScalar normFro() const;

		/**
		 * @brief Converts a matrix to general.
		 * @return A copy of `(*this)` with general property.
		 */
		T_Matrix general() const;

		/**
		 * @brief Converts `(*this)` to general in-place.
		 *
		 * Converts matrix by filling missing entries and changing its property.
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
		 */
		T_Matrix permuteLeftRight(const prm::PxMatrix<int_t>& P, const prm::PxMatrix<int_t>& Q) const;

		/**
		 * @brief Permutes the rows of a general matrix.
		 *
		 * Creates a permuted copy `P*(*this)` of `(*this)`.
		 *
		 * @param[in] P The left side permutation matrix.
		 * @return The matrix `P*(*this)`.
		 */
		T_Matrix permuteLeft(const prm::PxMatrix<int_t>& P) const;

		/**
		 * @brief Permutes the columns of a general matrix.
		 *
		 * Creates a permuted copy `(*this)*Q` of `(*this)`.
		 *
		 * @param[in] Q The right side permutation matrix.
		 * @return The matrix `(*this)*Q`.
		 */
		T_Matrix permuteRight(const prm::PxMatrix<int_t>& Q) const;

		/**
		 * @brief Permutes a matrix symmetrically.
		 *
		 * Creates a permuted copy `P*(*this)*P^T` of `(*this)`.
		 *
		 * @param[in] P The left and right side permutation matrix.
		 * @return The matrix `P*(*this)*P^T`.
		 */
		T_Matrix permuteMirror(const prm::PxMatrix<int_t>& P) const;

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
		 */
		T_Matrix rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

		/**
		 * @brief Gets a guarded submatrix with content reference.
		 *
		 * Gets a (ni x nj) guarded matrix that references contents of `(*this)`, starting at (ibgn, jbgn).
		 *
		 * @param[in] ibgn The row index that the requested part begins.
		 * @param[in] jbgn The column index that the requested part begins.
		 * @param[in] ni The number of rows of the requested block.
		 * @param[in] nj The number of columns of the requested block.
		 * @return A guarded matrix with content reference to `(*this)[ibgn:ibgn+ni,jbgn:jbgn+nj]`.
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
		 */
		void setBlock(uint_t ibgn, uint_t jbgn, const XxMatrix<T_Scalar,T_Matrix>& src);

		/**
		 * @brief Gets a matrix column with content copy.
		 *
		 * Gets a copy of the j-th column of the matrix.
		 *
		 * @param[in] j The column index requested.
		 * @return A vector with content copy of `(*this)[0:nrows(),j:j+1]`.
		 */
		T_Vector column(uint_t j) const;

		/**
		 * @brief Gets a matrix column with content reference.
		 *
		 * Gets a vector that references contents of `(*this)` at column j.
		 *
		 * @param[in] j The column index requested.
		 * @return A vector with content reference to `(*this)[0:nrows(),j:j+1]`.
		 */
		T_Vector rcolumn(uint_t j);

		/**
		 * @brief Gets a matrix column with content reference.
		 *
		 * Gets guarded a vector that references contents of `(*this)` at column j.
		 *
		 * @param[in] j The column index requested.
		 * @return A guarded vector with content reference to `(*this)[0:nrows(),j:j+1]`.
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

	private:

		uint_t m_ld;

		void defaults();

		void setLd(uint_t ld);

		void moveTo(XxMatrix<T_Scalar,T_Matrix>&);
		void wrapper(uint_t nr, uint_t nc, T_Scalar *vals, uint_t ldv, bool bind, const Property& pr);
};

/*-------------------------------------------------*/
} // namespace dns
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup module_index_stream_operators
 * @brief Writes to os the contents of mat.
 */
template <typename T_Matrix>
std::ostream& operator<<(std::ostream& os, const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& mat)
{
	os << mat.toString();
	return os;
}

#endif // CLA3P_DNS_XXMATRIX_HPP_
