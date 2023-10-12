#ifndef CLA3P_IMALLOC_HPP_
#define CLA3P_IMALLOC_HPP_

/** 
 * @file
 * Basic allocation features. The behaviour of each function is similar to the ones found in the standard.
 */

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @ingroup allocators
 * @brief The default cla3p allocator.
 *
 * Allocates `size` bytes of uninitialized storage.
 *
 * @param[in] size The requested size in bytes.
 * @return On success, a pointer to the allocated space. Otherwise a null pointer.
 */
void* i_malloc(bulk_t size);

/**
 * @ingroup allocators
 * @brief The default cla3p allocator.
 *
 * Allocates `(nmemb x size)` bytes of uninitialized storage.
 *
 * @param[in] nmemb The number of members to allocate.
 * @param[in] size The size of each member in bytes.
 * @return On success, a pointer to the allocated space. Otherwise a null pointer.
 */
void* i_malloc(bulk_t nmemb, bulk_t size);

/**
 * @ingroup allocators
 * @brief The default cla3p allocator.
 *
 * Allocates `(nmemb x size)` bytes of storage and initializes it to all bits zero.
 *
 * @param[in] nmemb The number of members to allocate.
 * @param[in] size The size of each member in bytes.
 * @return On success, a pointer to the allocated space. Otherwise a null pointer.
 */
void* i_calloc(bulk_t nmemb, bulk_t size);

/**
 * @ingroup allocators
 * @brief Reallocates the given area of memory.
 *
 * @param[in] ptr The pointer to the memory area to be reallocated.
 * @param[in] size The new size of the array.
 * @return On success, a pointer to the beginning of newly allocated memory. Otherwise a null pointer.
 */
void* i_realloc(void *ptr, bulk_t size);

/**
 * @ingroup allocators
 * @brief Reallocates the given area of memory.
 *
 * @param[in] ptr The pointer to the memory area to be reallocated.
 * @param[in] nmemb The new number of members.
 * @param[in] size The new size of each member in bytes.
 * @return On success, a pointer to the beginning of newly allocated memory. Otherwise a null pointer.
 */
void* i_realloc(void *ptr, bulk_t nmemb, bulk_t size);

/**
 * @ingroup allocators
 * @brief The default cla3p deallocator.
 *
 * Deallocates the space previously allocated by i_malloc(), i_calloc(), or i_realloc().
 */
void i_free(void *ptr);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_IMALLOC_HPP_
