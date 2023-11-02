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
#include "cla3p/support/imalloc.hpp"

// system

// 3rd
#include <mkl_service.h>

// cla3p
#include "cla3p/error/error.hpp"
#include "cla3p/support/utils.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
#define MKL_ALLOC_ALIGNMENT 64
/*-------------------------------------------------*/
static void check_allocation(const void *ptr, bulk_t nmemb, bulk_t size)
{
	if(!ptr) {
		std::string mem2str = bytes2human(nmemb * size);
		throw err::OutOfMemory("Failed to allocate " + mem2str);
	} // ptr
}
/*-------------------------------------------------*/
void* i_malloc(bulk_t nmemb, bulk_t size)
{
	return i_malloc(nmemb * size);
}
/*-------------------------------------------------*/
void* i_malloc(bulk_t size)
{
	void *ret = nullptr;

	if(!size) return ret;

	ret = mkl_malloc(size, MKL_ALLOC_ALIGNMENT);

	check_allocation(ret, 1, size);

	return ret;
}
/*-------------------------------------------------*/
void* i_calloc(bulk_t nmemb, bulk_t size)
{
	void *ret = nullptr;

	if(!nmemb || !size) return ret;

	ret = mkl_calloc(nmemb, size, MKL_ALLOC_ALIGNMENT);

	check_allocation(ret, nmemb, size);

	return ret;
}
/*-------------------------------------------------*/
void* i_realloc(void *ptr, bulk_t size)
{
	void *ret = nullptr;

	if(!size){
		i_free(ptr);
		return ret;
	} // empty allocation

	ret = mkl_realloc(ptr, size);

	check_allocation(ret, 1, size);

	return ret;
}
/*-------------------------------------------------*/
void* i_realloc(void *ptr, bulk_t nmemb, bulk_t size)
{
	return i_realloc(ptr, nmemb * size);
}
/*-------------------------------------------------*/
void i_free(void *ptr)
{
	if(ptr) {
		mkl_free(ptr);
	} // ptr
}
/*-------------------------------------------------*/
#undef MKL_ALLOC_ALIGNMENT
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
