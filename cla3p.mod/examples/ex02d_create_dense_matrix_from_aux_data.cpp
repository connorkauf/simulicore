#include <iostream>
#include "cla3p/support.hpp"
#include "cla3p/dense.hpp"

int main()
{
	/*
	 * allocate space for a & b and assume are filled with some values
	 */
	cla3p::uint_t lda = 7;
	cla3p::uint_t ldb = 5;
	cla3p::real_t *a = static_cast<cla3p::real_t*>(cla3p::i_malloc(lda*4)); 
	cla3p::real_t *b = static_cast<cla3p::real_t*>(cla3p::i_malloc(ldb*5)); 

	/*
	 * assign pointer a in matrix A but do not bind (need to manually dealloc a)
	 */
	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::wrap(3, 4, a, lda, false);
	std::cout << A.info() << std::endl;

	/*
	 * assign pointer b in matrix B with property and bind (no free call for b is required)
	 */
	cla3p::Property prB(cla3p::prop_t::SYMMETRIC, cla3p::uplo_t::L);
	cla3p::dns::RdMatrix B = cla3p::dns::RdMatrix::wrap(5, 5, b, ldb, true, prB);
	std::cout << B.info() << std::endl;

	/* 
	 * free a and exit
	 */
	cla3p::i_free(a);

	return 0;
}
