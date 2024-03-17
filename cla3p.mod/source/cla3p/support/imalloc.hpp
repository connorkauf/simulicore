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

#ifndef CLA3P_IMALLOC_HPP_
#define CLA3P_IMALLOC_HPP_

/** 
 * @file
 */

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @ingroup module_index_allocators
 * @brief The default cla3p allocator.
 *
 * Allocates `size` bytes of uninitialized storage.
 *
 * @param[in] size The requested size in bytes.
 * @return On success, a pointer to the allocated space. Otherwise a null pointer.
 */
void* i2malloc(bulk_t size);

/**
 * @ingroup module_index_allocators
 * @brief The default cla3p allocator.
 *
 * Allocates `(nmemb x size)` bytes of storage and initializes it to all bits zero.
 *
 * @param[in] nmemb The number of members to allocate.
 * @param[in] size The size of each member in bytes.
 * @return On success, a pointer to the allocated space. Otherwise a null pointer.
 */
void* i2calloc(bulk_t nmemb, bulk_t size);

/**
 * @ingroup module_index_allocators
 * @brief Reallocates the given area of memory.
 *
 * @param[in] ptr The pointer to the memory area to be reallocated.
 * @param[in] size The new size of the array.
 * @return On success, a pointer to the beginning of newly allocated memory. Otherwise a null pointer.
 */
void* i2realloc(void *ptr, bulk_t size);

/**
 * @ingroup module_index_allocators
 * @brief The templated cla3p allocator.
 *
 * Allocates `(nmemb x sizeof(T))` bytes of uninitialized storage.
 *
 * @param[in] nmemb The number of members to allocate.
 * @return On success, a pointer to the allocated space. Otherwise a null pointer.
 */
template <typename T>
T* i_malloc(bulk_t nmemb)
{
	return static_cast<T*>(i2malloc(nmemb * sizeof(T)));
}

/**
 * @ingroup module_index_allocators
 * @brief The templated cla3p allocator.
 *
 * Allocates `(nmemb x sizeof(T))` bytes of storage and initializes it to all bits zero.
 *
 * @param[in] nmemb The number of members to allocate.
 * @return On success, a pointer to the allocated space. Otherwise a null pointer.
 */
template <typename T>
T* i_calloc(bulk_t nmemb)
{
	return static_cast<T*>(i2calloc(nmemb, sizeof(T)));
}

/**
 * @ingroup module_index_allocators
 * @brief The templated cla3p re-allocator.
 *
 * Reallocates the given area of memory to `(nmemb x sizeof(T))` bytes.
 *
 * @param[in] ptr The pointer to the memory area to be reallocated.
 * @param[in] nmemb The new number of members requested.
 * @return On success, a pointer to the beginning of newly allocated memory. Otherwise a null pointer.
 */
template <typename T>
T* i_realloc(T* ptr, bulk_t nmemb)
{
	return static_cast<T*>(i2realloc(ptr, nmemb * sizeof(T)));
}

/**
 * @ingroup module_index_allocators
 * @brief The default cla3p deallocator.
 *
 * Deallocates the space previously allocated by i_malloc(), i_calloc(), or i_realloc().
 */
void i_free(void *ptr);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_IMALLOC_HPP_
