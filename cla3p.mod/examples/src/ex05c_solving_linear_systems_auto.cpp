/**
 * @example ex05c_solving_linear_systems_auto.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/linsol.hpp"
#include "cla3p/algebra.hpp"

/*--------------------------------------------------------------------*/
template <typename T_Rhs>
static void solve_linear_system(const cla3p::dns::RdMatrix& A, const T_Rhs& B)
{
	cla3p::dns::LSolverAuto<cla3p::dns::RdMatrix> autoSolver;

	/*
	 * Decompose A into a product depending on property
	 */

	autoSolver.decompose(A);

	T_Rhs X = B;

	/*
	 * Overwrite X with the solution (A^{-1} * B1)
	 */

	autoSolver.solve(X);

	std::cout << "  " << cla3p::TypeTraits<T_Rhs>::type_name() << " rhs::";
	std::cout << "Absolute Error: " << (B - A * X).evaluate().normOne() << std::endl;
}
/*--------------------------------------------------------------------*/
int main()
{
	/*
	 * Create a random general matrix
	 */

	const cla3p::dns::RdMatrix Agen = cla3p::dns::RdMatrix::random(5, 5);

	/*
	 * Create a random symmetric matrix
	 */

	cla3p::Property prA = cla3p::Property::SymmetricLower();
	const cla3p::dns::RdMatrix Asym = cla3p::dns::RdMatrix::random(5, 5, prA);

	/*
	 * Create random right hand sides
	 */

	const cla3p::dns::RdVector B1 = cla3p::dns::RdVector::random(5);
	const cla3p::dns::RdMatrix B2 = cla3p::dns::RdMatrix::random(5, 3);

	std::cout << "General lhs\n";
	solve_linear_system(Agen, B1);
	solve_linear_system(Agen, B2);

	std::cout << "\nSymmetric lhs\n";
	solve_linear_system(Asym, B1);
	solve_linear_system(Asym, B2);

	return 0;
}
/*--------------------------------------------------------------------*/
