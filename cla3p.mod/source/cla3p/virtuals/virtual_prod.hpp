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

#include "cla3p/types.hpp"
#include "cla3p/virtuals/virtual_entity.hpp"
#include "cla3p/virtuals/virtual_object.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/
template <typename T_Lhs, typename T_Rhs, typename T_Virtual>
class VirtualProdXx : public VirtualEntity<typename T_Rhs::value_type,T_Virtual> {

	private:
		using T_Object = typename T_Rhs::value_type;
		using T_Scalar = typename T_Object::value_type;

	public:
		explicit VirtualProdXx();
		explicit VirtualProdXx(const T_Lhs& lhs, const T_Rhs& rhs);
		~VirtualProdXx();

		void clear();

		void iscale(T_Scalar val) override;
		void iconjugate() override;

	protected:
		const T_Lhs& lhs() const;
		const T_Rhs& rhs() const;

		T_Lhs& lhs();
		T_Rhs& rhs();

	private:
		T_Lhs m_lhs;
		T_Rhs m_rhs;
};
/*-------------------------------------------------*/
template <typename T_Vector>
class VirtualProdMv : public VirtualProdXx<
											VirtualMatrix<typename TypeTraits<T_Vector>::matrix_type>, 
											VirtualVector<T_Vector>,
											VirtualProdMv<T_Vector>> {

	private:
		using T_Scalar = typename T_Vector::value_type;
		using T_Matrix = typename TypeTraits<T_Vector>::matrix_type;

	public:
		explicit VirtualProdMv();
		explicit VirtualProdMv(const VirtualMatrix<T_Matrix>& lhs, const VirtualVector<T_Vector>& rhs);
		~VirtualProdMv();

		const VirtualProdMv<T_Vector>& self() const override;
		T_Vector evaluate() const override;
		void evaluateOnExisting(T_Vector&) const override;
		void addToExisting(T_Vector&) const override;
};
/*-------------------------------------------------*/
template <typename T_Matrix>
class VirtualProdMm : public VirtualProdXx<
											VirtualMatrix<T_Matrix>, 
											VirtualMatrix<T_Matrix>,
											VirtualProdMm<T_Matrix>> {

	private:
		using T_Scalar = typename T_Matrix::value_type;

	public:
		explicit VirtualProdMm();
		explicit VirtualProdMm(const VirtualMatrix<T_Matrix>& lhs, const VirtualMatrix<T_Matrix>& rhs);
		~VirtualProdMm();

		const VirtualProdMm<T_Matrix>& self() const override;
		T_Matrix evaluate() const override;
		void evaluateOnExisting(T_Matrix&) const override;
		void addToExisting(T_Matrix&) const override;
		operator T_Matrix() const;

		VirtualProdMm<T_Matrix> transpose() const;
		VirtualProdMm<T_Matrix> ctranspose() const;

	private:
		void swap();
};
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_VIRTUAL_PROD_HPP_
