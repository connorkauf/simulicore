#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/linsol.hpp"
#include "cla3p/operations.hpp"

int main()
{
	const cla3p::dns::RdMatrix A  = cla3p::dns::RdMatrix::random(5,5);
	const cla3p::dns::RdVector B1 = cla3p::dns::RdVector::random(5);
	const cla3p::dns::RdMatrix B2 = cla3p::dns::RdMatrix::random(5,3);

	cla3p::dns::LSolverLU<cla3p::dns::RdMatrix> luSolver;
	luSolver.decompose(A); // decompose A into LU product

	{
		/*
		 * single column (vector) rhs
		 */
		cla3p::dns::RdVector X = B1.copy();
		luSolver.solve(X); // overwrite X with the solution (A^{-1} * B1)
		std::cout << "Absolute error: " << (B1 - A * X).normOne() << std::endl;
	}

	{
		/*
		 * multiple column (matrix) rhs
		 */
		cla3p::dns::RdMatrix X = B2.copy();
		luSolver.solve(X); // overwrite X with the solution (A^{-1} * B2)
		std::cout << "Absolute error: " << (B2 - A * X).normOne() << std::endl;
	}

	return 0;
}
