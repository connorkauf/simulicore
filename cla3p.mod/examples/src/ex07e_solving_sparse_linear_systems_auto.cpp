/**
 * @example ex07e_solving_sparse_linear_systems_auto.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/sparse.hpp"
#include "cla3p/linsol.hpp"
#include "cla3p/algebra.hpp"

/*--------------------------------------------------------------------*/
static cla3p::csc::RdMatrix DefaultSparseMatrix()
{
 static cla3p::int_t  colptr[] = {0, 3, 5, 8, 11, 13};
 static cla3p::int_t  rowidx[] = {0,  1,  3,  0, 1, 2, 3, 4,  0, 2, 3, 1,  4};
 static cla3p::real_t values[] = {1, -1, -3, -2, 5, 4, 6, 4, -4, 2, 7, 8, -5};

 return cla3p::csc::RdMatrix::wrap(5, 5, colptr, rowidx, values, false);
}
/*--------------------------------------------------*/
static cla3p::csc::RdMatrix DefaultSymmetricSparseMatrix()
{
 static cla3p::int_t  colptr[] = {0, 3, 5, 7,  8, 9};
 static cla3p::int_t  rowidx[] = {0,  1,  3, 1, 4, 2, 3, 3,  4};
 static cla3p::real_t values[] = {1, -2, -4, 5, 8, 4, 2, 7, -5};

 return cla3p::csc::RdMatrix::wrap(5, 5, colptr, rowidx, values, false, cla3p::Property::SymmetricLower());
}
/*--------------------------------------------------*/
template <typename T_Rhs>
static void solve_linear_system(const cla3p::csc::RdMatrix& A, const T_Rhs& B)
{
	cla3p::PardisoAuto<cla3p::csc::RdMatrix> autoSolver;

	/*
	 * Perform analysis & symbolic decomposition on A
	 */
	autoSolver.analysis(A);

	/*
	 * Decompose A into a product depending on property
	 */

	autoSolver.decompose(A);

	T_Rhs X;

	/*
	 * Fill X with the solution (A^{-1} * B)
	 */

	autoSolver.solve(B,X);

	std::cout << "  " << cla3p::TypeTraits<T_Rhs>::type_name() << " rhs::";
	std::cout << "Absolute Error: " << (B - A * X).evaluate().normOne() << std::endl;
}
/*--------------------------------------------------------------------*/
int main()
{
	/*
	 * Create a random general matrix
	 */

	const cla3p::csc::RdMatrix Agen = DefaultSparseMatrix();

	/*
	 * Create a random symmetric matrix
	 */

	const cla3p::csc::RdMatrix Asym = DefaultSymmetricSparseMatrix();

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
