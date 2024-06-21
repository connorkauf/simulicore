/**
 * @example ex08a_qr_decomposition.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/qr.hpp"

int main()
{
	const cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(5,3);
	const cla3p::dns::RdMatrix B = cla3p::dns::RdMatrix::random(3,5);

	std::cout << "A:\n" << A << "B:\n" << B;

	/*
	 * Set a simple qr object for A
	 */
	cla3p::DefaultQR<cla3p::dns::RdMatrix> qrA;


	/*
	 * Set a qr object for B with buffer pre-allocation
	 * and explicit Q calculation request
	 */
	cla3p::DefaultQR<cla3p::dns::RdMatrix> qrB(3, 5, cla3p::qpolicy_t::Full);

	/*
	 * Decompose A & B into QR products
	 */

	qrA.decompose(A);
	qrB.decompose(B);

	std::cout << "QR Decomposition of A (Q is not explicitly calculated)\n";
	std::cout << "------------------------------------------------------\n";
	std::cout << "Q (empty):\n" << qrA.Q() << "R:\n" << qrA.R();

	std::cout << "QR Decomposition of B (Q is explicitly calculated)\n";
	std::cout << "--------------------------------------------------\n";
	std::cout << "Q:\n" << qrB.Q() << "R:\n" << qrB.R();

	return 0;
}
