// this file inc
#include "naive_matrix_ops.hpp"

// system

// 3rd

// cla3p
#include "cla3p/src/bulk/dns.hpp"

/*-------------------------------------------------*/
static real_t GetElem(uint_t lda, const real_t *a, uint_t i, uint_t j, op_t op)
{
	real_t ret = 0.;

	/**/ if(op == op_t::N) ret = bulk::dns::entry(lda,a,i,j);
	else if(op == op_t::T) ret = bulk::dns::entry(lda,a,j,i);
	else if(op == op_t::C) ret = bulk::dns::entry(lda,a,j,i);

	return ret;
}
/*-------------------------------------------------*/
void naive_gemm(uint_t m, uint_t n, uint_t k, real_t alpha,
		op_t opA, const real_t *a, uint_t lda,
		op_t opB, const real_t *b, uint_t ldb,
		real_t beta, real_t *c, uint_t ldc)
{
	for(uint_t i = 0; i < m; i++) {
		for(uint_t j = 0; j < n; j++) {
			real_t sum = 0.;
			for(uint_t l = 0; l < k; l++) {
				real_t aa = GetElem(lda,a,i,l,opA);
				real_t bb = GetElem(ldb,b,l,j,opB);
				sum += alpha * aa * bb;
			} // l
			bulk::dns::entry(ldc,c,i,j) = (beta ? bulk::dns::entry(ldc,c,i,j) * beta : 0.);
			bulk::dns::entry(ldc,c,i,j) += sum;
		} // j
	} // i
}
/*-------------------------------------------------*/
