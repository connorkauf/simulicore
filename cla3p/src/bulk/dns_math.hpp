#ifndef CLA3P_BULK_DNS_MATH_HPP_
#define CLA3P_BULK_DNS_MATH_HPP_

#include "../types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace dns {
/*-------------------------------------------------*/

//
// Update: C += alpha * A
//
#define update_macro(typeout, typein) \
typeout update(uplo_t uplo, uint_t m, uint_t n, typein alpha, const typein *a, uint_t lda, typein *c, uint_t ldc)
update_macro(void, int_t);
update_macro(void, uint_t);
update_macro(void, real_t);
update_macro(void, real4_t);
update_macro(void, complex_t);
update_macro(void, complex8_t);
#undef update_macro

//
// Update: C = alpha * A + beta * B
//
#define add_macro(typeout, typein) \
typeout add(uplo_t uplo, uint_t m, uint_t n, \
		typein alpha, const typein *a, uint_t lda, \
		typein beta , const typein *b, uint_t ldb, typein *c, uint_t ldc)
add_macro(void, int_t);
add_macro(void, uint_t);
add_macro(void, real_t);
add_macro(void, real4_t);
add_macro(void, complex_t);
add_macro(void, complex8_t);
#undef add_macro

//
// Update: y = beta * y + alpha * op(A) * x
//
#define matvec_macro(typeout, typein) \
typeout matvec(prop_t ptype, uplo_t uplo, op_t opA, uint_t m, uint_t n, typein alpha, const typein *a, uint_t lda, const typein *x, typein beta, typein *y)
matvec_macro(void, int_t);
matvec_macro(void, uint_t);
matvec_macro(void, real_t);
matvec_macro(void, real4_t);
matvec_macro(void, complex_t);
matvec_macro(void, complex8_t);
#undef matvec_macro

//
// Update: C = beta * C + alpha * opA(A) * opB(B)
//
#define gematmat_macro(typeout, typein) \
typeout gematmat(uint_t m, uint_t n, uint_t k, typein alpha, \
		op_t opA, const typein *a, uint_t lda, \
		op_t opB, const typein *b, uint_t ldb, \
		typein beta, typein *c, uint_t ldc)
gematmat_macro(void, int_t);
gematmat_macro(void, uint_t);
gematmat_macro(void, real_t);
gematmat_macro(void, real4_t);
gematmat_macro(void, complex_t);
gematmat_macro(void, complex8_t);
#undef gematmat_macro

/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BULK_DNS_MATH_HPP_
