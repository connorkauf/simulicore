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

#ifndef CLA3P_PROPERTY_HPP_
#define CLA3P_PROPERTY_HPP_

/** 
 * @file
 * Property configuration
 */

#include <ostream>
#include <string>

#include "cla3p/types/enums.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @ingroup module_index_datatypes
 * @brief The property class.
 *
 * Used to define matrix properties.@n
 * Constructing a matrix with property can accelerate certain operations, 
 * but at the same time imposes equivalent constraints on others.
 *
 * @include ex00_property_create.cpp
 */
class Property {

	public:

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty property.
		 */
		Property();

		/**
		 * @brief The member constructor.
		 *
		 * Constructs a property with type `ptype` and fill type `ftype`.
		 */
		explicit Property(prop_t ptype, uplo_t ftype);

		/**
		 * @brief Destructs the property.
		 */
		~Property();

		/**
		 * @brief The copy constructor.
		 *
		 * Constructs a property with the copy of the contents of `other`.
		 */
		Property(const Property& other);

		/**
		 * @brief The copy assignment operator.
		 *
		 * Replaces the contents of `(*this)` with a copy of the contents of `other`.
		 */
		Property& operator=(const Property& other);

		/**
		 * @brief The compare operator.
		 *
		 * Checks if two properties are equal.
		 */
		bool operator==(const Property& other) const;

		/**
		 * @brief The compare operator.
		 *
		 * Checks if two properties are not equal.
		 */
		bool operator!=(const Property& other) const;

		/**
		 * @brief Resets all members.
		 *
		 * Returns property to initial state.
		 */
		void clear();

		/**
		 * @brief The property type.
		 */
		prop_t type() const;

		/**
		 * @brief The property fill type.
		 */
		uplo_t uplo() const;

		/**
		 * @brief The property fill type as a char.
		 */
		char cuplo() const;

		/**
		 * @brief The property name.
		 */
		std::string name() const;

		/**
		 * @brief Checks weather the property has a valid type.
		 */
		bool isValid() const;

		/**
		 * @brief Checks weather the property requires matrix to be square.
		 */
		bool isSquare() const;

		/**
		 * @brief Checks weather the property type is general.
		 */
		bool isGeneral() const;

		/**
		 * @brief Checks weather the property type is symmetric.
		 */
		bool isSymmetric() const;

		/**
		 * @brief Checks weather the property type is hermitian.
		 */
		bool isHermitian() const;

		/**
		 * @brief Checks weather the property type is triangular/trapezoidal.
		 */
		bool isTriangular() const;

		/**
		 * @brief Checks weather the property type is skew.
		 */
		bool isSkew() const;

		/**
		 * @brief Checks weather the entire matrix is used.
		 */
		bool isFull() const;

		/**
		 * @brief Checks weather the upper part of the matrix is used.
		 */
		bool isUpper() const;

		/**
		 * @brief Checks weather the lower part of the matrix is used.
		 */
		bool isLower() const;

	private:
		prop_t m_type;
		uplo_t m_uplo;

		void defaults();
		void check() const;
};

/*-------------------------------------------------*/

inline Property defaultProperty()
{
	return Property(prop_t::General, uplo_t::Full);
}

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup module_index_stream_operators
 * @brief Writes to os the type of pr.
 */
std::ostream& operator<<(std::ostream& so, const cla3p::Property& pr);

/*-------------------------------------------------*/

#endif // CLA3P_PROPERTY_HPP_
