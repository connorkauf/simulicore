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

#ifndef CLA3P_OPERATORS_ADD_HPP_
#define CLA3P_OPERATORS_ADD_HPP_

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
 * Generic Add Operator
 */
template <typename T_Object, typename T_Lhs, typename T_Rhs>
cla3p::VirtualSum<T_Object,T_Lhs,T_Rhs>
operator+(
		const cla3p::VirtualEntity<T_Object,T_Lhs>& vA,
		const cla3p::VirtualEntity<T_Object,T_Rhs>& vB)
{
	return cla3p::VirtualSum<T_Object,T_Lhs,T_Rhs>(vA.self(),vB.self());
}

/*
 * Generic Sub Operator
 */
template <typename T_Object, typename T_Lhs, typename T_Rhs>
cla3p::VirtualSum<T_Object,T_Lhs,T_Rhs>
operator-(
		const cla3p::VirtualEntity<T_Object,T_Lhs>& vA,
		const cla3p::VirtualEntity<T_Object,T_Rhs>& vB)
{
	return cla3p::VirtualSum<T_Object,T_Lhs,T_Rhs>(vA.self(),vB.scale(-1));
}

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_add
 * @brief Adds two compatible vectors.
 *
 * Performs the operation <b>X + Y</b>
 *
 * @param[in] X The first vector.
 * @param[in] Y The second vector.
 * @return The virtual vector sum that simulates the sum of the two.
 */
template <typename T_Vector>
cla3p::VirtualSum<T_Vector,cla3p::VirtualVector<T_Vector>,cla3p::VirtualVector<T_Vector>>
operator+(
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X,
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& Y)
{
	cla3p::VirtualVector<T_Vector> vX(X.self());
	cla3p::VirtualVector<T_Vector> vY(Y.self());
	return (vX + vY);
}

template <typename T_Vector, typename T_Virtual>
cla3p::VirtualSum<T_Vector,cla3p::VirtualVector<T_Vector>,T_Virtual>
operator+(
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X,
		const cla3p::VirtualEntity<T_Vector,T_Virtual>& vY)
{
	cla3p::VirtualVector<T_Vector> vX(X.self());
	return (vX + vY.self());
}

template <typename T_Vector, typename T_Virtual>
cla3p::VirtualSum<T_Vector,T_Virtual,cla3p::VirtualVector<T_Vector>>
operator+(
		const cla3p::VirtualEntity<T_Vector,T_Virtual>& vX,
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& Y)
{
	cla3p::VirtualVector<T_Vector> vY(Y.self());
	return (vX.self() + vY);
}

/**
 * @ingroup module_index_math_operators_add
 * @brief Subtracts two compatible vectors.
 *
 * Performs the operation <b>X - Y</b>
 *
 * @param[in] X The first vector.
 * @param[in] Y The second vector.
 * @return The virtual vector sum that simulates the subtraction of the two.
 */
template <typename T_Vector>
cla3p::VirtualSum<T_Vector,cla3p::VirtualVector<T_Vector>,cla3p::VirtualVector<T_Vector>>
operator-(
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X,
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& Y)
{
	cla3p::VirtualVector<T_Vector> vX(X.self());
	cla3p::VirtualVector<T_Vector> vY(Y.self());
	return (vX - vY);
}

template <typename T_Vector, typename T_Virtual>
cla3p::VirtualSum<T_Vector,cla3p::VirtualVector<T_Vector>,T_Virtual>
operator-(
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X,
		const cla3p::VirtualEntity<T_Vector,T_Virtual>& vY)
{
	cla3p::VirtualVector<T_Vector> vX(X.self());
	return (vX - vY.self());
}

template <typename T_Vector, typename T_Virtual>
cla3p::VirtualSum<T_Vector,T_Virtual,cla3p::VirtualVector<T_Vector>>
operator-(
		const cla3p::VirtualEntity<T_Vector,T_Virtual>& vX,
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& Y)
{
	cla3p::VirtualVector<T_Vector> vY(Y.self());
	return (vX.self() - vY);
}

/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_add
 * @brief Adds two compatible matrices.
 *
 * Performs the operation <b>A + B</b>
 *
 * @param[in] A The first matrix.
 * @param[in] B The second matrix.
 * @return The virtual matrix sum that simulates the sum of the two.
 */
template <typename T_Matrix>
cla3p::VirtualSum<T_Matrix,cla3p::VirtualMatrix<T_Matrix>,cla3p::VirtualMatrix<T_Matrix>>
operator+(
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B)
{
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	cla3p::VirtualMatrix<T_Matrix> vB(B.self());
	return (vA + vB);
}

template <typename T_Matrix, typename T_Virtual>
cla3p::VirtualSum<T_Matrix,cla3p::VirtualMatrix<T_Matrix>,T_Virtual>
operator+(
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::VirtualEntity<T_Matrix,T_Virtual>& vB)
{
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	return (vA + vB.self());
}

template <typename T_Matrix, typename T_Virtual>
cla3p::VirtualSum<T_Matrix,T_Virtual,cla3p::VirtualMatrix<T_Matrix>>
operator+(
		const cla3p::VirtualEntity<T_Matrix,T_Virtual>& vA,
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B)
{
	cla3p::VirtualMatrix<T_Matrix> vB(B.self());
	return (vA.self() + vB);
}

/**
 * @ingroup module_index_math_operators_add
 * @brief Subtracts two compatible matrices.
 *
 * Performs the operation <b>A - B</b>
 *
 * @param[in] A The first matrix.
 * @param[in] B The second matrix.
 * @return The virtual matrix sum that simulates the subtraction of the two.
 */
template <typename T_Matrix>
cla3p::VirtualSum<T_Matrix,cla3p::VirtualMatrix<T_Matrix>,cla3p::VirtualMatrix<T_Matrix>>
operator-(
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B)
{
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	cla3p::VirtualMatrix<T_Matrix> vB(B.self());
	return (vA - vB);
}

template <typename T_Matrix, typename T_Virtual>
cla3p::VirtualSum<T_Matrix,cla3p::VirtualMatrix<T_Matrix>,T_Virtual>
operator-(
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::VirtualEntity<T_Matrix,T_Virtual>& vB)
{
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	return (vA - vB.self());
}

template <typename T_Matrix, typename T_Virtual>
cla3p::VirtualSum<T_Matrix,T_Virtual,cla3p::VirtualMatrix<T_Matrix>>
operator-(
		const cla3p::VirtualEntity<T_Matrix,T_Virtual>& vA,
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B)
{
	cla3p::VirtualMatrix<T_Matrix> vB(B.self());
	return (vA.self() - vB);
}

/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_add
 * @brief Adds two compatible sparse matrices.
 *
 * Performs the operation <b>A + B</b>
 *
 * @param[in] A The first sparse matrix.
 * @param[in] B The second sparse matrix.
 * @return The sparse matrix that is the sum of the two.
 */
template <typename T_Matrix>
cla3p::VirtualSum<T_Matrix,cla3p::VirtualMatrix<T_Matrix>,cla3p::VirtualMatrix<T_Matrix>>
operator+(
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& B)
{
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	cla3p::VirtualMatrix<T_Matrix> vB(B.self());
	return (vA + vB);
}

template <typename T_Matrix, typename T_Virtual>
cla3p::VirtualSum<T_Matrix,cla3p::VirtualMatrix<T_Matrix>,T_Virtual>
operator+(
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::VirtualEntity<T_Matrix,T_Virtual>& vB)
{
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	return (vA + vB.self());
}

template <typename T_Matrix, typename T_Virtual>
cla3p::VirtualSum<T_Matrix,T_Virtual,cla3p::VirtualMatrix<T_Matrix>>
operator+(
		const cla3p::VirtualEntity<T_Matrix,T_Virtual>& vA,
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& B)
{
	cla3p::VirtualMatrix<T_Matrix> vB(B.self());
	return (vA.self() + vB);
}

/**
 * @ingroup module_index_math_operators_add
 * @brief Subtracts two compatible sparse matrices.
 *
 * Performs the operation <b>A - B</b>
 *
 * @param[in] A The first sparse matrix.
 * @param[in] B The second sparse matrix.
 * @return The sparse matrix that is the difference of the two.
 */
template <typename T_Matrix>
cla3p::VirtualSum<T_Matrix,cla3p::VirtualMatrix<T_Matrix>,cla3p::VirtualMatrix<T_Matrix>>
operator-(
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& B)
{
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	cla3p::VirtualMatrix<T_Matrix> vB(B.self());
	return (vA - vB);
}

template <typename T_Matrix, typename T_Virtual>
cla3p::VirtualSum<T_Matrix,cla3p::VirtualMatrix<T_Matrix>,T_Virtual>
operator-(
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A,
		const cla3p::VirtualEntity<T_Matrix,T_Virtual>& vB)
{
	cla3p::VirtualMatrix<T_Matrix> vA(A.self());
	return (vA - vB.self());
}

template <typename T_Matrix, typename T_Virtual>
cla3p::VirtualSum<T_Matrix,T_Virtual,cla3p::VirtualMatrix<T_Matrix>>
operator-(
		const cla3p::VirtualEntity<T_Matrix,T_Virtual>& vA,
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& B)
{
	cla3p::VirtualMatrix<T_Matrix> vB(B.self());
	return (vA.self() - vB);
}

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_ADD_HPP_
