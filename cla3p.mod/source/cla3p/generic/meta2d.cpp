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
#include "cla3p/generic/meta2d.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
Meta2D::Meta2D()
{
	defaults();
}
/*-------------------------------------------------*/
Meta2D::Meta2D(uint_t m, uint_t n)
{
	wrapper(m, n);
}
/*-------------------------------------------------*/
Meta2D::~Meta2D()
{
	clear();
}
/*-------------------------------------------------*/
uint_t Meta2D::nrows() const
{
	return m_nrows;
}
/*-------------------------------------------------*/
uint_t Meta2D::ncols() const
{
	return m_ncols;
}
/*-------------------------------------------------*/
void Meta2D::setNrows(uint_t m) 
{ 
	m_nrows = m; 
}
/*-------------------------------------------------*/
void Meta2D::setNcols(uint_t n) 
{ 
	m_ncols = n; 
}
/*-------------------------------------------------*/
void Meta2D::wrapper(uint_t m, uint_t n)
{
	setNrows(m);
	setNcols(n);
}
/*-------------------------------------------------*/
bool Meta2D::empty() const
{
	return !(nrows() && ncols());
}
/*-------------------------------------------------*/
bool Meta2D::operator!() const
{
	return empty();
}
/*-------------------------------------------------*/
Meta2D::operator bool() const
{
	return !empty();
}
/*-------------------------------------------------*/
void Meta2D::clear()
{
	defaults();
}
/*-------------------------------------------------*/
void Meta2D::defaults()
{
	setNrows(0);
	setNcols(0);
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
