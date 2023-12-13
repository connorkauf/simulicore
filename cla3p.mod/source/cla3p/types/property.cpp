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
#include "cla3p/types/property.hpp"

// system
#include <sstream>

// 3rd

// cla3p
#include "cla3p/types/literals.hpp"
#include "cla3p/error/exceptions.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
Property::Property()
{
	defaults();
}
/*-------------------------------------------------*/
Property::Property(const Property& other)
	: m_type(other.type()), m_uplo(other.uplo())
{
}
/*-------------------------------------------------*/
Property& Property::operator=(const Property& other)
{
	m_type = other.type();
	m_uplo = other.uplo();
	return *this;
}
/*-------------------------------------------------*/
bool Property::operator==(const Property& other) const
{
	return (m_type == other.type() && m_uplo == other.uplo());
}
/*-------------------------------------------------*/
bool Property::operator!=(const Property& other) const
{
	return !(*this == other);
}
/*-------------------------------------------------*/
Property::Property(prop_t ptype, uplo_t ftype)
	: m_type(ptype), m_uplo(ftype)
{
	check();
}
/*-------------------------------------------------*/
Property::~Property()
{
}
/*-------------------------------------------------*/
void Property::defaults()
{
	m_type = prop_t::Undefined;
	m_uplo = uplo_t::Full;
}
/*-------------------------------------------------*/
void Property::clear()
{
	defaults();
}
/*-------------------------------------------------*/
prop_t Property::type() const
{
	return m_type;
}
/*-------------------------------------------------*/
uplo_t Property::uplo() const
{
	return m_uplo;
}
/*-------------------------------------------------*/
char Property::cuplo() const
{
	return static_cast<char>(uplo());
}
/*-------------------------------------------------*/
void Property::check() const
{
	if(isGeneral() && !isFull()) {
		throw err::NoConsistency("Bad type/uplo combo");
	} 
	if(!isGeneral() && isFull()) {
		throw err::NoConsistency("Bad type/uplo combo");
	} 
}
/*-------------------------------------------------*/
std::string Property::name() const
{
	std::ostringstream ss;

	ss << type() << " " << uplo();

	return ss.str();
}
/*-------------------------------------------------*/
bool Property::isValid() const
{
	return (type() != prop_t::Undefined);
}
/*-------------------------------------------------*/
bool Property::isSquare() const
{
	return (isSymmetric() || isHermitian() || isSkew());
}
/*-------------------------------------------------*/
bool Property::isGeneral() const
{
	return (type() == prop_t::General);
}
/*-------------------------------------------------*/
bool Property::isSymmetric() const
{
	return (type() == prop_t::Symmetric);
}
/*-------------------------------------------------*/
bool Property::isHermitian() const
{
	return (type() == prop_t::Hermitian);
}
/*-------------------------------------------------*/
bool Property::isTriangular() const
{
	return (type() == prop_t::Triangular);
}
/*-------------------------------------------------*/
bool Property::isSkew() const
{
	return (type() == prop_t::Skew);
}
/*-------------------------------------------------*/
bool Property::isFull() const
{
	return (uplo() == uplo_t::Full);
}
/*-------------------------------------------------*/
bool Property::isUpper() const
{
	return (uplo() == uplo_t::Upper);
}
/*-------------------------------------------------*/
bool Property::isLower() const
{
	return (uplo() == uplo_t::Lower);
}
/*-------------------------------------------------*/
std::vector<Property> allProperties()
{
	std::vector<cla3p::Property> ret(9);

	ret[0] = cla3p::Property(cla3p::prop_t::General   , cla3p::uplo_t::Full );
	ret[1] = cla3p::Property(cla3p::prop_t::Symmetric , cla3p::uplo_t::Upper);
	ret[2] = cla3p::Property(cla3p::prop_t::Symmetric , cla3p::uplo_t::Lower);
	ret[3] = cla3p::Property(cla3p::prop_t::Hermitian , cla3p::uplo_t::Upper);
	ret[4] = cla3p::Property(cla3p::prop_t::Hermitian , cla3p::uplo_t::Lower);
	ret[5] = cla3p::Property(cla3p::prop_t::Triangular, cla3p::uplo_t::Upper);
	ret[6] = cla3p::Property(cla3p::prop_t::Triangular, cla3p::uplo_t::Lower);
	ret[7] = cla3p::Property(cla3p::prop_t::Skew      , cla3p::uplo_t::Upper);
	ret[8] = cla3p::Property(cla3p::prop_t::Skew      , cla3p::uplo_t::Lower);

	return ret;
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::Property& prop)
{
	os << prop.name();
	return os;
}
/*-------------------------------------------------*/
