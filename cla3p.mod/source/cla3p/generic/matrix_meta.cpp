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
#include "cla3p/generic/matrix_meta.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
MatrixMeta::MatrixMeta()
{
}
/*-------------------------------------------------*/
MatrixMeta::MatrixMeta(uint_t nr, uint_t nc, const Property& pr)
{
	wrapper(nr, nc, pr);
}
/*-------------------------------------------------*/
MatrixMeta::~MatrixMeta()
{
	clear();
}
/*-------------------------------------------------*/
const Property& MatrixMeta::prop() const
{
	return m_prop;
}
/*-------------------------------------------------*/
Property& MatrixMeta::prop()
{
	return m_prop;
}
/*-------------------------------------------------*/
void MatrixMeta::setProp(const Property& pr) 
{ 
	m_prop = pr; 
}
/*-------------------------------------------------*/
void MatrixMeta::wrapper(uint_t nr, uint_t nc, const Property& pr)
{
	Meta2D::wrapper(nr, nc);
	setProp(pr);
}
/*-------------------------------------------------*/
void MatrixMeta::clear()
{
	Meta2D::clear();
	prop().clear();
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
