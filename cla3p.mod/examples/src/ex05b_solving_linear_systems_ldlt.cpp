/**
 * @example ex05b_solving_linear_systems_ldlt.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/linsol.hpp"
#include "cla3p/algebra.hpp"

int main()
{
	/*
	 * Create a random symmetric matrix
	 */

	cla3p::Property prA = cla3p::Property::SymmetricLower();
	const cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(5,5,prA);

	/*
	 * Create random right hand sides
	 */

	const cla3p::dns::RdVector B1 = cla3p::dns::RdVector::random(5);
	const cla3p::dns::RdMatrix B2 = cla3p::dns::RdMatrix::random(5,3);

	cla3p::LapackLDLt<cla3p::dns::RdMatrix> ldltSolver;

	/*
	 * Decompose A into LDL' product
	 */

	ldltSolver.decompose(A);

	{
		/*
		 * Single column (vector) rhs
		 * Overwrite X with the solution (A^{-1} * B1)
		 */

		cla3p::dns::RdVector X = B1;

		ldltSolver.solve(X);

		std::cout << "Dense Vector rhs::Absolute Error: " 
			<< (B1 - A * X).evaluate().normOne() << std::endl;
	}

	{
		/*
		 * Multiple column (matrix) rhs
		 * Overwrite X with the solution (A^{-1} * B2)
		 */

		cla3p::dns::RdMatrix X = B2;

		ldltSolver.solve(X);

		std::cout << "Dense Matrix rhs::Absolute Error: " 
			<< (B2 - A * X).evaluate().normOne() << std::endl;
	}

	return 0;
}
