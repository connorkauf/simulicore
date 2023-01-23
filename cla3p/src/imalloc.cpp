// this file inc
#include "imalloc.hpp"

// system

// 3rd
#include <mkl_service.h>

// cla3p
#include "error.hpp"
#include "utils.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
#define MKL_ALLOC_ALIGNMENT 64
/*-------------------------------------------------*/
static void check_allocation(const void *ptr, bulk_t nmemb, bulk_t size)
{
	if(!ptr) {
		std::string mem2str = bytes2human(nmemb * size);
		throw OutOfMemory("Failed to allocate " + mem2str);
	} // ptr
}
/*-------------------------------------------------*/
void* i_malloc(bulk_t nmemb, bulk_t size)
{
	void *ret = nullptr;

	if(!nmemb || !size) return ret;

	ret = mkl_malloc(nmemb * size, MKL_ALLOC_ALIGNMENT);

	check_allocation(ret, nmemb, size);

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
void* i_realloc(void *ptr, bulk_t nmemb, bulk_t size)
{
	void *ret = nullptr;

	if(!nmemb || !size){
		i_free(ptr);
		return ret;
	} // empty allocation

	ret = mkl_realloc(ptr, nmemb * size);

	check_allocation(ret, nmemb, size);

	return ret;
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
