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

#ifndef CLA3P_VIRTUAL_ENTITY_HPP_
#define CLA3P_VIRTUAL_ENTITY_HPP_

/**
 * @file
 */

#include <ostream>

#include "cla3p/types/integer.hpp"

/*-------------------------------------------------*/

namespace cla3p {
namespace dns { template <typename T_Scalar, typename T_Vector> class XxVector; }
namespace dns { template <typename T_Scalar, typename T_Matrix> class XxMatrix; }
namespace csc { template <typename T_Int, typename T_Scalar, typename T_Matrix> class XxMatrix; }
} // namespace cla3p

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

template <typename T_Object, typename T_Virtual>
class VirtualEntity {

	private:
		using T_Scalar = typename T_Object::value_type;

	public:
		using value_type = T_Object;

		VirtualEntity() = default;
		~VirtualEntity() = default;

		virtual const T_Virtual& self() const = 0;
		virtual uint_t size1() const = 0;
		virtual uint_t size2() const = 0;
		virtual T_Virtual scale(T_Scalar val) const = 0;
		virtual T_Virtual conjugate() const = 0;

		virtual void addToTarget(T_Scalar, T_Object&) const = 0;

		T_Object evaluate() const
		{
			T_Object ret;
			addToTarget(T_Scalar(0), ret);
			return ret;
		}

		T_Virtual operator-() const
		{
			return scale(T_Scalar(-1));
		}
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup module_index_stream_operators
 * @brief Writes to os the contents of the evaluated v.
 */
template <typename T_Virtual>
std::ostream& operator<<(std::ostream& os, const cla3p::VirtualEntity<typename T_Virtual::value_type,T_Virtual>& v)
{
	os << v.evaluate();
	return os;
}

#endif // CLA3P_VIRTUAL_ENTITY_HPP_
