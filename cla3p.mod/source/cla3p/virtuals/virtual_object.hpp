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

#ifndef CLA3P_VIRTUAL_OBJECT_HPP_
#define CLA3P_VIRTUAL_OBJECT_HPP_

/**
 * @file
 */

#include "cla3p/types.hpp"
#include "cla3p/virtuals/virtual_entity.hpp"
#include "cla3p/generic/guard.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/
template <typename T_Matrix> class VirtualMatrix;
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
class VirtualObject : public VirtualEntity<T_Object,T_Virtual> {

	private:
		using T_Scalar = typename T_Object::value_type;

	public:
		explicit VirtualObject();
		explicit VirtualObject(const T_Object& obj);
		~VirtualObject();

		void clear();

		void iscale(T_Scalar val) override;
		void iconjugate() override;
		void itranspose();
		void ictranspose();

		T_Virtual transpose() const;
		T_Virtual ctranspose() const;

		op_t transOp() const;
		bool conjOp() const;
		T_Scalar coeff() const;
		const Guard<T_Object>& guard() const;

		const T_Object& obj() const;

	protected:
		void setTransOp(op_t transop);
		void setConjOp(bool conjop);
		void setCoeff(T_Scalar c);
		void setGuard(const Guard<T_Object>& guard);


	private:
		op_t m_transop;
		bool m_conjop;
		T_Scalar m_coeff;
		Guard<T_Object> m_guard;

		void defaults();
		void simplify();
};
/*-------------------------------------------------*/
template <typename T_Vector>
class VirtualVector : public VirtualObject<T_Vector, VirtualVector<T_Vector>> {

	private:
		using T_Scalar = typename T_Vector::value_type;
		using T_Matrix = typename TypeTraits<T_Vector>::matrix_type;

	public:
		using value_type = T_Vector;

		explicit VirtualVector();
		explicit VirtualVector(const T_Vector& vec);
		~VirtualVector();

		const VirtualVector<T_Vector>& self() const override;
		T_Vector evaluate() const override;
		void update(T_Scalar c, T_Vector& Y) const override;
		operator T_Vector() const;

		T_Scalar evaluateInner(const T_Vector& Y) const;
		T_Matrix evaluateOuter(const T_Vector& X) const;
};
/*-------------------------------------------------*/
template <typename T_Matrix>
class VirtualMatrix : public VirtualObject<T_Matrix,VirtualMatrix<T_Matrix>> {

	private:
		using T_Scalar = typename T_Matrix::value_type;
		using T_Vector = typename TypeTraits<T_Matrix>::vector_type;

	public:
		using value_type = T_Matrix;

		explicit VirtualMatrix();
		explicit VirtualMatrix(const T_Matrix& mat);
		explicit VirtualMatrix(const VirtualVector<T_Vector>& v);
		~VirtualMatrix();

		const VirtualMatrix<T_Matrix>& self() const override;
		T_Matrix evaluate() const override;
		void update(T_Scalar c, T_Matrix& B) const override;
		operator T_Matrix() const;
};
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_VIRTUAL_OBJECT_HPP_
