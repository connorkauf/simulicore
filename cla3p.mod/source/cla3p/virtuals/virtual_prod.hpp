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

#ifndef CLA3P_VIRTUAL_PROD_HPP_
#define CLA3P_VIRTUAL_PROD_HPP_

/**
 * @file
 */

#include "cla3p/virtuals/virtual_object.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

/*
 * Dense Vector Output
 */
template <typename T_Matrix, typename T_Vector>
void performVirtualMult(
		const VirtualMatrix<T_Matrix>&, 
		const VirtualVector<T_Vector>&, 
		typename T_Vector::value_type, 
		dns::XxVector<typename T_Vector::value_type, T_Vector>&);

template <typename T_Matrix, typename T_Rhs>
void performVirtualMult(
		const VirtualMatrix<T_Matrix>& vA, 
		const VirtualEntity<typename T_Rhs::value_type,T_Rhs>& vR, 
		typename T_Rhs::value_type::value_type beta, 
		dns::XxVector<typename T_Rhs::value_type::value_type, typename T_Rhs::value_type>& Y)
{
	using T_Vector = typename T_Rhs::value_type;
	T_Vector X = vR.evaluate();
	VirtualVector<T_Vector> vX(X);
	performVirtualMult(vA, vX, beta, Y);
}

template <typename T_Lhs, typename T_Vector>
void performVirtualMult(
		const VirtualEntity<typename T_Lhs::value_type,T_Lhs>& vL, 
		const VirtualVector<T_Vector>& vX, 
		typename T_Vector::value_type beta, 
		dns::XxVector<typename T_Vector::value_type, T_Vector>& Y)
{
	using T_Matrix = typename T_Lhs::value_type;
	T_Matrix A = vL.evaluate();
	VirtualMatrix<T_Matrix> vA(A);
	performVirtualMult(vA, vX, beta, Y);
}

template <typename T_Lhs, typename T_Rhs>
void performVirtualMult(
		const VirtualEntity<typename T_Lhs::value_type,T_Lhs>& vL, 
		const VirtualEntity<typename T_Rhs::value_type,T_Rhs>& vR, 
		typename T_Rhs::value_type::value_type beta, 
		dns::XxVector<typename T_Rhs::value_type::value_type, typename T_Rhs::value_type>& Y)
{
	using T_Matrix = typename T_Lhs::value_type;
	using T_Vector = typename T_Rhs::value_type;
	T_Matrix A = vL.evaluate();
	T_Vector X = vR.evaluate();
	VirtualMatrix<T_Matrix> vA(A);
	VirtualVector<T_Vector> vX(X);
	performVirtualMult(vA, vX, beta, Y);
}

/*
 * Dense Matrix Output
 */

template <typename T_LhsMatrix, typename T_RhsMatrix>
void performVirtualMult(
		const VirtualMatrix<T_LhsMatrix>&, 
		const VirtualMatrix<T_RhsMatrix>&, 
		typename T_RhsMatrix::value_type, 
		dns::XxMatrix<typename T_RhsMatrix::value_type, T_RhsMatrix>&);

template <typename T_Matrix, typename T_Rhs>
void performVirtualMult(
		const VirtualMatrix<T_Matrix>& vA, 
		const VirtualEntity<typename T_Rhs::value_type,T_Rhs>& vR, 
		typename T_Rhs::value_type::value_type beta, 
		dns::XxMatrix<typename T_Rhs::value_type::value_type, typename T_Rhs::value_type>& C)
{
	using T_RhsMatrix = typename T_Rhs::value_type;
	T_RhsMatrix B = vR.evaluate();
	VirtualMatrix<T_RhsMatrix> vB(B);
	performVirtualMult(vA, vB, beta, C);
}

template <typename T_Lhs, typename T_Matrix>
void performVirtualMult(
		const VirtualEntity<typename T_Lhs::value_type,T_Lhs>& vL, 
		const VirtualMatrix<T_Matrix>& vB, 
		typename T_Matrix::value_type beta, 
		dns::XxMatrix<typename T_Matrix::value_type, T_Matrix>& C)
{
	using T_LhsMatrix = typename T_Lhs::value_type;
	T_LhsMatrix A = vL.evaluate();
	VirtualMatrix<T_LhsMatrix> vA(A);
	performVirtualMult(vA, vB, beta, C);
}

template <typename T_Lhs, typename T_Rhs>
void performVirtualMult(
		const VirtualEntity<typename T_Lhs::value_type,T_Lhs>& vL, 
		const VirtualEntity<typename T_Rhs::value_type,T_Rhs>& vR, 
		typename T_Rhs::value_type::value_type beta, 
		dns::XxMatrix<typename T_Rhs::value_type::value_type, typename T_Rhs::value_type>& C)
{
	using T_LhsMatrix = typename T_Lhs::value_type;
	using T_RhsMatrix = typename T_Rhs::value_type;
	T_LhsMatrix A = vL.evaluate();
	T_RhsMatrix B = vR.evaluate();
	VirtualMatrix<T_LhsMatrix> vA(A);
	VirtualMatrix<T_RhsMatrix> vB(B);
	performVirtualMult(vA, vB, beta, C);
}

/*
 * Sparse Matrix Output
 */

template <typename T_Matrix>
void performVirtualMult(
		const VirtualMatrix<T_Matrix>&, 
		const VirtualMatrix<T_Matrix>&, 
		typename T_Matrix::value_type, 
		csc::XxMatrix<typename T_Matrix::index_type, typename T_Matrix::value_type, T_Matrix>&);

template <typename T_Matrix, typename T_Rhs>
void performVirtualMult(
		const VirtualMatrix<T_Matrix>& vA, 
		const VirtualEntity<typename T_Rhs::value_type,T_Rhs>& vR, 
		typename T_Rhs::value_type::value_type beta, 
		csc::XxMatrix<typename T_Rhs::value_type::index_type, typename T_Rhs::value_type::value_type, typename T_Rhs::value_type>& C)
{
	using T_RhsMatrix = typename T_Rhs::value_type;
	T_RhsMatrix B = vR.evaluate();
	VirtualMatrix<T_RhsMatrix> vB(B);
	performVirtualMult(vA, vB, beta, C);
}

template <typename T_Lhs, typename T_Matrix>
void performVirtualMult(
		const VirtualEntity<typename T_Lhs::value_type,T_Lhs>& vL, 
		const VirtualMatrix<T_Matrix>& vB, 
		typename T_Matrix::value_type beta, 
		csc::XxMatrix<typename T_Matrix::index_type, typename T_Matrix::value_type, T_Matrix>& C)
{
	using T_LhsMatrix = typename T_Lhs::value_type;
	T_LhsMatrix A = vL.evaluate();
	VirtualMatrix<T_LhsMatrix> vA(A);
	performVirtualMult(vA, vB, beta, C);
}

template <typename T_Lhs, typename T_Rhs>
void performVirtualMult(
		const VirtualEntity<typename T_Lhs::value_type,T_Lhs>& vL, 
		const VirtualEntity<typename T_Rhs::value_type,T_Rhs>& vR, 
		typename T_Rhs::value_type::value_type beta,
		csc::XxMatrix<typename T_Rhs::value_type::index_type, typename T_Rhs::value_type::value_type, typename T_Rhs::value_type>& C)
{
	using T_LhsMatrix = typename T_Lhs::value_type;
	using T_RhsMatrix = typename T_Rhs::value_type;
	T_LhsMatrix A = vL.evaluate();
	T_RhsMatrix B = vR.evaluate();
	VirtualMatrix<T_LhsMatrix> vA(A);
	VirtualMatrix<T_RhsMatrix> vB(B);
	performVirtualMult(vA, vB, beta, C);
}

/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/

template <typename T_Lhs, typename T_Rhs>
class VirtualProd : public VirtualEntity<typename T_Rhs::value_type,VirtualProd<T_Lhs,T_Rhs>> {

	private:
		using T_Virtual = VirtualProd<T_Lhs,T_Rhs>;
		using T_Object = typename T_Rhs::value_type;
		using T_Scalar = typename T_Object::value_type;

	public:
		explicit VirtualProd(
				const VirtualEntity<typename T_Lhs::value_type,T_Lhs>& lhs, 
				const VirtualEntity<typename T_Rhs::value_type,T_Rhs>& rhs)
			: m_lhs(lhs.self()), m_rhs(rhs.self()) {}

		~VirtualProd() = default;

		const T_Virtual& self() const override { return *this; }
		uint_t size1() const override { return lhs().size1(); }
		uint_t size2() const override { return rhs().size2(); }
		T_Virtual scale(T_Scalar val) const override { return T_Virtual(lhs().scale(val), rhs()); }
		T_Virtual conjugate() const override { return T_Virtual(lhs().conjugate(), rhs().conjugate()); }

		void addToTarget(T_Scalar beta, T_Object& trg) const override
		{
			performVirtualMult(lhs(), rhs(), beta, trg);
		}

	private:
		T_Lhs m_lhs;
		T_Rhs m_rhs;

		const T_Lhs& lhs() const { return m_lhs; }
		const T_Rhs& rhs() const { return m_rhs; }

		T_Lhs& lhs() { return m_lhs; }
		T_Rhs& rhs() { return m_rhs; }
};
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_VIRTUAL_PROD_HPP_
