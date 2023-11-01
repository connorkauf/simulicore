/**
 * @example ex02d_dense_matrix_create_from_aux_data.cpp
 */

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
	cla3p::real_t *a = 
		static_cast<cla3p::real_t*>(cla3p::i_calloc(lda*4, sizeof(cla3p::real_t))); 
	cla3p::real_t *b = 
		static_cast<cla3p::real_t*>(cla3p::i_calloc(ldb*5, sizeof(cla3p::real_t))); 

	for(cla3p::uint_t j = 0, icnt = 0; j < 4; j++)
		for(cla3p::uint_t i = 0; i < 3; i++)
			a[lda * j + i] = icnt++;

	for(cla3p::uint_t j = 0, icnt = 0; j < 5; j++)
		for(cla3p::uint_t i = j; i < 5; i++)
			b[ldb * j + i] = icnt++;

	/*
	 * Assign pointer a in matrix A but do not bind
	 * A simply hosts a, need to manually dealloc a
	 */

	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::wrap(3, 4, a, lda, false);

	std::cout << A.info("A") << A;

	/*
	 * Assign pointer b in matrix B with property and bind
	 * B takes ownership of b, no free call for b is required
	 */

	cla3p::Property prB(cla3p::prop_t::Symmetric, cla3p::uplo_t::Lower);
	cla3p::dns::RdMatrix B = cla3p::dns::RdMatrix::wrap(5, 5, b, ldb, true, prB);

	std::cout << B.info("B") << B;

	/* 
	 * Free a and exit
	 */

	cla3p::i_free(a);

	return 0;
}
