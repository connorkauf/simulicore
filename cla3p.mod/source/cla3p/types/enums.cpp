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
#include "cla3p/types/enums.hpp"

// system

// 3rd

// cla3p
#include "cla3p/types/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::prop_t& prop)
{
	std::string str = cla3p::msg::Unknown();

	if(prop == cla3p::prop_t::General   ) str = cla3p::msg::General();
	if(prop == cla3p::prop_t::Symmetric ) str = cla3p::msg::Symmetric();
	if(prop == cla3p::prop_t::Hermitian ) str = cla3p::msg::Hermitian();
	if(prop == cla3p::prop_t::Triangular) str = cla3p::msg::Triangular();
	if(prop == cla3p::prop_t::Skew      ) str = cla3p::msg::Skew();

	os << str;
	return os;
}
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::uplo_t& uplo)
{
	std::string str = cla3p::msg::Unknown();

	if(uplo == cla3p::uplo_t::Full ) str = cla3p::msg::Full();
	if(uplo == cla3p::uplo_t::Upper) str = cla3p::msg::Upper();
	if(uplo == cla3p::uplo_t::Lower) str = cla3p::msg::Lower();

	os << str;
	return os;
}
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::op_t& op)
{
	std::string str = cla3p::msg::Unknown();

	if(op == cla3p::op_t::N) str = cla3p::msg::NoOperation();
	if(op == cla3p::op_t::T) str = cla3p::msg::TransposeOperation();
	if(op == cla3p::op_t::C) str = cla3p::msg::ConjugateTransposeOperation();

	os << str;
	return os;
}
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::side_t& side)
{
	std::string str = cla3p::msg::Unknown();

	if(side == cla3p::side_t::Left ) str = cla3p::msg::Left();
	if(side == cla3p::side_t::Right) str = cla3p::msg::Right();

	os << str;
	return os;
}
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const cla3p::decomp_t& decomp)
{
	std::string str = cla3p::msg::Unknown();

	if(decomp == cla3p::decomp_t::Auto       ) str = cla3p::msg::DecompAuto();
	if(decomp == cla3p::decomp_t::LLT        ) str = cla3p::msg::DecompLLt();
	if(decomp == cla3p::decomp_t::LDLT       ) str = cla3p::msg::DecompLDLt();
	if(decomp == cla3p::decomp_t::LU         ) str = cla3p::msg::DecompPartialLU();
	if(decomp == cla3p::decomp_t::CompleteLU ) str = cla3p::msg::DecompCompleteLU();
	if(decomp == cla3p::decomp_t::SymmetricLU) str = cla3p::msg::DecompSymmetricLU();

	os << str;
	return os;
}
/*-------------------------------------------------*/
