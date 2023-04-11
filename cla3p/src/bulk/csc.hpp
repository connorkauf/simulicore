#ifndef CLA3P_BULK_CSC_HPP_
#define CLA3P_BULK_CSC_HPP_

#include <string>

#include "../types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace csc {
/*-------------------------------------------------*/

void roll(uint_t n, uint_t *colptr);
void unroll(uint_t n, uint_t *colptr);

uint_t maxrlen(uint_t n, const uint_t *colptr);

void sort_by_ridx(uint_t n, const uint_t *colptr, uint_t *rowidx);

#define sort_by_ridx_macro(typeout, typein) \
typeout sort_by_ridx(uint_t n, const uint_t *colptr, uint_t *rowidx, typein *values)
sort_by_ridx_macro(void, int_t);
sort_by_ridx_macro(void, uint_t);
sort_by_ridx_macro(void, real_t);
sort_by_ridx_macro(void, real4_t);
sort_by_ridx_macro(void, complex_t);
sort_by_ridx_macro(void, complex8_t);
#undef sort_by_ridx_macro

#define print_to_string_macro(typeout, typein, sd) \
typeout print_to_string(uint_t n, const uint_t *colptr, const uint_t *rowidx, const typein *values, uint_t nsd = sd)
print_to_string_macro(std::string, int_t     , 0);
print_to_string_macro(std::string, uint_t    , 0);
print_to_string_macro(std::string, real_t    , 3);
print_to_string_macro(std::string, real4_t   , 3);
print_to_string_macro(std::string, complex_t , 3);
print_to_string_macro(std::string, complex8_t, 3);
#undef print_to_string_macro

#define print_macro(typeout, typein, sd) \
typeout print(uint_t n, const uint_t *colptr, const uint_t *rowidx, const typein *values, uint_t nsd = sd)
print_macro(void, int_t     , 0);
print_macro(void, uint_t    , 0);
print_macro(void, real_t    , 3);
print_macro(void, real4_t   , 3);
print_macro(void, complex_t , 3);
print_macro(void, complex8_t, 3);
#undef print_macro

#define transpose_macro(typeout, typein) \
typeout transpose(uint_t m, uint_t n, const uint_t *colptr, const uint_t *rowidx, const typein *values, \
		uint_t *colptr_out, uint_t *rowidx_out, typein *values_out, typein coeff = 1)
transpose_macro(void, int_t);
transpose_macro(void, uint_t);
transpose_macro(void, real_t);
transpose_macro(void, real4_t);
transpose_macro(void, complex_t);
transpose_macro(void, complex8_t);
#undef transpose_macro

#define conjugate_transpose_macro(typeout, typein) \
typeout conjugate_transpose(uint_t m, uint_t n, const uint_t *colptr, const uint_t *rowidx, const typein *values, \
		uint_t *colptr_out, uint_t *rowidx_out, typein *values_out, typein coeff = 1)
conjugate_transpose_macro(void, int_t); // exception
conjugate_transpose_macro(void, uint_t); // exception
conjugate_transpose_macro(void, real_t); // exception
conjugate_transpose_macro(void, real4_t); // exception
conjugate_transpose_macro(void, complex_t);
conjugate_transpose_macro(void, complex8_t);
#undef conjugate_transpose_macro

void uplo2ge_colptr(uplo_t uplo, uint_t n, const uint_t *colptr, const uint_t *rowidx, uint_t *colptr_out);

#define sy2ge_macro(typeout, typein) \
typeout sy2ge(uplo_t uplo, uint_t n, const uint_t *colptr, const uint_t *rowidx, const typein *values, \
		uint_t *colptr_out, uint_t *rowidx_out, typein *values_out)
sy2ge_macro(void, int_t);
sy2ge_macro(void, uint_t);
sy2ge_macro(void, real_t);
sy2ge_macro(void, real4_t);
sy2ge_macro(void, complex_t);
sy2ge_macro(void, complex8_t);
#undef sy2ge_macro

#define he2ge_macro(typeout, typein) \
typeout he2ge(uplo_t uplo, uint_t n, const uint_t *colptr, const uint_t *rowidx, const typein *values, \
		uint_t *colptr_out, uint_t *rowidx_out, typein *values_out)
he2ge_macro(void, int_t); // exception
he2ge_macro(void, uint_t); // exception
he2ge_macro(void, real_t); // exception
he2ge_macro(void, real4_t); // exception
he2ge_macro(void, complex_t);
he2ge_macro(void, complex8_t);
#undef he2ge_macro

// FIXME: move this to types or whatever
enum class dup_t {
	SUM  = 0,
	PROD    ,
	AMAX    ,
	AMIN     
};

#define remove_duplicates_macro(typeout, typein) \
typeout remove_duplicates(uint_t n, uint_t *colptr, uint_t *rowidx, typein *values, dup_t op)
remove_duplicates_macro(void, int_t);
remove_duplicates_macro(void, real_t);
remove_duplicates_macro(void, real4_t);
remove_duplicates_macro(void, complex_t);
remove_duplicates_macro(void, complex8_t);
#undef remove_duplicates_macro

/*-------------------------------------------------*/
} // namespace csc
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BULK_CSC_HPP_
