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
#include "cla3p/generic/ownership.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
Ownership::Ownership()
{
	defaults();
}
/*-------------------------------------------------*/
Ownership::~Ownership()
{
}
/*-------------------------------------------------*/
bool Ownership::owner() const 
{
	return m_owner; 
}
/*-------------------------------------------------*/
void Ownership::setOwner(bool owner) 
{ 
	m_owner = owner; 
}
/*-------------------------------------------------*/
void Ownership::clear()
{
	defaults();
}
/*-------------------------------------------------*/
void Ownership::defaults()
{
	setOwner(false);
}
/*-------------------------------------------------*/
void Ownership::unbind()
{
	setOwner(false);
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
