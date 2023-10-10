#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/linsol.hpp"
#include "cla3p/operations.hpp"

/*--------------------------------------------------------------------*/
template <typename T_rhs>
static void solve_linear_system(const cla3p::dns::RdMatrix& A, const T_rhs& B)
{
	cla3p::dns::LSolverAuto<cla3p::dns::RdMatrix> autoSolver;
	autoSolver.decompose(A); // decompose A into a product depending on property

	T_rhs X = B.copy();
	autoSolver.solve(X); // overwrite X with the solution (A^{-1} * B1)
	std::cout << "Absolute error: " << (B - A * X).normOne() << std::endl;
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

	cla3p::Property prA(cla3p::prop_t::Symmetric, cla3p::uplo_t::L);
	const cla3p::dns::RdMatrix Asym = cla3p::dns::RdMatrix::random(5, 5, prA);

	/*
	 * Create random right hand sides
	 */

	const cla3p::dns::RdVector B1 = cla3p::dns::RdVector::random(5);
	const cla3p::dns::RdMatrix B2 = cla3p::dns::RdMatrix::random(5, 3);

	solve_linear_system(Agen, B1);
	solve_linear_system(Agen, B2);
	solve_linear_system(Asym, B1);
	solve_linear_system(Asym, B2);

	return 0;
}
/*--------------------------------------------------------------------*/
