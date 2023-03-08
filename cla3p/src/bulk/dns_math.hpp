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
// C(m x n)
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
// C(m x n)
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
// A(m x n)
//
#define gem_x_vec_macro(typeout, typein) \
typeout gem_x_vec(op_t opA, uint_t m, uint_t n, typein alpha, const typein *a, uint_t lda, const typein *x, typein beta, typein *y)
gem_x_vec_macro(void, int_t);
gem_x_vec_macro(void, uint_t);
gem_x_vec_macro(void, real_t);
gem_x_vec_macro(void, real4_t);
gem_x_vec_macro(void, complex_t);
gem_x_vec_macro(void, complex8_t);
#undef gem_x_vec_macro

//
// Update: y = beta * y + alpha * A * x
//
#define sym_x_vec_macro(typeout, typein) \
typeout sym_x_vec(uplo_t uplo, uint_t n, typein alpha, const typein *a, uint_t lda, const typein *x, typein beta, typein *y)
sym_x_vec_macro(void, int_t);
sym_x_vec_macro(void, uint_t);
sym_x_vec_macro(void, real_t);
sym_x_vec_macro(void, real4_t);
sym_x_vec_macro(void, complex_t);
sym_x_vec_macro(void, complex8_t);
#undef sym_x_vec_macro

//
// Update: y = beta * y + alpha * A * x
//
#define hem_x_vec_macro(typeout, typein) \
typeout hem_x_vec(uplo_t uplo, uint_t n, typein alpha, const typein *a, uint_t lda, const typein *x, typein beta, typein *y)
hem_x_vec_macro(void, int_t); // exception
hem_x_vec_macro(void, uint_t); // exception
hem_x_vec_macro(void, real_t); // exception
hem_x_vec_macro(void, real4_t); // exception
hem_x_vec_macro(void, complex_t);
hem_x_vec_macro(void, complex8_t);
#undef hem_x_vec_macro

//
// Update: C = beta * C + alpha * opA(A) * opB(B)
// C(m x n)
//
#define gem_x_gem_macro(typeout, typein) \
typeout gem_x_gem(uint_t m, uint_t n, uint_t k, typein alpha, \
		op_t opA, const typein *a, uint_t lda, \
		op_t opB, const typein *b, uint_t ldb, \
		typein beta, typein *c, uint_t ldc)
gem_x_gem_macro(void, int_t);
gem_x_gem_macro(void, uint_t);
gem_x_gem_macro(void, real_t);
gem_x_gem_macro(void, real4_t);
gem_x_gem_macro(void, complex_t);
gem_x_gem_macro(void, complex8_t);
#undef gem_x_gem_macro

//
// Update: C = beta * C + alpha * A * B
// C(m x n)
//
#define sym_x_gem_macro(typeout, typein) \
typeout sym_x_gem(uplo_t uplo, uint_t m, uint_t n, typein alpha, \
		const typein *a, uint_t lda, \
		const typein *b, uint_t ldb, \
		typein beta, typein *c, uint_t ldc)
sym_x_gem_macro(void, int_t);
sym_x_gem_macro(void, uint_t);
sym_x_gem_macro(void, real_t);
sym_x_gem_macro(void, real4_t);
sym_x_gem_macro(void, complex_t);
sym_x_gem_macro(void, complex8_t);
#undef sym_x_gem_macro

//
// Update: C = beta * C + alpha * B * A
// C(m x n)
//
#define gem_x_sym_macro(typeout, typein) \
typeout gem_x_sym(uplo_t uplo, uint_t m, uint_t n, typein alpha, \
		const typein *a, uint_t lda, \
		const typein *b, uint_t ldb, \
		typein beta, typein *c, uint_t ldc)
gem_x_sym_macro(void, int_t);
gem_x_sym_macro(void, uint_t);
gem_x_sym_macro(void, real_t);
gem_x_sym_macro(void, real4_t);
gem_x_sym_macro(void, complex_t);
gem_x_sym_macro(void, complex8_t);
#undef gem_x_sym_macro

//
// Update: C = beta * C + alpha * A * B
// C(m x n)
//
#define hem_x_gem_macro(typeout, typein) \
typeout hem_x_gem(uplo_t uplo, uint_t m, uint_t n, typein alpha, \
		const typein *a, uint_t lda, \
		const typein *b, uint_t ldb, \
		typein beta, typein *c, uint_t ldc)
hem_x_gem_macro(void, int_t); // exception
hem_x_gem_macro(void, uint_t); // exception
hem_x_gem_macro(void, real_t); // exception
hem_x_gem_macro(void, real4_t); // exception
hem_x_gem_macro(void, complex_t);
hem_x_gem_macro(void, complex8_t);
#undef hem_x_gem_macro

//
// Update: C = beta * C + alpha * B * A
// C(m x n)
//
#define gem_x_hem_macro(typeout, typein) \
typeout gem_x_hem(uplo_t uplo, uint_t m, uint_t n, typein alpha, \
		const typein *a, uint_t lda, \
		const typein *b, uint_t ldb, \
		typein beta, typein *c, uint_t ldc)
gem_x_hem_macro(void, int_t); // exception
gem_x_hem_macro(void, uint_t); // exception
gem_x_hem_macro(void, real_t); // exception
gem_x_hem_macro(void, real4_t); // exception
gem_x_hem_macro(void, complex_t);
gem_x_hem_macro(void, complex8_t);
#undef gem_x_hem_macro

/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BULK_DNS_MATH_HPP_
