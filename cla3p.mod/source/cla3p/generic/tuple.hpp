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

#ifndef CLA3P_TUPLE_HPP_
#define CLA3P_TUPLE_HPP_

#include <ostream>

#include "cla3p/generic/coord.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

template <typename T_Int, typename T_Scalar>
class Tuple : public Coord<T_Int> {

	public:
		Tuple();
		Tuple(T_Int r, T_Int c, T_Scalar v);
		~Tuple();

		T_Scalar val() const;

	private:
		T_Scalar m_val;

		void setVal(T_Scalar v);

		void defaults();
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

template <typename T_Int, typename T_Scalar>
std::ostream& operator<<(std::ostream& os, const cla3p::Tuple<T_Int,T_Scalar>& tuple)
{
  os << "(" << tuple.row() << ", " << tuple.col() << ", " << tuple.val() << ")";
  return os;
}

#endif // CLA3P_TUPLE_HPP_
