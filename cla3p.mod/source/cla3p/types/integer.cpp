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
#include "cla3p/types/integer.hpp"

// system
#include <type_traits>
#include <limits>

// 3rd

// cla3p
#include "cla3p/types/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
std::string TypeTraits<int_t>::type_name()
{
  return msg::Integer();
}
/*-------------------------------------------------*/
std::string TypeTraits<int_t>::prec_name()
{
#if defined (CLA3P_I64)
  return msg::Double();
#else
  return msg::Single();
#endif
}
/*-------------------------------------------------*/
int_t TypeTraits<int_t>::epsilon()
{
	return std::numeric_limits<int_t>::epsilon();
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string TypeTraits<uint_t>::type_name()
{
  return msg::UnsignedInteger();
}
/*-------------------------------------------------*/
std::string TypeTraits<uint_t>::prec_name()
{
#if defined (CLA3P_I64)
  return msg::Double();
#else
  return msg::Single();
#endif
}
/*-------------------------------------------------*/
uint_t TypeTraits<uint_t>::epsilon()
{
	return std::numeric_limits<uint_t>::epsilon();
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
