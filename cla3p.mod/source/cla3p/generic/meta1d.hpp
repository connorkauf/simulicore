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

#ifndef CLA3P_META1D_HPP_
#define CLA3P_META1D_HPP_

#include "cla3p/types/integer.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief The single dimension metadata class.
 */
class Meta1D {

	public:
		Meta1D();
		Meta1D(uint_t n);
		~Meta1D();

		/**
		 * @brief The vector size.
		 * @return The number of entries in `(*this)`.
		 */
		uint_t size() const;

		/**
		 * @brief Test whether object is empty.
		 * @return true if object dimension is zero, false otherwise
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
		void setSize(uint_t n);

		void wrapper(uint_t n);

	private:
		uint_t m_size;

		void defaults();
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_META1D_HPP_
