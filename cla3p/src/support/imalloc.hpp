#ifndef CLA3P_IMALLOC_HPP_
#define CLA3P_IMALLOC_HPP_

/** @file
 * Basic allocation features
 */

#include "../types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @brief The default cla3p allocators
 *
 * Allocates (nmemb x size) bytes of uninitialized storage
 */
void* i_malloc(bulk_t nmemb, bulk_t size);

/**
 * @brief The default cla3p allocators
 *
 * Allocates (nmemb x size) bytes of storage and initializes it to all bits zero
 */
void* i_calloc(bulk_t nmemb, bulk_t size);

/**
 * @brief The default cla3p allocators
 *
 * Reallocates the given area of memory
 */
void* i_realloc(void *ptr, bulk_t nmemb, bulk_t size);

/**
 * @brief The default cla3p deallocator
 *
 * Deallocates the space previously allocated by i_malloc, i_calloc, or i_realloc 
 */
void i_free(void *ptr);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_IMALLOC_HPP_
