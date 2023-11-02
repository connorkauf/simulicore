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

#ifndef CLA3P_ERROR_LITERALS_HPP_
#define CLA3P_ERROR_LITERALS_HPP_

#include <string>

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace msg {
/*-------------------------------------------------*/

std::string IndexOutOfBounds(uint_t m, uint_t n, uint_t i, uint_t j);
std::string IndexOutOfBounds(uint_t n, uint_t i);

std::string Success();
std::string InvalidDimensions();
std::string InvalidPointer();
std::string InvalidLeadingDimension();
std::string InvalidProperty();
std::string NeedSquareMatrix();
std::string EmptyObject();
std::string OpNotAllowed();
std::string LapackError();
std::string DivisionByZero();
std::string HermitianInconsistency();

/*-------------------------------------------------*/
} // namespace msg
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ERROR_LITERALS_HPP_
