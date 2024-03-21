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

#ifndef CLA3P_DNS_XXVECTOR_HPP_
#define CLA3P_DNS_XXVECTOR_HPP_

/**
 * @file
 */

#include <string>
#include <ostream>

#include "cla3p/generic/meta1d.hpp"
#include "cla3p/generic/guard.hpp"
#include "cla3p/dense/dns_xxobject.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

namespace prm { template <typename T_Int> class PxMatrix; }

template <typename T_Vector> class VirtualVector;
template <typename T_Vector> class VirtualProdMv;

/*-------------------------------------------------*/
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief The general purpose dense vector class.
 */
template <typename T_Scalar, typename T_Vector>
class XiVector : public Meta1D, public XxObject<T_Scalar> {

	public:

		explicit XiVector();
		explicit XiVector(uint_t n);
		~XiVector();

		XiVector(XiVector<T_Scalar,T_Vector>&&);
		XiVector<T_Scalar,T_Vector>& operator=(XiVector<T_Scalar,T_Vector>&&);

		/** 
		 * @name Operators
		 * @{
		 */

		/**
		 * @brief Vector entry operator.
		 * @param[in] i The index of the requested entry.
		 * @return A reference to the i-th element of `(*this)`.
		 */
		T_Scalar& operator()(uint_t i);

		/**
		 * @copydoc cla3p::dns::XiVector::operator()(uint_t i)
		 */
		const T_Scalar& operator()(uint_t i) const;

		/** @} */

		/** 
		 * @name Public Member Functions
		 * @{
		 */

		/**
		 * @brief Clears the vector.
		 *
		 * Deallocates owned data and resets all members.
		 */
		void clear();

		/**
		 * @brief Fills the vector with a value.
		 *
		 * Sets all entries of the vector to a single value.
		 *
		 * @param[in] val The value to be set.
		 */
		void fill(T_Scalar val);

		/**
		 * @brief Copies a vector.
		 * @return A deep copy of `(*this)`.
		 */
		T_Vector copy() const;

		/**
		 * @brief Shallow-copies a vector.
		 * @return A shallow copy of `(*this)`, `(*this)` is unchanged.
		 */
		T_Vector rcopy();

		/**
		 * @brief Shallow-copies an immutable vector.
		 * @return A guarded shallow copy of `(*this)`.
		 */
		Guard<T_Vector> rcopy() const;

		/**
		 * @brief Moves a vector.
		 * @return A shallow copy of `(*this)`, `(*this)` is destroyed.
		 */
		T_Vector move();

		/**
		 * @brief Prints vector information.
		 * @param[in] header Set a header identifier.
		 */
		std::string info(const std::string& header = "") const;

		/**
		 * @brief Prints the contents of the vector.
		 * @param[in] nsd The number of significant digits (for real/complex types only, otherwise ignored).
		 */
		void print(uint_t nsd = 3) const;

		/**
		 * @brief Prints the contents of the vector to a string.
		 * @param[in] nsd The number of significant digits (for real/complex types only, otherwise ignored).
		 * @return The string containing the formatted numerical values of the vector.
		 */
		std::string toString(uint_t nsd = 3) const;

		/** @} */

		/** 
		 * @name Creators/Generators
		 * @{
		 */

		/**
		 * @brief Creates a vector.
		 *
		 * Creates a n-sized vector with uninitialized values.
		 *
		 * @param[in] n The vector size.
		 * @return The newly created vector.
		 */
		static T_Vector init(uint_t n);

		/**
		 * @brief Creates a vector from aux data.
		 *
		 * Creates a n-sized vector from bulk data.
		 *
		 * @param[in] n The vector size.
		 * @param[in] vals The array containing the vector values.
		 * @param[in] bind Binds the data to the vector, the vector will deallocate vals on destroy using i_free().
		 * @return The newly created vector.
		 */
		static T_Vector wrap(uint_t n, T_Scalar *vals, bool bind);

		/**
		 * @brief Creates a guard from aux data.
		 *
		 * Creates a n-sized guarded vector from bulk data.
		 *
		 * @param[in] n The vector size.
		 * @param[in] vals The array containing the vector values.
		 * @return The newly created guard.
		 */
		static Guard<T_Vector> wrap(uint_t n, const T_Scalar *vals);

		/** @} */

	private:

		void moveTo(XiVector<T_Scalar,T_Vector>&);
		void wrapper(uint_t n, T_Scalar *vals, bool bind);
};

/**
 * @nosubgrouping 
 * @brief The floating point dense vector class.
 */
template <typename T_Scalar, typename T_Vector>
class XxVector : public XiVector<T_Scalar,T_Vector> {

	private:
		using T_RScalar = typename TypeTraits<T_Scalar>::real_type;
		using T_Matrix = typename TypeTraits<T_Vector>::matrix_type;

	public:

		explicit XxVector();
		explicit XxVector(uint_t n);
		~XxVector();

		virtual const T_Vector& self() const = 0;
		virtual T_Vector& self() = 0;

		XxVector(XxVector<T_Scalar,T_Vector>&&) = default;
		XxVector<T_Scalar,T_Vector>& operator=(XxVector<T_Scalar,T_Vector>&&) = default;

		XxVector(const VirtualVector<T_Vector>&);
		XxVector<T_Scalar,T_Vector>& operator=(const VirtualVector<T_Vector>&);

		XxVector(const VirtualProdMv<T_Vector>&);
		XxVector<T_Scalar,T_Vector>& operator=(const VirtualProdMv<T_Vector>&);

		/** 
		 * @name Operators
		 * @{
		 */

		/**
		 * @brief Unary minus operator.
		 *
		 * Virtually negates the vector.
		 *
		 * @return The result of the virtual operation `-(*this)`.
		 */
		VirtualVector<T_Vector> operator-() const;

		/** @} */

		/** 
		 * @name Public Member Functions
		 * @{
		 */

		/**
		 * @brief Multiplies the vector by a scalar.
		 * @param[in] val The scaling coefficient.
		 */
		void iscale(T_Scalar val);

		/**
		 * @brief Virtually transposes a vector.
		 * @return A virtual vector object that represents the transposed vector.
		 */
		VirtualVector<T_Vector> transpose() const;

		/**
		 * @brief Virtually conjugate-transposes a vector.
		 * @return A virtual vector object that represents the conjugate-transposed vector.
		 */
		VirtualVector<T_Vector> ctranspose() const;

		/**
		 * @brief Virtually conjugates a vector.
		 * @return A virtual vector object that represents the conjugated vector.
		 */
		VirtualVector<T_Vector> conjugate() const;

		/**
		 * @brief Conjugates the vector in-place.
		 *
		 * Negates the imaginary part of the elements of the vector.
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
		 * @brief Vector Euclidean norm.
		 * @return The Euclidean norm of `(*this)`.
		 */
		T_RScalar normEuc() const;

		/**
		 * @brief Permutes the entries of a vector
		 *
		 * Creates a permuted copy `P*(*this)` of `(*this)`.
		 *
		 * @param[in] P The left side permutation matrix.
		 * @return The vector `P*(*this)`.
		 */
		T_Vector permuteLeft(const prm::PxMatrix<int_t>& P) const;

		/**
		 * @brief Gets a subvector with content copy.
		 *
		 * Gets a copy of a ni-sized portion of `(*this)`, starting at ibgn.
		 *
		 * @param[in] ibgn The index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A vector with content copy of `(*this)[ibgn:ibgn+ni]`.
		 */
		T_Vector block(uint_t ibgn, uint_t ni) const;

		/**
		 * @brief Gets a subvector with content reference.
		 *
		 * Gets a ni-sized vector that references contents of `(*this)`, starting at ibgn.
		 *
		 * @param[in] ibgn The index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A vector with content reference to `(*this)[ibgn:ibgn+ni]`.
		 */
		T_Vector rblock(uint_t ibgn, uint_t ni);

		/**
		 * @brief Gets a guarded subvector with content reference.
		 *
		 * Gets a ni-sized guarded vector that references contents of `(*this)`, starting at ibgn.
		 *
		 * @param[in] ibgn The index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A guarded vector with content reference to `(*this)[ibgn:ibgn+ni]`.
		 */
		Guard<T_Vector> rblock(uint_t ibgn, uint_t ni) const;

		/**
		 * @brief Sets a subvector.
		 *
		 * Copies the contents of `src` to `(*this)[ibgn:ibgn+src.size()]`.
		 *
		 * @param[in] ibgn The index that src will be placed.
		 * @param[in] src The vector to be placed.
		 */
		void setBlock(uint_t ibgn, const XxVector<T_Scalar,T_Vector>& src);

		/**
		 * @brief Converts a vector to a matrix (deep data copy).
		 * @return A copy of `(*this)` as matrix.
		 */
		T_Matrix matrix() const;

		/**
		 * @brief Converts a vector to a matrix (shallow data copy).
		 * @return A matrix referencing the contents of `(*this)`.
		 */
		T_Matrix rmatrix();

		/**
		 * @brief Converts an immutable vector to a guarded matrix (shallow data copy).
		 * @return A guarded matrix referencing the contents of `(*this)`.
		 */
		Guard<T_Matrix> rmatrix() const;

		/** @} */

		/** 
		 * @name Creators/Generators
		 * @{
		 */

		/**
		 * @brief Creates a vector with random values in (lo,hi).
		 *
		 * Creates a n-sized vector with random values.
		 *
		 * @param[in] n The vector size.
		 * @param[in] lo The smallest value of each generated element.
		 * @param[in] hi The largest value of each generated element.
		 * @return The newly created vector.
		 */
		static T_Vector random(uint_t n, T_RScalar lo = T_RScalar(0), T_RScalar hi = T_RScalar(1));

		/** @} */

	private:
		void fillFromVirtual(const VirtualVector<T_Vector>&);
		void fillFromVirtual(const VirtualProdMv<T_Vector>&);

};

/*-------------------------------------------------*/
} // namespace dns
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup module_index_stream_operators
 * @brief Writes to os the contents of vec.
 */
template <typename T_Vector>
std::ostream& operator<<(std::ostream& os, const cla3p::dns::XiVector<typename T_Vector::value_type,T_Vector>& vec)
{
	os << vec.toString();
	return os;
}

#endif // CLA3P_DNS_XXVECTOR_HPP_
