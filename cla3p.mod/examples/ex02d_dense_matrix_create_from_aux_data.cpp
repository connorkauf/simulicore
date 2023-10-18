#include <iostream>
#include "cla3p/support.hpp"
#include "cla3p/dense.hpp"

int main()
{
	/*
	 * Allocate space for a & b and assume are filled with some values
	 * Values in a and b are assumed to be in column-major order
	 */

	cla3p::uint_t lda = 7;
	cla3p::uint_t ldb = 5;
	cla3p::real_t *a = static_cast<cla3p::real_t*>(cla3p::i_calloc(lda*4, sizeof(cla3p::real_t))); 
	cla3p::real_t *b = static_cast<cla3p::real_t*>(cla3p::i_calloc(ldb*5, sizeof(cla3p::real_t))); 

	/*
	 * Assign pointer a in matrix A but do not bind
	 * A simply hosts a, need to manually dealloc a
	 */

	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::wrap(3, 4, a, lda, false);
	std::cout << A.info() << std::endl;

	/*
	 * Assign pointer b in matrix B with property and bind
	 * B takes ownership of b, no free call for b is required
	 */

	cla3p::Property prB(cla3p::prop_t::Symmetric, cla3p::uplo_t::Lower);
	cla3p::dns::RdMatrix B = cla3p::dns::RdMatrix::wrap(5, 5, b, ldb, true, prB);
	std::cout << B.info() << std::endl;

	/* 
	 * Free a and exit
	 */

	cla3p::i_free(a);

	return 0;
}
