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
#include "cla3p/support/rand.hpp"

// system
#include <cstdlib>

// 3rd

// cla3p
#include "cla3p/error/exceptions.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Int>
static T_Int randomCaseInt(T_Int lo, T_Int hi)
{
	T_Int diff = hi - lo;
	T_Int stdRandVal = std::rand();
	T_Int inc = stdRandVal % diff;
	return (lo + inc);
}
/*-------------------------------------------------*/
template int_t  randomCaseInt(int_t , int_t );
template uint_t randomCaseInt(uint_t, uint_t);
/*-------------------------------------------------*/
template <typename T_Scalar>
static T_Scalar randomCaseReal(T_Scalar lo, T_Scalar hi)
{
  T_Scalar diff = hi - lo;
	T_Scalar stdRandVal = static_cast<T_Scalar>(std::rand());
  T_Scalar inc = diff * (stdRandVal / static_cast<T_Scalar>(RAND_MAX + 1U));
	return (lo + inc);
}
/*-------------------------------------------------*/
template real_t  randomCaseReal(real_t , real_t );
template real4_t randomCaseReal(real4_t, real4_t);
/*-------------------------------------------------*/
template <typename T_Scalar>
static T_Scalar randomCaseComplex(
		typename TypeTraits<T_Scalar>::real_type lo, 
		typename TypeTraits<T_Scalar>::real_type hi)
{
	return T_Scalar(randomCaseReal(lo,hi), randomCaseReal(lo,hi));
}
/*-------------------------------------------------*/
template complex_t  randomCaseComplex(real_t , real_t );
template complex8_t randomCaseComplex(real4_t, real4_t);
/*-------------------------------------------------*/
template <typename T_Scalar>
static T_Scalar randomCase(
		typename TypeTraits<T_Scalar>::real_type lo,
		typename TypeTraits<T_Scalar>::real_type hi);
/*-------------------------------------------------*/
template<> int_t  randomCase<int_t >(int_t  lo, int_t  hi) { return randomCaseInt<int_t >(lo,hi); }
template<> uint_t randomCase<uint_t>(uint_t lo, uint_t hi) { return randomCaseInt<uint_t>(lo,hi); }
/*-------------------------------------------------*/
template<> real_t  randomCase<real_t >(real_t  lo, real_t  hi) { return randomCaseReal<real_t >(lo,hi); }
template<> real4_t randomCase<real4_t>(real4_t lo, real4_t hi) { return randomCaseReal<real4_t>(lo,hi); }
/*-------------------------------------------------*/
template<> complex_t  randomCase<complex_t >(real_t  lo, real_t  hi) { return randomCaseComplex<complex_t >(lo,hi); }
template<> complex8_t randomCase<complex8_t>(real4_t lo, real4_t hi) { return randomCaseComplex<complex8_t>(lo,hi); }
/*-------------------------------------------------*/
template <typename T_Scalar>
T_Scalar rand(
		typename TypeTraits<T_Scalar>::real_type lo,
		typename TypeTraits<T_Scalar>::real_type hi)
{
	if(lo > hi)
		throw err::Exception("Need lo <= hi");

	return randomCase<T_Scalar>(lo,hi);
}
/*-------------------------------------------------*/
template int_t      rand(int_t  , int_t  );
template uint_t     rand(uint_t , uint_t );
template real_t     rand(real_t , real_t );
template real4_t    rand(real4_t, real4_t);
template complex_t  rand(real_t , real_t );
template complex8_t rand(real4_t, real4_t);
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
