/*
 * Copyright (c) 2023-2024 Connor C. Kaufman (connor.kaufman.gh@outlook.com)
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

// 3rd

// cla3p
#include "cla3p/types/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
std::string BasicTypeTraits<int_t>::type_name()
{
  return msg::Integer();
}
/*-------------------------------------------------*/
std::string BasicTypeTraits<int_t>::prec_name()
{
#if defined (CLA3P_I64)
  return msg::Double();
#else
  return msg::Single();
#endif
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string BasicTypeTraits<uint_t>::type_name()
{
  return msg::UnsignedInteger();
}
/*-------------------------------------------------*/
std::string BasicTypeTraits<uint_t>::prec_name()
{
#if defined (CLA3P_I64)
  return msg::Double();
#else
  return msg::Single();
#endif
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
