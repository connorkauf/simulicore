/**
 * @example ex05d_solving_linear_systems_operators.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/linsol.hpp"
#include "cla3p/operations.hpp"

/*--------------------------------------------------------------------*/
template <typename T_rhs>
static void solve_linear_system(const cla3p::dns::RdMatrix& A, const T_rhs& B)
{
	{
		/*
		 * Solve using operator /
		 */

		T_rhs X = B / A;

		std::cout << "  " << cla3p::TypeTraits<T_rhs>::type_name() << " rhs::";
		std::cout << "Absolute error: " << (B - A * X).normOne() << std::endl;
	}

	{
		/*
		 * Solve using operator /=
		 */

		T_rhs X = B.copy();

		X /= A;

		std::cout << "  " << cla3p::TypeTraits<T_rhs>::type_name() << " rhs::";
		std::cout << "Absolute error: " << (B - A * X).normOne() << std::endl;
	}
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

	cla3p::Property prS(cla3p::prop_t::Symmetric, cla3p::uplo_t::Lower);
	const cla3p::dns::RdMatrix Asym = cla3p::dns::RdMatrix::random(5, 5, prS);

	/*
	 * Create a random triangular matrix
	 */

	cla3p::Property prT(cla3p::prop_t::Triangular, cla3p::uplo_t::Upper);
	const cla3p::dns::RdMatrix Atri = cla3p::dns::RdMatrix::random(5, 5, prT);

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

	std::cout << "\nTriangular lhs\n";
	solve_linear_system(Atri, B1);
	solve_linear_system(Atri, B2);

	return 0;
}
/*--------------------------------------------------------------------*/
