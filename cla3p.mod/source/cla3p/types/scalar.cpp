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
#include "cla3p/types/scalar.hpp"

// system
#include <type_traits>
#include <limits>

// 3rd

// cla3p
#include "cla3p/types/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
std::string TypeTraits<real_t>::type_name() { return msg::Real(); }
std::string TypeTraits<real_t>::prec_name() { return msg::Double(); }
/*-------------------------------------------------*/
TypeTraits<real_t>::real_type TypeTraits<real_t>::epsilon() 
{ 
	return std::numeric_limits<TypeTraits<real_t>::real_type>::epsilon(); 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string TypeTraits<real4_t>::type_name() { return msg::Real(); }
std::string TypeTraits<real4_t>::prec_name() { return msg::Single(); }
/*-------------------------------------------------*/
TypeTraits<real4_t>::real_type TypeTraits<real4_t>::epsilon() 
{ 
	return std::numeric_limits<TypeTraits<real4_t>::real_type>::epsilon(); 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string TypeTraits<complex_t>::type_name() { return msg::Complex(); }
std::string TypeTraits<complex_t>::prec_name() { return msg::Double(); }
/*-------------------------------------------------*/
TypeTraits<complex_t>::real_type TypeTraits<complex_t>::epsilon() 
{ 
	return std::numeric_limits<TypeTraits<complex_t>::real_type>::epsilon(); 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string TypeTraits<complex8_t>::type_name() { return msg::Complex(); }
std::string TypeTraits<complex8_t>::prec_name() { return msg::Single(); }
/*-------------------------------------------------*/
TypeTraits<complex8_t>::real_type TypeTraits<complex8_t>::epsilon() 
{ 
	return std::numeric_limits<TypeTraits<complex8_t>::real_type>::epsilon(); 
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

