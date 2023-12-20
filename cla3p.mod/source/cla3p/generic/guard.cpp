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
#include "cla3p/generic/guard.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/sparse.hpp"
#include "cla3p/perms.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Object>
Guard<T_Object>::Guard()
{
}
/*-------------------------------------------------*/
template <typename T_Object>
Guard<T_Object>::~Guard()
{
	clear();
}
/*-------------------------------------------------*/
template <typename T_Object>
Guard<T_Object>::Guard(const Guard<T_Object>& other)
{
	m_obj = const_cast<T_Object&>(other.get()).rcopy();
}
/*-------------------------------------------------*/
template <typename T_Object>
Guard<T_Object>& Guard<T_Object>::operator=(const Guard<T_Object>& other)
{
	m_obj = const_cast<T_Object&>(other.get()).rcopy();
	return *this;
}
/*-------------------------------------------------*/
template <typename T_Object>
Guard<T_Object>::Guard(const T_Object& obj)
{
	m_obj = const_cast<T_Object&>(obj).rcopy();
}
/*-------------------------------------------------*/
template <typename T_Object>
void Guard<T_Object>::clear()
{
	m_obj.clear();
}
/*-------------------------------------------------*/
template <typename T_Object>
const T_Object& Guard<T_Object>::get() const
{
	return m_obj;
}
/*-------------------------------------------------*/
template class Guard<dns::RdVector>;
template class Guard<dns::RfVector>;
template class Guard<dns::CdVector>;
template class Guard<dns::CfVector>;
/*-------------------------------------------------*/
template class Guard<dns::RdMatrix>;
template class Guard<dns::RfMatrix>;
template class Guard<dns::CdMatrix>;
template class Guard<dns::CfMatrix>;
/*-------------------------------------------------*/
template class Guard<csc::RdMatrix>;
template class Guard<csc::RfMatrix>;
template class Guard<csc::CdMatrix>;
template class Guard<csc::CfMatrix>;
template class Guard<csc::RdUMatrix>;
template class Guard<csc::RfUMatrix>;
template class Guard<csc::CdUMatrix>;
template class Guard<csc::CfUMatrix>;
/*-------------------------------------------------*/
template class Guard<PiMatrix>;
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
