#ifndef CLA3P_BULK_LOWRANK_HPP_
#define CLA3P_BULK_LOWRANK_HPP_

#include "cla3p/types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace lrk {
/*-------------------------------------------------*/

//
// s: the singular values (descending order)
// ref: a reference value such that
//      if ref < 0 -> atol = tol * s[0]
//      else          atol = tol * ref
//
// return: # of singular values > atol
//
uint_t sv2rank(uint_t n, const real_t *s, real_t tol, real_t ref);

void fr2lr_svd(uint_t m, uint_t n, const real_t *a, uint_t lda, real_t tol, real_t ref);
void fr2lr_qr3(uint_t m, uint_t n, const real_t *a, uint_t lda, real_t tol, real_t ref);

uint_t add_part1(uint_t m, uint_t n, 
		uint_t k1, const real_t *a1, uint_t lda1, const real_t *b1, uint_t ldb1,
		uint_t k2, const real_t *a2, uint_t lda2, const real_t *b2, uint_t ldb2);


/*-------------------------------------------------*/
} // namespace lrk
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BULK_LOWRANK_HPP_
