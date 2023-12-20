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

// this file inc
#include "cla3p/generic/tuple.hpp"

// system

// 3rd

// cla3p
#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
Tuple<T_Int,T_Scalar>::Tuple()
{
	defaults();
}
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
Tuple<T_Int,T_Scalar>::Tuple(T_Int r, T_Int c, T_Scalar v)
	: Coord<T_Int>(r,c)
{
	setVal(v);
}
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
Tuple<T_Int,T_Scalar>::~Tuple()
{
}
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
void Tuple<T_Int,T_Scalar>::defaults()
{
	setVal(0);
}
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
void Tuple<T_Int,T_Scalar>::setVal(T_Scalar v)
{
	m_val = v;
}
/*-------------------------------------------------*/
template <typename T_Int, typename T_Scalar>
T_Scalar Tuple<T_Int,T_Scalar>::val() const
{
	return m_val;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class Tuple<int_t,real_t>;
template class Tuple<int_t,real4_t>;
template class Tuple<int_t,complex_t>;
template class Tuple<int_t,complex8_t>;
template class Tuple<uint_t,real_t>;
template class Tuple<uint_t,real4_t>;
template class Tuple<uint_t,complex_t>;
template class Tuple<uint_t,complex8_t>;
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
