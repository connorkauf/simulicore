#ifndef CLA3P_IMALLOC_HPP_
#define CLA3P_IMALLOC_HPP_

#include "types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

void* i_malloc(bulk_t nmemb, bulk_t size);
void* i_calloc(bulk_t nmemb, bulk_t size);
void* i_realloc(void *ptr, bulk_t nmemb, bulk_t size);
void  i_free(void *ptr);

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_IMALLOC_HPP_
