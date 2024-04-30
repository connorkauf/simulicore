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

#ifndef CLA3P_VIRTUAL_SUM_HPP_
#define CLA3P_VIRTUAL_SUM_HPP_

/**
 * @file
 */

#include "cla3p/types.hpp"
#include "cla3p/virtuals/virtual_entity.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/
template <typename T_Object, typename T_Lhs, typename T_Rhs>
class VirtualSum : public VirtualEntity<T_Object,VirtualSum<T_Object,T_Lhs,T_Rhs>>{

	private:
		using T_Virtual = VirtualSum<T_Object,T_Lhs,T_Rhs>;
		using T_Scalar = typename T_Object::value_type;

	public:
		explicit VirtualSum(
				const VirtualEntity<T_Object,T_Lhs>& lhs, 
				const VirtualEntity<T_Object,T_Rhs>& rhs)
			: m_lhs(lhs.self()), m_rhs(rhs.self()) {}
		~VirtualSum() = default;

		const T_Virtual& self() const override { return *this; }
		uint_t size1() const override { return lhs().size1(); }
		uint_t size2() const override { return lhs().size2(); }
		T_Virtual scale(T_Scalar val) const override { return T_Virtual(lhs().scale(val), rhs().scale(val)); }
		T_Virtual conjugate() const override { return T_Virtual(lhs().conjugate(), rhs().conjugate()); }

		void addToTarget(T_Scalar beta, T_Object& trg) const override
		{
			lhs().addToTarget(beta, trg);
			rhs().addToTarget(T_Scalar(1), trg);
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

#endif // CLA3P_VIRTUAL_SUM_HPP_
