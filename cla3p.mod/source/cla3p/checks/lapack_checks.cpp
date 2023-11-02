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
#include "cla3p/checks/lapack_checks.hpp"

// system

// 3rd

// cla3p
#include "cla3p/error/error.hpp"
#include "cla3p/error/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
void lapack_info_check(int_t info)
{
	if(info > 0) {

		// TODO: separate exception for numerical ???
		throw err::Exception(msg::LapackError() + " info: " + std::to_string(info));

	} else if(info < 0) {

		throw err::Exception(msg::LapackError() + " info: " + std::to_string(info));

	}
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
