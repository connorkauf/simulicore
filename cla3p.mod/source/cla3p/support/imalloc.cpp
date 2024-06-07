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
#include <cstdlib>

// 3rd

// cla3p
#include "cla3p/error/exceptions.hpp"
#include "cla3p/support/utils.hpp"
#if defined(CLA3P_INTEL_MKL)
#include "cla3p/proxies/mkl_proxy.hpp"
#endif

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
static void check_allocation(const void *ptr, bulk_t nmemb, bulk_t size)
{
	if(!ptr) {
		std::string mem2str = bytesToString(nmemb * size);
		throw err::OutOfMemory("Failed to allocate " + mem2str);
	} // ptr
}
/*-------------------------------------------------*/
void* i2malloc(bulk_t size)
{
	void *ret = nullptr;

	if(!size) return ret;

#if defined(CLA3P_INTEL_MKL)
	ret = mkl::malloc(size);
#else
	ret = std::malloc(size);
#endif

	check_allocation(ret, 1, size);

	return ret;
}
/*-------------------------------------------------*/
void* i2calloc(bulk_t nmemb, bulk_t size)
{
	void *ret = nullptr;

	if(!nmemb || !size) return ret;

#if defined(CLA3P_INTEL_MKL)
	ret = mkl::calloc(nmemb, size);
#else
	ret = std::calloc(nmemb, size);
#endif

	check_allocation(ret, nmemb, size);

	return ret;
}
/*-------------------------------------------------*/
void* i2realloc(void *ptr, bulk_t size)
{
	void *ret = nullptr;

	if(!size){
		i_free(ptr);
		return ret;
	} // empty allocation

#if defined(CLA3P_INTEL_MKL)
	ret = mkl::realloc(ptr, size);
#else
	ret = std::realloc(ptr, size);
#endif

	check_allocation(ret, 1, size);

	return ret;
}
/*-------------------------------------------------*/
void i_free(void *ptr)
{
	if(ptr) {
#if defined(CLA3P_INTEL_MKL)
		mkl::free(ptr);
#else
		std::free(ptr);
#endif
	} // ptr
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
