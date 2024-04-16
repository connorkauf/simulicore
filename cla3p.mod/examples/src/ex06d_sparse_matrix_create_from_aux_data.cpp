/**
 * @example ex06d_sparse_matrix_create_from_aux_data.cpp
 */

#include <iostream>
#include "cla3p/support.hpp"
#include "cla3p/sparse.hpp"

int main()
{
	/*
	 * Allocate space for two csc matrix representations and assume are filled with some values
	 */

	cla3p::uint_t nr  = 15; // number of rows
	cla3p::uint_t nc  = 12; // number of columns
	cla3p::uint_t nnz = 10; // number of non-zeros

	cla3p::int_t  *colptrA = cla3p::i_calloc<cla3p::int_t >(nc + 1); 
	cla3p::int_t  *rowidxA = cla3p::i_calloc<cla3p::int_t >(nnz); 
	cla3p::real_t *valuesA = cla3p::i_calloc<cla3p::real_t>(nnz); 

	cla3p::int_t  *colptrB = cla3p::i_calloc<cla3p::int_t >(nc + 1); 
	cla3p::int_t  *rowidxB = cla3p::i_calloc<cla3p::int_t >(nnz); 
	cla3p::real_t *valuesB = cla3p::i_calloc<cla3p::real_t>(nnz); 

	/*
	 * Assign csc pointers in matrix A but do not bind
	 * A simply hosts, need to manually dealloc csc vectors
	 */

	cla3p::csc::RdMatrix A = cla3p::csc::RdMatrix::wrap(nr, nc, colptrA, rowidxA, valuesA, false);

	std::cout << A.info("A");

	/*
	 * Assign pointer b in matrix B with property and bind
	 * Assign csc pointers in matrix B with property and bind 
	 * B takes ownership of csc vectors, no free call for the csc vectors is required
	 */

	cla3p::Property prB = cla3p::Property::SymmetricLower();
	cla3p::csc::RdMatrix B = cla3p::csc::RdMatrix::wrap(nc, nc, colptrB, rowidxB, valuesB, true, prB);

	std::cout << B.info("B");

	/* 
	 * Free a and exit
	 */

	cla3p::i_free(colptrA);
	cla3p::i_free(rowidxA);
	cla3p::i_free(valuesA);

	return 0;
}
