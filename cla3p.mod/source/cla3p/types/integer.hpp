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

#ifndef CLA3P_INTEGER_HPP_
#define CLA3P_INTEGER_HPP_

/** 
 * @file
 */

#include <string>

#include "cla3p/generic/type_traits.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

#if defined (CLA3P_I64)
#define _DFMT_ "lld"
#define _UFMT_ "llu"
using int_t = long long int;
using uint_t = unsigned long long int;
#else
#define _DFMT_ "d"
#define _UFMT_ "u"
using int_t = int;
using uint_t = unsigned int;
#endif

using nint_t = int;

/**
 * @ingroup cla3p_module_index_datatypes
 * @brief Standard indexing.
 */
using bulk_t = std::size_t;

/*-------------------------------------------------*/

template<> class TypeTraits<int_t> {
	public:
		using real_type = int_t;
		static std::string type_name();
		static std::string prec_name();
		static int_t epsilon();
};

template<> class TypeTraits<uint_t> {
	public:
		using real_type = uint_t;
		static std::string type_name();
		static std::string prec_name();
		static uint_t epsilon();
};

/*-------------------------------------------------*/

namespace arith {
inline int_t conj(const int_t& i) { return i; }
inline uint_t conj(const uint_t& u) { return u; }

inline int_t getRe(const int_t& i) { return i; }
inline uint_t getRe(const uint_t& u) { return u; }

inline int_t getIm(const int_t&) { return 0; }
inline uint_t getIm(const uint_t&) { return 0; }

inline void setIm(int_t&, int_t) { }
inline void setIm(uint_t&, uint_t) { }
} // namespace arith

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_INTEGER_HPP_
