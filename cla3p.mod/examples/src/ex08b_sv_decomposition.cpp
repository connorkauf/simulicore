/**
 * @example ex08b_sv_decomposition.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/svd.hpp"

int main()
{
	const cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(5,3);
	const cla3p::dns::RdMatrix B = cla3p::dns::RdMatrix::random(3,5);

	std::cout << "A:\n" << A << "B:\n" << B;

	/*
	 * Set a simple svd object for A
	 */
	cla3p::DefaultSVD<cla3p::dns::RdMatrix> svdA;


	/*
	 * Set a svd object for B with buffer pre-allocation 
	 * and no calculation for V
	 */
	cla3p::svpolicy_t policyU = cla3p::svpolicy_t::Limited;
	cla3p::svpolicy_t policyV = cla3p::svpolicy_t::NoCalculation;
	cla3p::DefaultSVD<cla3p::dns::RdMatrix> svdB(3, 5, policyU, policyV);

	/*
	 * Decompose A & B into USV' products
	 */

	svdA.decompose(A);
	svdB.decompose(B);

	std::cout << "SVD Decomposition of A\n";
	std::cout << "----------------------\n";
	std::cout 
		<< "S:\n" << svdA.singularValues() 
		<< "U:\n" << svdA.leftSingularVectors() 
		<< "V:\n" << svdA.rightSingularVectors();

	std::cout << "SVD Decomposition of B\n";
	std::cout << "----------------------\n";
	std::cout 
		<< "S:\n" << svdB.singularValues() 
		<< "U:\n" << svdB.leftSingularVectors() 
		<< "V(empty):\n" << svdB.rightSingularVectors();

	return 0;
}
