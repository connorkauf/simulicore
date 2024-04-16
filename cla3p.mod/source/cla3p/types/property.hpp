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
 */

#include <ostream>
#include <string>
#include <vector>

#include "cla3p/types/scalar.hpp"
#include "cla3p/types/enums.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
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
		 * @brief Switches the uplo field.
		 *
		 * Makes the upper property lower & vice versa. Full uplo remains the same.
		 */
		void switchUplo();

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

	public:

		/**
		 * @brief The General property.
		 *
		 * Constructs a general property.
		 */
		static Property General();

		/**
		 * @brief The Symmetric property (upper fill).
		 *
		 * Constructs a symmetric property, upper matrix part will be filled/used.
		 */
		static Property SymmetricUpper();

		/**
		 * @brief The Symmetric property (lower fill).
		 *
		 * Constructs a symmetric property, lower matrix part will be filled/used.
		 */
		static Property SymmetricLower();

		/**
		 * @brief The Hermitian property (upper fill).
		 *
		 * Constructs a hermitian property, upper matrix part will be filled/used.
		 */
		static Property HermitianUpper();

		/**
		 * @brief The Hermitian property (lower fill).
		 *
		 * Constructs a hermitian property, lower matrix part will be filled/used.
		 */
		static Property HermitianLower();

		/**
		 * @brief The Triangular property (upper fill).
		 *
		 * Constructs a triangular/trapezoidal property, upper matrix part will be filled/used.
		 */
		static Property TriangularUpper();

		/**
		 * @brief The Triangular property (lower fill).
		 *
		 * Constructs a triangular/trapezoidal property, lower matrix part will be filled/used.
		 */
		static Property TriangularLower();

		/**
		 * @brief The Skew property (upper fill).
		 *
		 * Constructs a skew property, upper matrix part will be filled/used.
		 */
		static Property SkewUpper();

		/**
		 * @brief The Skew property (lower fill).
		 *
		 * Constructs a skew property, lower matrix part will be filled/used.
		 */
		static Property SkewLower();

	private:
		prop_t m_type;
		uplo_t m_uplo;

		void defaults();
		void check() const;
};

/*-------------------------------------------------*/

template <typename T_Scalar>
inline Property sanitizeProperty(const Property& pr)
{
	if(pr.isHermitian() && TypeTraits<T_Scalar>::is_real()) {
		return Property(prop_t::Symmetric, pr.uplo());
	} // convert to symmetric
	return pr;
}

std::vector<Property> allProperties();

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
