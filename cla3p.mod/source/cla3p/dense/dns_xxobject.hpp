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

#ifndef CLA3P_DNS_XXOBJECT_HPP_
#define CLA3P_DNS_XXOBJECT_HPP_

#include <cstddef>

#include "cla3p/generic/ownership.hpp"
#include "cla3p/generic/guard.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief The dense object class.
 */
template <typename T_Scalar>
class XxObject : public Ownership {

	public:
		using value_type = T_Scalar;

	public:

		explicit XxObject();
		explicit XxObject(std::size_t numElements);
		~XxObject();

		/**
		 * @brief The values array.
		 * @return The pointer to the contents of the object.
		 */
		T_Scalar* values();

		/**
		 * @copydoc cla3p::dns::XxObject::values()
		 */
		const T_Scalar* values() const;

	protected:

		void clear();

		void wrapper(T_Scalar *vals, bool bind);

	private:

		T_Scalar *m_values;

		void defaults();

		void setValues(T_Scalar *vals);
};

#if 0

/**
 * @nosubgrouping 
 * @brief The dense object class.
 */
template <typename T_Scalar, typename T_Object>
class XxObject2 : public Array2D<T_Scalar> {
	
	private:
		using T_RScalar = typename TypeTraits<T_Scalar>::real_type;

	public:
		explicit XxObject2();
		explicit XxObject2(uint_t nr, uint_t nc, uint_t nl, const Property& pr);
		~XxObject2();

		// no copy
		XxObject2(const XxObject2<T_Scalar,T_Object>&) = delete;
		XxObject2<T_Scalar,T_Object>& operator=(const XxObject2<T_Scalar,T_Object>&) = delete;

		// move
		XxObject2(XxObject2<T_Scalar,T_Object>&& other) = default;
		XxObject2<T_Scalar,T_Object>& operator=(XxObject2<T_Scalar,T_Object>&& other) = default;

		virtual const T_Object& self() const = 0;

		/** 
		 * @name Operators
		 * @{
		 */

		/**
		 * @brief Unary minus operator.
		 *
		 * Negates the object.
		 *
		 * @return The result of the operation `-(*this)`.
		 */
		T_Object operator-() const;

		/** @} */

		/** 
		 * @name Public Member Functions
		 * @{
		 */

		/**
		 * @brief Copies an object.
		 * @return A deep copy of `(*this)`.
		 */
		T_Object copy() const;

		/**
		 * @brief Shallow-copies an object.
		 * @return A shallow copy of `(*this)`, `(*this)` is unchanged.
		 */
		T_Object rcopy();

		/**
		 * @brief Shallow-copies an immutable object.
		 * @return A guard shallow copy of `(*this)`.
		 */
		Guard<T_Object> rcopy() const;

		/**
		 * @brief Moves an object.
		 * @return A shallow copy of `(*this)`, `(*this)` is destroyed.
		 */
		T_Object move();

		/**
		 * @brief Multiplies the object by a scalar.
		 * @param[in] val The scaling coefficient.
		 */
		void iscale(T_Scalar val);

		/**
		 * @brief Conjugates the object in-place.
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

		/** @} */

	protected:
		T_Object getBlockCopy(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;
		T_Object getBlockReference(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);
		Guard<T_Object> getBlockReference(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;
		void setBlockCopy(const XxObject2<T_Scalar,T_Object>&, uint_t ibgn, uint_t jbgn);

};
#endif // 0 FIXME: DELETE

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_XXOBJECT_HPP_
