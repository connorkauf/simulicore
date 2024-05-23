/**
 * @example ex07b_solving_sparse_linear_systems_llt.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/sparse.hpp"
#include "cla3p/linsol.hpp"
#include "cla3p/algebra.hpp"

/*--------------------------------------------------*/
static cla3p::csc::RdMatrix DefaultSymmetricSparseMatrix()
{
	static cla3p::int_t  colptr[] = {0, 3, 5, 7,  8, 9};
	static cla3p::int_t  rowidx[] = { 0,  1,  3,  1, 4,  2, 3,  3,  4};
	static cla3p::real_t values[] = {10, -2, -4, 50, 8, 40, 2, 70, 50};

	return cla3p::csc::RdMatrix::wrap(5, 5, colptr, rowidx, values, false, cla3p::Property::SymmetricLower());
}
/*--------------------------------------------------*/
int main()
{
	const cla3p::csc::RdMatrix A = DefaultSymmetricSparseMatrix();
	const cla3p::dns::RdVector B1 = cla3p::dns::RdVector::random(5);
	const cla3p::dns::RdMatrix B2 = cla3p::dns::RdMatrix::random(5,3);
	cla3p::dns::RdVector X1; // X1 will be created in solve
	cla3p::dns::RdMatrix X2(5,3); // Preallocate space for X2

	cla3p::PardisoLLt<cla3p::csc::RdMatrix> lltSolver;

	/*
	 * Perform analysis & symbolic decomposition on A
	 */
	lltSolver.analysis(A);

	/*
	 * Decompose A into LL' product
	 */

	lltSolver.decompose(A);

	{
		/*
		 * Single column (vector) rhs
		 * Calculate X1 = (A^{-1} * B1)
		 */

		lltSolver.solve(B1,X1);

		std::cout << "Dense Vector rhs::Absolute Error: "
			<< (B1 - A * X1).evaluate().normOne() << std::endl;
	}

	{
		/*
		 * Multiple column (matrix) rhs
		 * Calculate X2 = (A^{-1} * B2)
		 */

		lltSolver.solve(B2,X2);

		std::cout << "Dense Matrix rhs::Absolute Error: "
			<< (B2 - A * X2).evaluate().normOne() << std::endl;
	}

	return 0;
}
