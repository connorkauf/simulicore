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

#ifndef CLA3P_COORD_HPP_
#define CLA3P_COORD_HPP_

#include <ostream>

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

template <typename T_Int>
class Coord {

	public:
		Coord();
		Coord(T_Int r, T_Int c);
		~Coord();

		T_Int row() const;
		T_Int col() const;

	private:
		T_Int m_row;
		T_Int m_col;

		void setRow(T_Int r);
		void setCol(T_Int c);

		void defaults();
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

template <typename T_Int>
std::ostream& operator<<(std::ostream& os, const cla3p::Coord<T_Int>& coord)
{
  os << "(" << coord.row() << ", " << coord.col() << ")";
  return os;
}

#endif // CLA3P_COORD_HPP_
