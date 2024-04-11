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

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

template <typename T_Object, typename T_Virtual>
class VirtualEntity {

	private:
		using T_Scalar = typename T_Object::value_type;

	public:
		VirtualEntity() = default;
		~VirtualEntity() = default;

		virtual const T_Virtual& self() const = 0;
		virtual T_Object evaluate() const = 0;
		virtual void evaluateOnExisting(T_Object&) const = 0;
		virtual void addToExisting(T_Object&) const = 0;

		virtual void iscale(T_Scalar val) = 0;
		virtual void iconjugate() = 0;

		T_Virtual scale(T_Scalar val) const;
		T_Virtual conjugate() const;

		T_Virtual operator-() const;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup module_index_stream_operators
 * @brief Writes to os the contents of v.
 */
template <typename T_Object, typename T_Virtual>
std::ostream& operator<<(std::ostream& os, const cla3p::VirtualEntity<T_Object,T_Virtual>& v)
{
	os << v.evaluate().toString();
	return os;
}

#endif // CLA3P_VIRTUAL_ENTITY_HPP_
