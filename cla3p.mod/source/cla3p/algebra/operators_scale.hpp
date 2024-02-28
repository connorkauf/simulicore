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

#ifndef CLA3P_OPERATORS_SCALING_HPP_
#define CLA3P_OPERATORS_SCALING_HPP_

/**
 * @file
 * Global scaling operator definitions
 */

#include "cla3p/virtuals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns { template <typename T_Scalar, typename T_Object> class XxObject; }
namespace dns { template <typename T_Scalar, typename T_Vector> class XxVector; }
namespace dns { template <typename T_Scalar, typename T_Matrix> class XxMatrix; }
namespace csc { template <typename T_Int, typename T_Scalar, typename T_Matrix> class XxMatrix; }
} // namespace cla3p
/*-------------------------------------------------*/

/*
 * Combinations                  | Valid Op | Return Type
 * ------------------------------------------------------
 * T_Scalar      * XxVector      | YES      | VirtualVector
 * T_Scalar      * XxMatrix      | YES      | VirtualMatrix
 * T_Scalar      * VirtualEntity | YES      | T_Virtual
 *                               |          |
 * XxVector      * T_Scalar      | YES      | VirtualVector
 * XxMatrix      * T_Scalar      | YES      | VirtualMatrix
 * VirtualEntity * T_Scalar      | YES      | T_Virtual
 *                               |          |
 * XxVector      / T_Scalar      | YES      | VirtualVector
 * XxMatrix      / T_Scalar      | YES      | VirtualMatrix
 * VirtualEntity / T_Scalar      | YES      | T_Virtual
 *                               |          |
 * XxVector      *= T_Scalar     | YES      | void
 * XxMatrix      *= T_Scalar     | YES      | void
 * VirtualEntity *= T_Scalar     | YES      | void
 *                               |          |
 * XxVector      /= T_Scalar     | YES      | void
 * XxMatrix      /= T_Scalar     | YES      | void
 * VirtualEntity /= T_Scalar     | YES      | void
 */

/**
 * @ingroup module_index_math_operators_scal
 * @brief Multiplies a scalar with a vector.
 *
 * Performs the operation <b>val * X</b>
 *
 * @param[in] val The coefficient value.
 * @param[in] X The input vector.
 * @return The virtually scaled vector.
 */
template <typename T_Vector>
cla3p::VirtualVector<T_Vector> operator*(
		typename T_Vector::value_type val, 
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X) 
{ 
	cla3p::VirtualVector<T_Vector> sv(X.self());
  return sv.scale(val);
}

/**
 * @ingroup module_index_math_operators_scal
 * @brief Multiplies a scalar with a dense matrix.
 *
 * Performs the operation <b>val * A</b>
 *
 * @param[in] val The coefficient value.
 * @param[in] A The input matrix.
 * @return The virtually scaled matrix.
 */
template <typename T_Matrix>
cla3p::VirtualMatrix<T_Matrix> operator*(
		typename T_Matrix::value_type val, 
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A) 
{ 
	cla3p::VirtualMatrix<T_Matrix> sm(A.self());
  return sm.scale(val);
}

/**
 * @ingroup module_index_math_operators_scal
 * @brief Multiplies a scalar with a sparse matrix.
 *
 * Performs the operation <b>val * A</b>
 *
 * @param[in] val The coefficient value.
 * @param[in] A The input matrix.
 * @return The scaled matrix copy.
 */
template <typename T_Matrix>
T_Matrix operator*(
		typename T_Matrix::value_type val, 
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A) 
{ 
	T_Matrix ret = A.copy();
	ret.iscale(val);
	return ret;
}

/*-------------------------------------------------*/

/*
 * T_Scalar * VirtualEntity
 */
template <typename T_Object, typename T_Virtual> 
T_Virtual operator*(
		typename T_Object::value_type val, 
		const cla3p::VirtualEntity<T_Object,T_Virtual>& v)
{ 
	return v.scale(val); 
}

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_scal
 * @brief Multiplies a vector with a scalar.
 *
 * Performs the operation <b>X * val</b>
 *
 * @param[in] X The input vector.
 * @param[in] val The coefficient value.
 * @return The virtually scaled vector.
 */
template <typename T_Vector>
cla3p::VirtualVector<T_Vector> operator*(
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X, 
		typename T_Vector::value_type val) 
{ 
	cla3p::VirtualVector<T_Vector> sv(X.self());
  return sv.scale(val);
}

/**
 * @ingroup module_index_math_operators_scal
 * @brief Multiplies a dense matrix with a scalar.
 *
 * Performs the operation <b>A * val</b>
 *
 * @param[in] A The input matrix.
 * @param[in] val The coefficient value.
 * @return The virtually scaled matrix.
 */
template <typename T_Matrix>
cla3p::VirtualMatrix<T_Matrix> operator*(
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
		typename T_Matrix::value_type val) 
{ 
	cla3p::VirtualMatrix<T_Matrix> sm(A.self());
  return sm.scale(val);
}

/**
 * @ingroup module_index_math_operators_scal
 * @brief Multiplies a sparse matrix with a scalar.
 *
 * Performs the operation <b>A * val</b>
 *
 * @param[in] A The input matrix.
 * @param[in] val The coefficient value.
 * @return The scaled matrix copy.
 */
template <typename T_Matrix>
T_Matrix operator*(
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A, 
		typename T_Matrix::value_type val) 
{ 
	return (val * A);
}

/*-------------------------------------------------*/

/*
 * VirtualEntity * T_Scalar
 */
template <typename T_Object, typename T_Virtual>
T_Virtual operator*(
		const cla3p::VirtualEntity<T_Object,T_Virtual>& v, 
		typename T_Object::value_type val)
{ 
	return (val * v);
}

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_scal
 * @brief Devides a vector by a scalar.
 *
 * Performs the operation <b>(1/val) * X</b>
 *
 * @param[in] X The input vector.
 * @param[in] val The non-zero coefficient value.
 * @return The virtually scaled vector.
 */
template <typename T_Vector>
cla3p::VirtualVector<T_Vector> operator/(
		const cla3p::dns::XxVector<typename T_Vector::value_type,T_Vector>& X, 
		typename T_Vector::value_type val) 
{ 
	return (cla3p::arith::inv(val) * X);
}

/**
 * @ingroup module_index_math_operators_scal
 * @brief Devides a dense matrix by a scalar.
 *
 * Performs the operation <b>(1/val) * A</b>
 *
 * @param[in] A The input matrix.
 * @param[in] val The non-zero coefficient value.
 * @return The virtually scaled matrix.
 */
template <typename T_Matrix>
cla3p::VirtualMatrix<T_Matrix> operator/(
		const cla3p::dns::XxMatrix<typename T_Matrix::value_type,T_Matrix>& A, 
		typename T_Matrix::value_type val) 
{ 
	return (cla3p::arith::inv(val) * A);
}

/**
 * @ingroup module_index_math_operators_scal
 * @brief Devides a sparse matrix by a scalar.
 *
 * Performs the operation <b>(1/val) * A</b>
 *
 * @param[in] A The input matrix.
 * @param[in] val The non-zero coefficient value.
 * @return The scaled matrix copy.
 */
template <typename T_Matrix>
T_Matrix operator/(
		const cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A, 
		typename T_Matrix::value_type val) 
{ 
	return (cla3p::arith::inv(val) * A);
}

/*-------------------------------------------------*/

/*
 * VirtualEntity / T_Scalar
 */
template <typename T_Object, typename T_Virtual>
T_Virtual operator/(
		const cla3p::VirtualEntity<T_Object,T_Virtual>& v, 
		typename T_Object::value_type val)
{ 
	return v.scale(cla3p::arith::inv(val));
}

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_scal
 * @brief Scaling operator.
 *
 * Scales `src` by `val`.
 *
 * @param[in] src The input object.
 * @param[in] val The scaling coefficient.
 */
template <typename T_Object>
void operator*=(
		cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& src, 
		typename T_Object::value_type val);

/**
 * @ingroup module_index_math_operators_scal
 * @brief Scaling operator.
 *
 * Scales `A` by `val`.
 *
 * @param[in] A The input sparse matrix.
 * @param[in] val The scaling coefficient.
 */
template <typename T_Matrix>
void operator*=(
		cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A, 
		typename T_Matrix::value_type val);

/*-------------------------------------------------*/

/*
 * VirtualEntity *= T_Scalar
 */
template <typename T_Object, typename T_Virtual>
void operator*=(
		cla3p::VirtualEntity<T_Object,T_Virtual>& v, 
		typename T_Object::value_type val)
{ 
	v.iscale(val); 
}

/*-------------------------------------------------*/

/**
 * @ingroup module_index_math_operators_scal
 * @brief Scaling operator.
 *
 * Scales `src` by `1/val`.
 *
 * @param[in] src The input object.
 * @param[in] val The non-zero scaling coefficient.
 */
template <typename T_Object>
void operator/=(
		cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& src, 
		typename T_Object::value_type val);

/**
 * @ingroup module_index_math_operators_scal
 * @brief Scaling operator.
 *
 * Scales `A` by `1/val`.
 *
 * @param[in] A The input sparse matrix.
 * @param[in] val The scaling coefficient.
 */
template <typename T_Matrix>
void operator/=(
		cla3p::csc::XxMatrix<typename T_Matrix::index_type,typename T_Matrix::value_type,T_Matrix>& A, 
		typename T_Matrix::value_type val);

/*-------------------------------------------------*/

/*
 * VirtualEntity /= T_Scalar
 */
template <typename T_Object, typename T_Virtual>
void operator/=(
		cla3p::VirtualEntity<T_Object,T_Virtual>& v, 
		typename T_Object::value_type val)
{ 
	v.iscale(cla3p::arith::inv(val)); 
}

/*-------------------------------------------------*/

#endif // CLA3P_OPERATORS_SCALING_HPP_
