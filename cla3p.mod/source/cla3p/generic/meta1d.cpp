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
#include "cla3p/generic/meta1d.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
Meta1D::Meta1D()
{
	defaults();
}
/*-------------------------------------------------*/
Meta1D::Meta1D(uint_t n)
{
	wrapper(n);
}
/*-------------------------------------------------*/
Meta1D::~Meta1D()
{
	clear();
}
/*-------------------------------------------------*/
uint_t Meta1D::size() const
{
	return m_size;
}
/*-------------------------------------------------*/
void Meta1D::setSize(uint_t n) 
{ 
	m_size = n; 
}
/*-------------------------------------------------*/
void Meta1D::wrapper(uint_t n)
{
	setSize(n);
}
/*-------------------------------------------------*/
bool Meta1D::empty() const
{
	return !size();
}
/*-------------------------------------------------*/
bool Meta1D::operator!() const
{
	return empty();
}
/*-------------------------------------------------*/
Meta1D::operator bool() const
{
	return !empty();
}
/*-------------------------------------------------*/
void Meta1D::clear()
{
	defaults();
}
/*-------------------------------------------------*/
void Meta1D::defaults()
{
	setSize(0);
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
