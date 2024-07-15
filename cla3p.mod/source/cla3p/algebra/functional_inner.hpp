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

#ifndef CLA3P_ALGEBRA_FUNCTIONAL_INNER_HPP_
#define CLA3P_ALGEBRA_FUNCTIONAL_INNER_HPP_

/**
 * @file
 */

/*-------------------------------------------------*/
namespace cla3p { 
namespace ops {
/*-------------------------------------------------*/

/**
 * @ingroup cla3p_module_index_math_op_vecvec
 * @brief Calculate vector dot product.
 *
 * Performs the operation <b>X<sup>T</sup> Y</b>
 *
 * @param[in] X The input vector.
 * @param[in] Y The input vector.
 * @return The dot product value.
 */
template <typename T_Vector>
typename T_Vector::value_type dot(const T_Vector& X, const T_Vector& Y);

/**
 * @ingroup cla3p_module_index_math_op_vecvec
 * @brief Calculate vector conjugate dot product.
 *
 * Performs the operation <b>X<sup>H</sup> Y</b>
 *
 * @param[in] X The input vector.
 * @param[in] Y The input vector.
 * @return The conjugate dot product value.
 */
template <typename T_Vector>
typename T_Vector::value_type dotc(const T_Vector& X, const T_Vector& Y);

/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ALGEBRA_FUNCTIONAL_INNER_HPP_
