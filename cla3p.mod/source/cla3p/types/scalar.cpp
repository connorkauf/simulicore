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
#include "cla3p/types/scalar.hpp"

// system

// 3rd

// cla3p
#include "cla3p/types/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
std::string BasicTypeTraits<real_t>::type_name() { return msg::Real(); }
std::string BasicTypeTraits<real_t>::prec_name() { return msg::Double(); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string BasicTypeTraits<real4_t>::type_name() { return msg::Real(); }
std::string BasicTypeTraits<real4_t>::prec_name() { return msg::Single(); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string BasicTypeTraits<complex_t>::type_name() { return msg::Complex(); }
std::string BasicTypeTraits<complex_t>::prec_name() { return msg::Double(); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string BasicTypeTraits<complex8_t>::type_name() { return msg::Complex(); }
std::string BasicTypeTraits<complex8_t>::prec_name() { return msg::Single(); }
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

