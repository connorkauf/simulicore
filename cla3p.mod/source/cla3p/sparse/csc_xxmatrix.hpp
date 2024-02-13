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

#ifndef CLA3P_CSC_XXMATRIX_HPP_
#define CLA3P_CSC_XXMATRIX_HPP_

#include <ostream>
#include <string>

#include "cla3p/types.hpp"
#include "cla3p/generic/ownership.hpp"
#include "cla3p/generic/matrix_meta.hpp"
#include "cla3p/generic/guard.hpp"
//#include "cla3p/virtuals/virtual_object.hpp"

/*-------------------------------------------------*/

namespace cla3p { template <typename T_Int> class PxMatrix; }

/*-------------------------------------------------*/
namespace cla3p { 
namespace csc {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief The sparse matrix class (compressed sparse column format).
 */
template <typename T_Int, typename T_Scalar, typename T_Matrix>
class XxMatrix : public Ownership, public MatrixMeta {

	public:
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
		 * Constructs a (nr x nc) matrix with nz non-zero uninitialized values.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] nz The number of matrix non zeros.
		 * @param[in] pr The matrix property.
		 */
		explicit XxMatrix(uint_t nr, uint_t nc, uint_t nz, const Property& pr = defaultProperty());

		/**
		 * @brief The move constructor.
		 *
		 * Constructs a matrix with the contents of `other`, `other` is destroyed.
		 */
		XxMatrix(XxMatrix<T_Int,T_Scalar,T_Matrix>&& other);

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
		XxMatrix<T_Int,T_Scalar,T_Matrix>& operator=(XxMatrix<T_Int,T_Scalar,T_Matrix>&& other);

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

		/**
		 * @brief The matrix column pointer array.
		 * @return The array containing the number of non-zero elements in each column of `(*this)`.
		 */
		T_Int* colptr();

		/**
		 * @copydoc colptr()
		 */
		const T_Int* colptr() const;

		/**
		 * @brief The matrix row index array.
		 * @return The array containing the non-zero element row index in each column of `(*this)`.
		 */
		T_Int* rowidx();

		/**
		 * @copydoc rowidx()
		 */
		const T_Int* rowidx() const;

		/**
		 * @brief The matrix values array.
		 * @return The array containing the non-zero element values in each column of `(*this)`.
		 */
		T_Scalar* values();

		/**
		 * @copydoc values()
		 */
		const T_Scalar* values() const;

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
		 * @brief Prints matrix information.
		 * @param[in] msg Set a header identifier.
		 */
		std::string info(const std::string& msg = "") const;

		/**
		 * @brief Copies a matrix.
		 * @return A deep copy of `(*this)`.
		 *
		 * @see rcopy() const, rcopy(), move()
		 */
		T_Matrix copy() const;

		/**
		 * @brief Shallow-copies a matrix.
		 * @return A shallow copy of `(*this)`, `(*this)` is unchanged.
		 *
		 * @see copy(), rcopy() const, move()
		 */
		T_Matrix rcopy();

		/**
		 * @brief Shallow-copies an immutable matrix.
		 * @return A guard shallow copy of `(*this)`.
		 *
		 * @see copy(), rcopy(), move()
		 */
		Guard<T_Matrix> rcopy() const;

		/**
		 * @brief Moves a matrix.
		 * @return A shallow copy of `(*this)`, `(*this)` is destroyed.
		 *
		 * @see copy(), rcopy() const, rcopy()
		 */
		T_Matrix move();

		/**
		 * @brief Prints the contents of the object to a string.
		 * @param[in] nsd The number of significant digits.
		 * @return The string containing the formatted numerical values of the matrix.
		 */
		std::string toString(uint_t nsd = 3) const;

		/**
		 * @brief Transposes a matrix.
		 */
		T_Matrix transpose() const;

		/**
		 * @brief Conjugate-transposes a matrix.
		 */
		T_Matrix ctranspose() const;

		/**
		 * @brief Conjugates a matrix in-place.
		 */
		void iconjugate();

		/**
		 * @brief Conjugates a matrix.
		 */
		T_Matrix conjugate() const;

#if 0

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
		T_Matrix permuteLeftRight(const PxMatrix<int_t>& P, const PxMatrix<int_t>& Q) const;

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
		T_Matrix permuteLeft(const PxMatrix<int_t>& P) const;

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
		T_Matrix permuteRight(const PxMatrix<int_t>& Q) const;

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
		T_Matrix permuteMirror(const PxMatrix<int_t>& P) const;

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
		void ipermuteLeftRight(const PxMatrix<int_t>& P, const PxMatrix<int_t>& Q);

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
		void ipermuteLeft(const PxMatrix<int_t>& P);

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
		void ipermuteRight(const PxMatrix<int_t>& Q);

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
		void ipermuteMirror(const PxMatrix<int_t>& P);
#endif // 0

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
		 * @param[in] nz The number of matrix non zeros.
		 * @param[in] pr The matrix property.
		 * @return The newly created matrix.
		 */
		static T_Matrix init(uint_t nr, uint_t nc, uint_t nz, const Property& pr = defaultProperty());

		/**
		 * @brief Creates a matrix from aux data.
		 *
		 * Creates a (nr x nc) matrix from bulk data.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] cptr The array containing the matrix column pointers.
		 * @param[in] ridx The array containing the matrix row indexes.
		 * @param[in] vals The array containing the matrix values.
		 * @param[in] bind Binds the data to the matrix, the matrix will deallocate all arrays on destroy using i_free().
		 * @param[in] pr The matrix property.
		 * @return The newly created matrix.
		 */
		static T_Matrix wrap(uint_t nr, uint_t nc, T_Int *cptr, T_Int *ridx, T_Scalar *vals, bool bind, const Property& pr = defaultProperty());

		/**
		 * @brief Creates a matrix guard from aux data.
		 *
		 * Creates a (nr x nc) matrix from bulk data.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] cptr The array containing the matrix column pointers.
		 * @param[in] ridx The array containing the matrix row indexes.
		 * @param[in] vals The array containing the matrix values.
		 * @param[in] pr The matrix property.
		 * @return The newly created guard.
		 */
		static Guard<T_Matrix> wrap(uint_t nr, uint_t nc, const T_Int *cptr, const T_Int *ridx, const T_Scalar *vals, const Property& pr = defaultProperty());

		/** @} */

	private:
		T_Int*    m_colptr;
		T_Int*    m_rowidx;
		T_Scalar* m_values;

		void defaults();

		void setColptr(T_Int*);
		void setRowidx(T_Int*);
		void setValues(T_Scalar*);

		void copyTo(XxMatrix<T_Int,T_Scalar,T_Matrix>&) const;
		void shallowCopyTo(XxMatrix<T_Int,T_Scalar,T_Matrix>&);
		void moveTo(XxMatrix<T_Int,T_Scalar,T_Matrix>&);
		void wrapper(uint_t nr, uint_t nc, T_Int *cptr, T_Int *ridx, T_Scalar *vals, bool bind, const Property& pr);

	public:
		void updateSelfWithScaledOther(T_Scalar alpha, const XxMatrix<T_Int,T_Scalar,T_Matrix>& other);
		void createFromScaledSum(
				T_Scalar alpha, 
				const XxMatrix<T_Int,T_Scalar,T_Matrix>& otherA,
				const XxMatrix<T_Int,T_Scalar,T_Matrix>& otherB);
};

/*-------------------------------------------------*/
} // namespace csc
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup module_index_stream_operators
 * @brief Writes to os the contents of mat.
 */
template <typename T_Int, typename T_Scalar, typename T_Matrix>
std::ostream& operator<<(std::ostream& os, const cla3p::csc::XxMatrix<T_Int,T_Scalar,T_Matrix>& mat)
{
	os << mat.toString();
	return os;
}

#endif // CLA3P_CSC_XXMATRIX_HPP_
