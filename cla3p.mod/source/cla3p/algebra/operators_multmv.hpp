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
 * Combinations                  | Valid Op | Return Type
 * ------------------------------------------------------
 * XxMatrix * XxVector           | YES      | VirtualProdMv 
 * XxMatrix * VirtualVector      | YES      | VirtualProdMv
 * XxMatrix * VirtualProdMv      | YES      | T_Vector
 *                               |          |
 * VirtualMatrix * XxVector      | YES      | VirtualProdMv
 * VirtualMatrix * VirtualVector | YES      | VirtualProdMv
 * VirtualMatrix * VirtualProdMv | YES      | T_Vector
 *                               |          |
 * VirtualProdMm * XxVector      | YES      | T_Vector
 * VirtualProdMm * VirtualVector | YES      | T_Vector
 * VirtualProdMm * VirtualProdMv | YES      | T_Vector
 */

/**
 * @ingroup module_index_math_operators_mult
 * @brief Multiplies a matrix with a vector.
 *
 * Performs the operation <b>A * X</b>
 *
 * @param[in] A The input matrix.
 * @param[in] X The input vector.
 * @return The virtual product.
 */
template <typename T_Matrix, typename T_Vector>
cla3p::VirtualProdMv<T_Matrix,T_Vector> operator*(
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X) 
{ 
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	cla3p::VirtualVector<T_Vector> vX(X.self());
	cla3p::VirtualProdMv<T_Matrix,T_Vector> ret(vA,vX);
	return ret;
}

/*-------------------------------------------------*/

/*
 * XxMatrix * VirtualVector
 */
template <typename T_Matrix, typename T_Vector>
cla3p::VirtualProdMv<T_Matrix,T_Vector> operator*(
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::VirtualVector<T_Vector>& vX) 
{ 
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	cla3p::VirtualProdMv<T_Matrix,T_Vector> ret(vA,vX);
	return ret;
}

/*-------------------------------------------------*/

/*
 * XxMatrix * VirtualProdMv
 */
template <typename T_Matrix, typename T_Vector>
T_Vector operator*(
	const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::VirtualProdMv<T_Matrix,T_Vector>& vX) 
{ 
	return (A * vX.evaluate()).evaluate();
}

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_mult
 * @brief Multiplies a sparse matrix with a vector.
 *
 * Performs the operation <b>A * X</b>
 *
 * @param[in] A The input matrix.
 * @param[in] X The input vector.
 * @return The virtual product.
 */
template <typename T_Matrix, typename T_Vector>
T_Vector operator*(
	const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X);

/*-------------------------------------------------*/

/*
 * XxMatrix * VirtualVector
 */
template <typename T_Matrix, typename T_Vector>
T_Vector operator*(
	const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::VirtualVector<T_Vector>& vX) 
{ 
	return (A * vX.evaluate());
}

/*-------------------------------------------------*/

/*
 * XxMatrix * VirtualProdMv
 */
template <typename T_Matrix, typename T_Vector>
T_Vector operator*(
	const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A, 
	const cla3p::VirtualProdMv<T_Matrix,T_Vector>& vX) 
{ 
	return (A * vX.evaluate()).evaluate();
}

/*-------------------------------------------------*/

/*
 * VirtualMatrix * XxVector
 */
template <typename T_Matrix, typename T_Vector>
cla3p::VirtualProdMv<T_Matrix,T_Vector> operator*(
	const cla3p::VirtualMatrix<T_Matrix>& vA, 
	const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X) 
{ 
	cla3p::VirtualVector<T_Vector> vX(X.self());
	cla3p::VirtualProdMv<T_Matrix,T_Vector> ret(vA,vX);
	return ret;
}

/*-------------------------------------------------*/

/*
 * VirtualMatrix * VirtualVector
 */
template <typename T_Matrix, typename T_Vector>
cla3p::VirtualProdMv<T_Matrix,T_Vector> operator*(
	const cla3p::VirtualMatrix<T_Matrix>& vA, 
	const cla3p::VirtualVector<T_Vector>& vX) 
{ 
	cla3p::VirtualProdMv<T_Matrix,T_Vector> ret(vA,vX);
	return ret;
}

/*-------------------------------------------------*/

/*
 * VirtualMatrix * VirtualProdMv
 */
template <typename T_Matrix, typename T_Vector>
T_Vector operator*(
	const cla3p::VirtualMatrix<T_Matrix>& vA, 
	const cla3p::VirtualProdMv<T_Matrix,T_Vector>& vX) 
{ 
	return (vA * vX.evaluate()).evaluate();
}

/*-------------------------------------------------*/

/*
 * VirtualProdMm * XxVector
 */
template <typename T_Matrix, typename T_Vector>
T_Vector operator*(
	const cla3p::VirtualProdMm<T_Matrix>& vA, 
	const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X) 
{ 
	return (vA.evaluate() * X).evaluate();
}

/*-------------------------------------------------*/

/*
 * VirtualProdMm * VirtualVector
 */
template <typename T_Matrix, typename T_Vector>
T_Vector operator*(
	const cla3p::VirtualProdMm<T_Matrix>& vA, 
	const cla3p::VirtualVector<T_Vector>& vX) 
{ 
	return (vA.evaluate() * vX).evaluate();
}

/*-------------------------------------------------*/

/*
 * VirtualProdMm * VirtualProdMv
 */
template <typename T_Matrix, typename T_Vector>
T_Vector operator*(
	const cla3p::VirtualProdMm<T_Matrix>& vA, 
	const cla3p::VirtualProdMv<T_Matrix,T_Vector>& vX) 
{ 
	return (vA.evaluate() * vX.evaluate()).evaluate();
}

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_MULTMV_HPP_
