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

// this file inc
#include "cla3p/perms/pxmatrix.hpp"

// system
#include <algorithm>

// 3rd

// cla3p
#include "cla3p/support/rand.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace prm {
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int>::PxMatrix()
{
}
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int>::PxMatrix(uint_t n)
	: dns::XiVector<T_Int,PxMatrix<T_Int>>(n)
{
}
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int>::~PxMatrix()
{
}
/*-------------------------------------------------*/
template <typename T_Int>
void PxMatrix<T_Int>::operator=(T_Int val)
{
	this->fill(val);
}
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int> PxMatrix<T_Int>::inverse() const
{
	PxMatrix<T_Int> ret(this->size());

	for(uint_t i = 0; i < this->size(); i++) {
		ret((*this)(i)) = i;
	} // i

	return ret;
}
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int> PxMatrix<T_Int>::permuteLeft(const PxMatrix<T_Int>& P) const
{
	PxMatrix<T_Int> ret(this->size());

	for(uint_t i = 0; i < this->size(); i++) {
		ret(i) = P((*this)(i));
	} // i

	return ret;
}
/*-------------------------------------------------*/
template <typename T_Int>
static void fill_identity_permutation(uint_t n, T_Int *P)
{
	for(uint_t i = 0; i < n; i++) {
		P[i] = static_cast<T_Int>(i);
	} // i
}
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int> PxMatrix<T_Int>::identity(uint_t n)
{
	PxMatrix<T_Int> ret(n);
	fill_identity_permutation(ret.size(), ret.values());
	return ret;
}
/*-------------------------------------------------*/
template <typename T_Int>
static void fill_random_permutation(uint_t n, T_Int *P)
{
	if(!n) return;

	fill_identity_permutation(n, P);

	uint_t ilen = n;
	for(uint_t i = 0; i < n - 1; i++) {
		uint_t k = rand<T_Int>(0, ilen-1);
		std::swap(P[k], P[ilen-1]);
		ilen--;
	} // i
}
/*-------------------------------------------------*/
template <typename T_Int>
PxMatrix<T_Int> PxMatrix<T_Int>::random(uint_t n)
{
	PxMatrix<T_Int> ret(n);
	fill_random_permutation(ret.size(), ret.values());
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class PxMatrix<int_t>;
/*-------------------------------------------------*/
} // namespace prm
} // namespace cla3p
/*-------------------------------------------------*/
