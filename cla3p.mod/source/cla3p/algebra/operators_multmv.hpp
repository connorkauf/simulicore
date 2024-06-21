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

#ifndef CLA3P_OPERATORS_MULTMV_HPP_
#define CLA3P_OPERATORS_MULTMV_HPP_

/**
 * @file
 */

#include "cla3p/virtuals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns { template <typename T_Scalar, typename T_Vector> class XxVector; }
namespace dns { template <typename T_Scalar, typename T_Matrix> class XxMatrix; }
namespace csc { template <typename T_Int, typename T_Scalar, typename T_Matrix> class XxMatrix; }
} // namespace cla3p
/*-------------------------------------------------*/

/*
 * Virtual x Vector
 */
template <typename T_Virtual, typename T_Vector>
cla3p::VirtualProd<T_Virtual,cla3p::VirtualVector<T_Vector>> 
operator*(
	const cla3p::VirtualEntity<typename T_Virtual::value_type,T_Virtual>& v, 
	const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X) 
{ 
	cla3p::VirtualVector<T_Vector> vX(X.self());
	return (v.self() * vX);
}

/**
 * @ingroup cla3p_module_index_math_operators_mult
 * @brief Multiplies a matrix with a vector.
 *
 * Performs the operation <b>A * X</b>
 *
 * @param[in] A The input matrix.
 * @param[in] X The input vector.
 * @return The virtual product.
 */
template <typename T_Matrix, typename T_Vector>
cla3p::VirtualProd<cla3p::VirtualMatrix<T_Matrix>,cla3p::VirtualVector<T_Vector>> 
operator*(
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X) 
{ 
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	cla3p::VirtualVector<T_Vector> vX(X.self());
	return (vA * vX);
}

/**
 * @ingroup cla3p_module_index_math_operators_mult
 * @brief Multiplies a sparse matrix with a vector.
 *
 * Performs the operation <b>A * X</b>
 *
 * @param[in] A The input matrix.
 * @param[in] X The input vector.
 * @return The virtual product.
 */
template <typename T_Matrix, typename T_Vector>
cla3p::VirtualProd<cla3p::VirtualMatrix<T_Matrix>,cla3p::VirtualVector<T_Vector>> 
operator*(
	const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X)
{
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	cla3p::VirtualVector<T_Vector> vX(X.self());
	return (vA * vX);
}

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_MULTMV_HPP_
