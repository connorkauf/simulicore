#ifndef CLA3P_TESTS_NAIVE_MATRIX_OPS_HPP_
#define CLA3P_TESTS_NAIVE_MATRIX_OPS_HPP_

#include "cla3p/src/types.hpp"

/*-------------------------------------------------*/
using namespace cla3p;
/*-------------------------------------------------*/
void naive_gemm(uint_t m, uint_t n, uint_t k, real_t alpha,
		TransOp opA, const real_t *a, uint_t lda,
		TransOp opB, const real_t *b, uint_t ldb,
		real_t beta, real_t *c, uint_t ldc);
/*-------------------------------------------------*/

#endif // CLA3P_TESTS_NAIVE_MATRIX_OPS_HPP_
