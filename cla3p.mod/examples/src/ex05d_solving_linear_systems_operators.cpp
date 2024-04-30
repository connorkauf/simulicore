/**
 * @example ex05d_solving_linear_systems_operators.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/linsol.hpp"
#include "cla3p/algebra.hpp"

/*--------------------------------------------------------------------*/
template <typename T_Rhs>
static void solve_linear_system(const cla3p::dns::RdMatrix& A, const T_Rhs& B)
{
	{
		/*
		 * Solve using operator /
		 */

		T_Rhs X = A / B;

		std::cout << "  " << cla3p::TypeTraits<T_Rhs>::type_name() << " rhs::";
		std::cout << "Absolute error: " << (B - A * X).evaluate().normOne() << std::endl;
	}

	{
		/*
		 * Solve using operator /=
		 */

		T_Rhs X = B;

		X /= A;

		std::cout << "  " << cla3p::TypeTraits<T_Rhs>::type_name() << " rhs::";
		std::cout << "Absolute error: " << (B - A * X).evaluate().normOne() << std::endl;
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

	cla3p::Property prS = cla3p::Property::SymmetricLower();
	const cla3p::dns::RdMatrix Asym = cla3p::dns::RdMatrix::random(5, 5, prS);

	/*
	 * Create a random triangular matrix
	 */

	cla3p::Property prT = cla3p::Property::TriangularUpper();
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
