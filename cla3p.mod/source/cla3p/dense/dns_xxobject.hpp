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

/**
 * @file
 */

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

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_XXOBJECT_HPP_
