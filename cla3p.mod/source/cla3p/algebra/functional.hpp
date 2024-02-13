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

#ifndef CLA3P_ALGEBRA_FUNCTIONAL_HPP_
#define CLA3P_ALGEBRA_FUNCTIONAL_HPP_

/**
 * @file
 * Global math operations
 */

#include "cla3p/types/operation.hpp"
#include "cla3p/types/property.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
template <typename T_Scalar, typename T_Object> class XxObject;
template <typename T_Scalar, typename T_Vector> class XxVector;
template <typename T_Scalar, typename T_Matrix> class XxMatrix;
} // namespace dns
namespace csc {
template <typename T_Int, typename T_Scalar, typename T_Object> class XxObject;
template <typename T_Int, typename T_Scalar, typename T_Vector> class XxVector;
template <typename T_Int, typename T_Scalar, typename T_Matrix> class XxMatrix;
} // namespace csc
} // namespace cla3p
/*-------------------------------------------------*/

/*-------------------------------------------------*/
namespace cla3p { 
namespace ops {
/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_op_vecvec
 * @brief Calculate vector dot product.
 *
 * Performs the operation <b>X<sup>T</sup> Y</b>
 *
 * @param[in] X The input vector.
 * @param[in] Y The input vector.
 * @return The dot product value.
 */
template <typename T_Vector>
typename T_Vector::value_type dot(
		const dns::XxVector<typename T_Vector::value_type,T_Vector>& X, 
		const dns::XxVector<typename T_Vector::value_type,T_Vector>& Y)
{
	return X.calcDotProductWith(Y);
}

/**
 * @ingroup module_index_math_op_vecvec
 * @brief Calculate vector conjugate dot product.
 *
 * Performs the operation <b>X<sup>H</sup> Y</b>
 *
 * @param[in] X The input vector.
 * @param[in] Y The input vector.
 * @return The conjugate dot product value.
 */
template <typename T_Vector>
typename T_Vector::value_type dotc(
		const dns::XxVector<typename T_Vector::value_type,T_Vector>& X, 
		const dns::XxVector<typename T_Vector::value_type,T_Vector>& Y)
{
	return X.calcConjugateDotProductWith(Y);
}

/**
 * @ingroup module_index_math_op_vecvec
 * @brief Update a matrix with a vector outer product.
 *
 * Performs the operation <b>A = A + alpha * X Y<sup>T</sup></b>@n
 * A can be General/Symmetric/Hermitian.@n
 * If A is Symmetric/Hermitian, it is assumed that the outcome of the operation <b>X Y<sup>T</sup></b> is also Symmetric/Hermitian 
 * and only the corresponding part (upper/lower) will be calculated.
 *
 * @param[in] alpha The update coefficient.
 * @param[in] X The input vector.
 * @param[in] Y The input vector.
 * @param[in,out] A The matrix to be updated.
 */
template <typename T_Vector>
void outer(typename T_Vector::value_type alpha, 
		const dns::XxVector<typename T_Vector::value_type,T_Vector>& X, 
		const dns::XxVector<typename T_Vector::value_type,T_Vector>& Y,
		typename TypeTraits<T_Vector>::matrix_type& A)
{
	A.updateSelfWithScaledVecVec(false, alpha, X, Y);
}

/**
 * @ingroup module_index_math_op_vecvec
 * @brief Update a matrix with a conjugate vector outer product.
 *
 * Performs the operation <b>A = A + alpha * X Y<sup>H</sup></b>@n
 * A can be General/Symmetric/Hermitian.@n
 * If A is Symmetric/Hermitian, it is assumed that the outcome of the operation <b>X Y<sup>H</sup></b> is also Symmetric/Hermitian
 * and only the corresponding part (upper/lower) will be calculated.
 *
 * @param[in] alpha The update coefficient.
 * @param[in] X The input vector.
 * @param[in] Y The input vector.
 * @param[in,out] A The matrix to be updated.
 */
template <typename T_Vector>
void outerc(typename T_Vector::value_type alpha, 
		const dns::XxVector<typename T_Vector::value_type,T_Vector>& X, 
		const dns::XxVector<typename T_Vector::value_type,T_Vector>& Y,
		typename TypeTraits<T_Vector>::matrix_type& A)
{
	A.updateSelfWithScaledVecVec(true, alpha, X, Y);
}

/**
 * @ingroup module_index_math_op_vecvec
 * @brief Calculate vector outer product.
 *
 * Performs the operation <b>X Y<sup>T</sup></b>.@n
 * %Property pr can be General/Symmetric/Hermitian.@n
 * If pr is Symmetric/Hermitian, it is assumed that the outcome of the operation <b>X Y<sup>T</sup></b> is also Symmetric/Hermitian
 * and only the corresponding part (upper/lower) will be calculated.
 *
 * @param[in] X The input vector.
 * @param[in] Y The input vector.
 * @param[in] pr The property of the output matrix.
 * @return The outer product matrix.
 */
template <typename T_Vector>
typename TypeTraits<T_Vector>::matrix_type outer(
		const dns::XxVector<typename T_Vector::value_type,T_Vector>& X, 
		const dns::XxVector<typename T_Vector::value_type,T_Vector>& Y,
		const Property& pr = defaultProperty())
{
	typename TypeTraits<T_Vector>::matrix_type ret(X.size(), Y.size(), pr);
	ret = 0;
	outer(1, X, Y, ret);
	return ret;
}

/**
 * @ingroup module_index_math_op_vecvec
 * @brief Calculate vector conjugate outer product.
 *
 * Performs the operation <b>X Y<sup>H</sup></b>@n
 * %Property pr can be General/Symmetric/Hermitian.@n
 * If pr is Symmetric/Hermitian, it is assumed that the outcome of the operation <b>X Y<sup>H</sup></b> is also Symmetric/Hermitian
 * and only the corresponding part (upper/lower) will be calculated.
 *
 * @param[in] X The input vector.
 * @param[in] Y The input vector.
 * @param[in] pr The property of the output matrix.
 * @return The conjugate outer product matrix.
 */
template <typename T_Vector>
typename TypeTraits<T_Vector>::matrix_type outerc(
		const dns::XxVector<typename T_Vector::value_type,T_Vector>& X, 
		const dns::XxVector<typename T_Vector::value_type,T_Vector>& Y,
		const Property& pr = defaultProperty())
{
	typename TypeTraits<T_Vector>::matrix_type ret(X.size(), Y.size(), pr);
	ret = 0;
	outerc(1, X, Y, ret);
	return ret;
}

/**
 * @ingroup module_index_math_op_add
 * @brief Update a dense object with a compatible scaled dense object.
 *
 * Performs the operation <b>B = B + alpha * A</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] A The input dense object.
 * @param[in,out] B The dense object to be updated.
 */
template <typename T_Object>
void update(
		typename T_Object::value_type alpha, 
		const dns::XxObject<typename T_Object::value_type,T_Object>& A, 
		dns::XxObject<typename T_Object::value_type,T_Object>& B)
{
	B.updateSelfWithScaledOther(alpha, A);
}

/**
 * @ingroup module_index_math_op_add
 * @brief Update a sparse matrix with a compatible scaled sparse matrix.
 *
 * Performs the operation <b>B = B + alpha * A</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] A The input sparse matrix.
 * @param[in,out] B The sparse matrix to be updated.
 */
template <typename T_Matrix>
void update(
		typename T_Matrix::value_type alpha, 
		const csc::XxMatrix<int_t,typename T_Matrix::value_type,T_Matrix>& A, 
		csc::XxMatrix<int_t,typename T_Matrix::value_type,T_Matrix>& B)
{
	B.updateSelfWithScaledOther(alpha, A);
}

/**
 * @ingroup module_index_math_op_add
 * @brief Adds two compatible scaled dense objects.
 *
 * Performs the operation <b>alpha * A + beta * B</b>
 *
 * @param[in] alpha The scaling coefficient for A.
 * @param[in] A The first input dense object.
 * @param[in] beta The scaling coefficient for B.
 * @param[in] B The second input dense object.
 * @return The result of the operation <b>(alpha * A + beta * B)</b>.
 */
template <typename T_Object>
T_Object add(
		typename T_Object::value_type alpha, const dns::XxObject<typename T_Object::value_type,T_Object>& A, 
		typename T_Object::value_type beta , const dns::XxObject<typename T_Object::value_type,T_Object>& B)
{
	T_Object ret;
	ret.createFromScaledSum(alpha, A, beta, B);
	return ret;
}

/**
 * @ingroup module_index_math_op_add
 * @brief Adds two compatible sparse matrices.
 *
 * Performs the operation <b>alpha * A + B</b>
 *
 * @param[in] alpha The scaling coefficient for A.
 * @param[in] A The first input sparse matrix.
 * @param[in] B The second input sparse matrix.
 * @return The result of the operation <b>(alpha * A + B)</b>.
 */
template <typename T_Matrix>
T_Matrix add(
		typename T_Matrix::value_type alpha, 
		const csc::XxMatrix<int_t,typename T_Matrix::value_type,T_Matrix>& A, 
		const csc::XxMatrix<int_t,typename T_Matrix::value_type,T_Matrix>& B)
{
	T_Matrix ret;
	ret.createFromScaledSum(alpha, A, B);
	return ret;
}

/**
 * @ingroup module_index_math_op_matvec
 * @brief Updates a vector with a matrix-vector product.
 *
 * Performs the operation <b>Y = Y + alpha * opA(A) * X</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A. If A is symmetric or hermitian, opA is ignored.
 * @param[in] A The input matrix.
 * @param[in] X The input vector.
 * @param[in,out] Y The vector to be updated.
 */

template <typename T_Vector, typename T_Matrix>
void mult(typename T_Vector::value_type alpha, op_t opA, 
		const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
		const dns::XxVector<typename T_Vector::value_type,T_Vector>& X, 
		dns::XxVector<typename T_Vector::value_type,T_Vector>& Y)
{
	Y.updateSelfWithScaledMatVec(alpha, opA, A, X);
}

/**
 * @ingroup module_index_math_op_matvec
 * @brief Creates a vector from a matrix-vector product.
 *
 * Performs the operation <b>alpha * opA(A) * X</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A. If A is symmetric or hermitian, opA is ignored.
 * @param[in] A The input matrix.
 * @param[in] X The input vector.
 * @return The vector <b>(alpha * opA(A) * X)</b>.
 */
template <typename T_Vector, typename T_Matrix>
T_Vector mult(typename T_Vector::value_type alpha, op_t opA, 
		const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
		const dns::XxVector<typename T_Vector::value_type,T_Vector>& X)
{
	Operation _opA(opA);
	T_Vector ret(_opA.isTranspose() ? A.ncols() : A.nrows());
	ret = 0;
	mult(alpha, opA, A, X, ret);
	return ret;
}

/**
 * @ingroup module_index_math_op_matvec
 * @brief Replaces a vector with a triangular matrix-vector product.
 *
 * Performs the operation <b>X := opA(A) * X</b>
 *
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input triangular matrix.
 * @param[in,out] X The vector to be replaced.
 */
template <typename T_Vector, typename T_Matrix>
void trimult(op_t opA, 
		const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
		dns::XxVector<typename T_Vector::value_type,T_Vector>& X)
{
	X.replaceSelfWithTriVec(opA, A);
}

/**
 * @ingroup module_index_math_op_matvec
 * @brief Replaces a vector with the solution of a triangular system.
 *
 * Solves the system <b>opA(A) * X = B</b>
 *
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input triangular matrix.
 * @param[in,out] B On entry, the rhs, on exit the system solution X.
 */
template <typename T_Vector, typename T_Matrix>
void trisol(op_t opA, 
		const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
		dns::XxVector<typename T_Vector::value_type,T_Vector>& B)
{
	B.replaceSelfWithInvTriVec(opA, A);
}

/**
 * @ingroup module_index_math_op_matmat
 * @brief Updates a general matrix with a matrix-matrix product.
 *
 * Performs the operation <b>C = C + alpha * opA(A) * opB(B)</b>@n
 * C can be General/Symmetric/Hermitian.@n
 * If C is Symmetric/Hermitian, it is assumed that the outcome of the operation <b>opA(A) * opB(B)</b> is also Symmetric/Hermitian
 * and only the corresponding part (upper/lower) will be calculated.
 *
 * Valid combinations are the following:
 @verbatim
  A: General     B: General     opA: unconstrained      opB: unconstrained      C: General/Symmetric/Hermitian
  A: Symmetric   B: General     opA: ignored            opB: must be set to N   C: General
  A: Hermitian   B: General     opA: ignored            opB: must be set to N   C: General
  A: Triangular  B: General     opA: unconstrained      opB: must be set to N   C: General
  A: General     B: Symmetric   opA: must be set to N   opB: ignored            C: General
  A: General     B: Hermitian   opA: must be set to N   opB: ignored            C: General
  A: General     B: Triangular  opA: must be set to N   opB: unconstrained      C: General
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input matrix.
 * @param[in] opB The operation to be performed for matrix B.
 * @param[in] B The input matrix.
 * @param[in,out] C The matrix to be updated.
 */
template <typename T_Matrix>
void mult(typename T_Matrix::value_type alpha, 
		op_t opA, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
		op_t opB, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B, 
		dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& C)
{
	C.updateSelfWithScaledMatMat(alpha, opA, A, opB, B);
}

/**
 * @ingroup module_index_math_op_matmat
 * @brief Creates a general matrix from a matrix-matrix product.
 *
 * Performs the operation <b>alpha * opA(A) * opB(B)</b>@n
 * %Property pr can be General/Symmetric/Hermitian.@n
 * If pr is Symmetric/Hermitian, it is assumed that the outcome of the operation <b>opA(A) * opB(B)</b> is also Symmetric/Hermitian
 * and only the corresponding part (upper/lower) will be calculated.
 *
 * Valid combinations are the following:
 @verbatim
  A: General     B: General     opA: unconstrained      opB: unconstrained      C: General/Symmetric/Hermitian
  A: Symmetric   B: General     opA: ignored            opB: must be set to N   C: General
  A: Hermitian   B: General     opA: ignored            opB: must be set to N   C: General
  A: Triangular  B: General     opA: unconstrained      opB: must be set to N   C: General
  A: General     B: Symmetric   opA: must be set to N   opB: ignored            C: General
  A: General     B: Hermitian   opA: must be set to N   opB: ignored            C: General
  A: General     B: Triangular  opA: must be set to N   opB: unconstrained      C: General
 @endverbatim
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input matrix.
 * @param[in] opB The operation to be performed for matrix B.
 * @param[in] B The input matrix.
 * @param[in] pr The property of the output matrix.
 * @return The matrix <b>(alpha * opA(A) * opB(B))</b>.
 */
template <typename T_Matrix>
T_Matrix mult(typename T_Matrix::value_type alpha, 
		op_t opA, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
		op_t opB, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B,
		const Property& pr = defaultProperty())
{
	Operation _opA(opA);
	Operation _opB(opB);
	T_Matrix ret(
			_opA.isTranspose() ? A.ncols() : A.nrows(), 
			_opB.isTranspose() ? B.nrows() : B.ncols(), pr);
	ret = 0;
	mult(alpha, opA, A, opB, B, ret);
	return ret;
}

/**
 * @ingroup module_index_math_op_matmat
 * @brief Replaces a matrix with a scaled triangular matrix-matrix product.
 *
 * Performs the operation <b>B := alpha * opA(A) * B</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input triangular matrix.
 * @param[in,out] B The matrix to be replaced.
 */
template <typename T_Matrix>
void trimult(typename T_Matrix::value_type alpha, op_t opA, 
		const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
		dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B)
{
	B.replaceSelfWithScaledTriMat(alpha, side_t::Left, opA, A);
}

/**
 * @ingroup module_index_math_op_matmat
 * @brief Replaces a matrix with a scaled triangular matrix-matrix product.
 *
 * Performs the operation <b>B := alpha * B * opA(A)</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in,out] B The matrix to be replaced.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input triangular matrix.
 */
template <typename T_Matrix>
void trimult(typename T_Matrix::value_type alpha, 
		dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B,
		op_t opA, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A) 
{
	B.replaceSelfWithScaledTriMat(alpha, side_t::Right, opA, A);
}

/**
 * @ingroup module_index_math_op_matmat
 * @brief Replaces a matrix with the scaled solution of a triangular system.
 *
 * Solves the system <b>opA(A) * X = alpha * B</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input triangular matrix.
 * @param[in,out] B On entry, the rhs, on exit the system solution X.
 */
template <typename T_Matrix>
void trisol(typename T_Matrix::value_type alpha, op_t opA, 
		const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
		dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B)
{
	B.replaceSelfWithScaledInvTriMat(alpha, side_t::Left, opA, A);
}

/**
 * @ingroup module_index_math_op_matmat
 * @brief Replaces a matrix with the scaled solution of a triangular system.
 *
 * Solves the system <b>X * opA(A) = alpha * B</b>
 *
 * @param[in] alpha The scaling coefficient.
 * @param[in,out] B On entry, the rhs, on exit the system solution X.
 * @param[in] opA The operation to be performed for matrix A.
 * @param[in] A The input triangular matrix.
 */
template <typename T_Matrix>
void trisol(typename T_Matrix::value_type alpha, 
		dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& B,
		op_t opA, const dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A) 
{
	B.replaceSelfWithScaledInvTriMat(alpha, side_t::Right, opA, A);
}

/*-------------------------------------------------*/
} // namespace ops
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ALGEBRA_FUNCTIONAL_HPP_
