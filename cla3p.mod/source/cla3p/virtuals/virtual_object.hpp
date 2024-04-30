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

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

template <typename T_Vector> class VirtualVector;

/*-------------------------------------------------*/

template <typename T_Object>
class VirtualParams {

	private:
		using T_Scalar = typename T_Object::value_type;

	public:
		VirtualParams(const T_Object&);
		~VirtualParams() = default;
		VirtualParams(const VirtualParams<T_Object>&); // define this to suppress ABI warning

		op_t transOp() const;
		bool conjOp() const;
		T_Scalar coeff() const;
		const T_Object& obj() const;

	protected:
		void iscale(T_Scalar);
		void iconjugate();
		void itranspose();
		void ictranspose();

	private:
		op_t m_transop;
		bool m_conjop;
		T_Scalar m_coeff;
		const T_Object& m_obj;

		void defaults();
		void simplify();

		void setTransOp(op_t transop);
		void setConjOp(bool conjop);
		void setCoeff(T_Scalar coeff);
};

/*-------------------------------------------------*/

template <typename T_Vector>
class VirtualRowVec : public VirtualParams<T_Vector> {

	private:
		using T_Scalar = typename T_Vector::value_type;
		using T_Matrix = typename TypeTraits<T_Vector>::matrix_type;

	public:
		VirtualRowVec(const T_Vector& vec, bool conjop);
		~VirtualRowVec() = default;

		T_Scalar evaluateInner(const VirtualVector<T_Vector>& vY) const;
		T_Matrix evaluateOuter(const VirtualVector<T_Vector>& vX) const;
};

/*-------------------------------------------------*/

template <typename T_Object, typename T_Virtual>
class VirtualObject : 
	public VirtualEntity<T_Object,T_Virtual>,
	public VirtualParams<T_Object> {

	private:
		using T_Scalar = typename T_Object::value_type;

	public:
		explicit VirtualObject(const T_Object&);
		~VirtualObject() = default;

		uint_t size1() const override;
		uint_t size2() const override;
		T_Virtual scale(T_Scalar) const override;
		T_Virtual conjugate() const override;

		bool needsEvaluation() const;
};
/*-------------------------------------------------*/
template <typename T_Vector>
class VirtualVector : public VirtualObject<T_Vector, VirtualVector<T_Vector>> {

	private:
		using T_Scalar = typename T_Vector::value_type;

	public:
		explicit VirtualVector(const T_Vector&);
		~VirtualVector() = default;

		const VirtualVector<T_Vector>& self() const override;
		void addToTarget(T_Scalar, T_Vector&) const override;

		VirtualRowVec<T_Vector> transpose() const;
		VirtualRowVec<T_Vector> ctranspose() const;
};
/*-------------------------------------------------*/
template <typename T_Matrix>
class VirtualMatrix : public VirtualObject<T_Matrix,VirtualMatrix<T_Matrix>> {

	private:
		using T_Scalar = typename T_Matrix::value_type;

	public:
		explicit VirtualMatrix(const T_Matrix&);
		~VirtualMatrix() = default;

		const VirtualMatrix<T_Matrix>& self() const override;
		void addToTarget(T_Scalar, T_Matrix&) const override;

		VirtualMatrix<T_Matrix> transpose() const;
		VirtualMatrix<T_Matrix> ctranspose() const;
};
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_VIRTUAL_OBJECT_HPP_
