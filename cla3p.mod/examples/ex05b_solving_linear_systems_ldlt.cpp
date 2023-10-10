#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/linsol.hpp"
#include "cla3p/operations.hpp"

int main()
{
	/*
	 * Create a random symmetric matrix
	 */

	cla3p::Property prA(cla3p::prop_t::Symmetric, cla3p::uplo_t::L);
	const cla3p::dns::RdMatrix A  = cla3p::dns::RdMatrix::random(5,5,prA);

	/*
	 * Create random right hand sides
	 */

	const cla3p::dns::RdVector B1 = cla3p::dns::RdVector::random(5);
	const cla3p::dns::RdMatrix B2 = cla3p::dns::RdMatrix::random(5,3);

	cla3p::dns::LSolverLDLt<cla3p::dns::RdMatrix> ldltSolver;
	ldltSolver.decompose(A); // decompose A into LDL' product

	{
		/*
		 * Single column (vector) rhs
		 */

		cla3p::dns::RdVector X = B1.copy();
		ldltSolver.solve(X); // overwrite X with the solution (A^{-1} * B1)
		std::cout << "Absolute error: " << (B1 - A * X).normOne() << std::endl;
	}

	{
		/*
		 * Multiple column (matrix) rhs
		 */

		cla3p::dns::RdMatrix X = B2.copy();
		ldltSolver.solve(X); // overwrite X with the solution (A^{-1} * B2)
		std::cout << "Absolute error: " << (B2 - A * X).normOne() << std::endl;
	}

	return 0;
}
