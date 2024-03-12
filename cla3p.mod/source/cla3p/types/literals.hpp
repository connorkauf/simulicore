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

#ifndef CLA3P_TYPE_LITERALS_HPP_
#define CLA3P_TYPE_LITERALS_HPP_

/** 
 * @file
 */

#include <string>

/*-------------------------------------------------*/
namespace cla3p {
namespace msg {
/*-------------------------------------------------*/
std::string Unknown();

std::string Integer();
std::string UnsignedInteger();
std::string Real();
std::string Complex();

std::string Single();
std::string Double();

std::string Dense();
std::string SparseCsc();
std::string SparseCoo();

std::string Vector();
std::string Matrix();
std::string PermutationMatrix();

std::string DenseVector();
std::string DenseMatrix();
std::string SparseCscMatrix();
std::string SparseCooMatrix();

std::string NoOperation();
std::string TransposeOperation();
std::string ConjugateTransposeOperation();

std::string General();
std::string Symmetric();
std::string Hermitian();
std::string Triangular();
std::string Skew();

std::string Full();
std::string Upper();
std::string Lower();

/*-------------------------------------------------*/
} // namespace msg
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_TYPE_LITERALS_HPP_
