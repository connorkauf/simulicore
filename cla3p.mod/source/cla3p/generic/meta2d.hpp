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

#ifndef CLA3P_META2D_HPP_
#define CLA3P_META2D_HPP_

#include "cla3p/types/integer.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief The double dimension metadata class.
 */
class Meta2D {

	public:
		Meta2D();
		Meta2D(uint_t m, uint_t n);
		~Meta2D();

		/**
		 * @brief The matrix rows.
		 * @return The number of rows in `(*this)`.
		 */
		uint_t nrows() const;

		/**
		 * @brief The matrix columns.
		 * @return The number of columns in `(*this)`.
		 */
		uint_t ncols() const;

		/**
		 * @brief Test whether object is empty.
		 * @return true if object dimensions is zero, false otherwise
		 */
		bool empty() const;

		/**
		 * @copydoc empty()
		 */
		bool operator!() const; 

		/**
		 * @brief Test whether object is empty.
		 * @return true if object is not empty, false otherwise
		 */
		operator bool() const;

	protected:
		void clear();
		void setNrows(uint_t m);
		void setNcols(uint_t n);

		void wrapper(uint_t m, uint_t n);

	private:
		uint_t m_nrows;
		uint_t m_ncols;

		void defaults();
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_META2D_HPP_
