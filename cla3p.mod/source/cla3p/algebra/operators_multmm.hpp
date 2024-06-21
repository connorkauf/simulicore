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

#ifndef CLA3P_OPERATORS_MULTMM_HPP_
#define CLA3P_OPERATORS_MULTMM_HPP_

/**
 * @file
 */

#include "cla3p/virtuals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns { template <typename T_Scalar, typename T_Matrix> class XxMatrix; }
namespace csc { template <typename T_Int, typename T_Scalar, typename T_Matrix> class XxMatrix; }
} // namespace cla3p
/*-------------------------------------------------*/

/*
 * Virtual x Matrix
 */
template <typename T_Virtual, typename T_Matrix>
cla3p::VirtualProd<T_Virtual,cla3p::VirtualMatrix<T_Matrix>> 
operator*(
	const cla3p::VirtualEntity<typename T_Virtual::value_type,T_Virtual>& v, 
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A) 
{ 
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	return (v.self() * vA);
}

template <typename T_Virtual, typename T_Matrix>
cla3p::VirtualProd<T_Virtual,cla3p::VirtualMatrix<T_Matrix>> 
operator*(
	const cla3p::VirtualEntity<typename T_Virtual::value_type,T_Virtual>& v, 
	const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A) 
{ 
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	return (v.self() * vA);
}

/*
 * Matrix x Virtual
 */
template <typename T_Matrix, typename T_Virtual>
cla3p::VirtualProd<cla3p::VirtualMatrix<T_Matrix>, T_Virtual> 
operator*(
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::VirtualEntity<typename T_Virtual::value_type,T_Virtual>& v) 
{ 
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	return (vA * v.self());
}

template <typename T_Matrix, typename T_Virtual>
cla3p::VirtualProd<cla3p::VirtualMatrix<T_Matrix>, T_Virtual> 
operator*(
	const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::VirtualEntity<typename T_Virtual::value_type,T_Virtual>& v) 
{ 
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	return (vA * v.self());
}

/**
 * @ingroup cla3p_module_index_math_operators_mult
 * @brief Multiplies a matrix with a matrix.
 *
 * Performs the operation <b>A * B</b>
 *
 * @param[in] A The lhs input matrix.
 * @param[in] B The rhs input matrix.
 * @return The virtual product.
 */
template <typename T_Matrix>
cla3p::VirtualProd<cla3p::VirtualMatrix<T_Matrix>,cla3p::VirtualMatrix<T_Matrix>> 
operator*(
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B) 
{
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	cla3p::VirtualMatrix<T_Matrix> vB(B.self());
	return (vA * vB);
}

/**
 * @ingroup cla3p_module_index_math_operators_mult
 * @brief Multiplies a sparse matrix with a dense matrix.
 *
 * Performs the operation <b>A * B</b>
 *
 * @warning The virtual matrix product `A * B.transpose()` 
 * where A is sparse and B is dense calculates the transpose of B explicitly.@n
 * If you plan to use the specific product in a loop, 
 * it is recommended to pre-calculate the transpose of B.
 *
 * @param[in] A The lhs input matrix.
 * @param[in] B The rhs input matrix.
 * @return The resulting dense matrix.
 */
template <typename T_CscMatrix, typename T_DnsMatrix>
cla3p::VirtualProd<cla3p::VirtualMatrix<T_CscMatrix>,cla3p::VirtualMatrix<T_DnsMatrix>> 
operator*(
	const cla3p::csc::XxMatrix<typename T_CscMatrix::index_type,typename T_CscMatrix::value_type,T_CscMatrix>& A, 
	const cla3p::dns::XxMatrix<typename T_DnsMatrix::value_type,T_DnsMatrix>& B) 
{
	cla3p::VirtualMatrix<T_CscMatrix> vA(A.self());
	cla3p::VirtualMatrix<T_DnsMatrix> vB(B.self());
	return (vA * vB);
}

/**
 * @ingroup cla3p_module_index_math_operators_mult
 * @brief Multiplies a sparse matrix with a sparse matrix.
 *
 * Performs the operation <b>A * B</b>
 *
 * @param[in] A The lhs input matrix.
 * @param[in] B The rhs input matrix.
 * @return The resulting sparse matrix.
 */
template <typename T_Matrix>
cla3p::VirtualProd<cla3p::VirtualMatrix<T_Matrix>,cla3p::VirtualMatrix<T_Matrix>> 
operator*(
	const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& B) 
{
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	cla3p::VirtualMatrix<T_Matrix> vB(B.self());
	return (vA * vB);
}

#endif // CLA3P_OPERATORS_MULTMM_HPP_
