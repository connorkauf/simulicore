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
#include "cla3p/generic/coord.hpp"

// system

// 3rd

// cla3p
#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Int>
Coord<T_Int>::Coord()
{
	defaults();
}
/*-------------------------------------------------*/
template <typename T_Int>
Coord<T_Int>::Coord(T_Int r, T_Int c)
{
	setRow(r);
	setCol(c);
}
/*-------------------------------------------------*/
template <typename T_Int>
Coord<T_Int>::~Coord()
{
}
/*-------------------------------------------------*/
template <typename T_Int>
void Coord<T_Int>::defaults()
{
	setRow(0);
	setCol(0);
}
/*-------------------------------------------------*/
template <typename T_Int>
void Coord<T_Int>::setRow(T_Int r)
{
	m_row = r;
}
/*-------------------------------------------------*/
template <typename T_Int>
void Coord<T_Int>::setCol(T_Int c)
{
	m_col = c;
}
/*-------------------------------------------------*/
template <typename T_Int>
T_Int Coord<T_Int>::row() const
{
	return m_row;
}
/*-------------------------------------------------*/
template <typename T_Int>
T_Int Coord<T_Int>::col() const
{
	return m_col;
}
/*-------------------------------------------------*/
template class Coord<int_t>;
template class Coord<uint_t>;
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
