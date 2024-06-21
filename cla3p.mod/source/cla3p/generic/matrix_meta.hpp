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

#ifndef CLA3P_MATRIX_META_HPP_
#define CLA3P_MATRIX_META_HPP_

/**
 * @file
 */

#include "cla3p/generic/meta2d.hpp"
#include "cla3p/types/property.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief The matrix metadata class.
 */
class MatrixMeta : public Meta2D {

	public:
		MatrixMeta();
		MatrixMeta(uint_t nr, uint_t nc, const Property& pr);
		~MatrixMeta();

		/**
		 * @brief The matrix property.
		 * @details Gets the defined property for the matrix.
		 */
		const Property& prop() const;

	protected:
		void clear();
		void setProp(const Property& pr);

		void wrapper(uint_t nr, uint_t nc, const Property& pr);

	private:
		Property m_prop;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_MATRIX_META_HPP_
