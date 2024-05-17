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

#ifndef CLA3P_CSC_XXOBJECT_HPP_
#define CLA3P_CSC_XXOBJECT_HPP_

/**
 * @file
 */

#include <cstddef>

#include "cla3p/types.hpp"
#include "cla3p/generic/ownership.hpp"
#include "cla3p/generic/guard.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace csc {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief The dense object class.
 */
template <typename T_Int, typename T_Scalar>
class XxObject : public Ownership {

	public:
		using index_type = T_Int;
		using value_type = T_Scalar;

	public:

		explicit XxObject();
		explicit XxObject(uint_t nc, uint_t nz);
		~XxObject();

		/**
		 * @brief The column pointer array.
		 * @return The array containing the number of non-zero elements in each column of `(*this)`.
		 */
		T_Int* colptr();

		/**
		 * @copydoc colptr()
		 */
		const T_Int* colptr() const;

		/**
		 * @brief The row index array.
		 * @return The array containing the non-zero element row index in each column of `(*this)`.
		 */
		T_Int* rowidx();

		/**
		 * @copydoc rowidx()
		 */
		const T_Int* rowidx() const;

		/**
		 * @brief The values array.
		 * @return The pointer to the contents of the object.
		 */
		T_Scalar* values();

		/**
		 * @copydoc cla3p::csc::XxObject::values()
		 */
		const T_Scalar* values() const;

	protected:

		void clear();

		void wrapper(T_Int *cptr, T_Int *ridx, T_Scalar *vals, bool bind);

	private:

		T_Int*    m_colptr;
		T_Int*    m_rowidx;
		T_Scalar* m_values;

		void defaults();

		void setColptr(T_Int*);
		void setRowidx(T_Int*);
		void setValues(T_Scalar*);
};

/*-------------------------------------------------*/
} // namespace csc
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_CSC_XXOBJECT_HPP_
