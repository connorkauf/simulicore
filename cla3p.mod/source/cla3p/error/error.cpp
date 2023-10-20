/*
 * Copyright (c) 2023-2024 Connor C. Kaufman (connor.kaufman.gh@outlook.com)
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
#include "cla3p/error/error.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace err {
/*-------------------------------------------------*/
Exception::Exception(const std::string& msg)
{
	m_msg = msg;
}
/*-------------------------------------------------*/
Exception::~Exception() throw()
{
}
/*-------------------------------------------------*/
const char* Exception::what() const throw()
{
	return m_msg.c_str();
}
/*-------------------------------------------------*/
NoConsistency::NoConsistency(const std::string& msg)
	: Exception("Consistency error: " + msg)
{
}
/*-------------------------------------------------*/
NoConsistency::~NoConsistency() throw()
{
}
/*-------------------------------------------------*/
InvalidOp::InvalidOp(const std::string& msg)
	: Exception("Invalid operation error: " + msg)
{
}
/*-------------------------------------------------*/
InvalidOp::~InvalidOp() throw()
{
}
/*-------------------------------------------------*/
OutOfMemory::OutOfMemory(const std::string& msg)
	: Exception("Memory error: " + msg)
{
}
/*-------------------------------------------------*/
OutOfMemory::~OutOfMemory() throw()
{
}
/*-------------------------------------------------*/
OutOfBounds::OutOfBounds(const std::string& msg)
	: Exception("Out of bounds error: " + msg)
{
}
/*-------------------------------------------------*/
OutOfBounds::~OutOfBounds() throw()
{
}
/*-------------------------------------------------*/
} // namespace err
} // namespace cla3p
/*-------------------------------------------------*/
