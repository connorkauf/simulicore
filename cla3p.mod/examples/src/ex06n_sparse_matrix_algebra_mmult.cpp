/**
 * @example ex06n_sparse_matrix_algebra_mmult.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/sparse.hpp"
#include "cla3p/algebra.hpp"

int main()
{
	cla3p::coo::RdMatrix Acoo(5, 5, 10);
	cla3p::coo::RdMatrix Bcoo(5, 3, 10);

	Acoo.insert(0,0,1.0);
	Acoo.insert(1,1,2.0);
	Acoo.insert(2,1,3.0);
	Acoo.insert(1,3,4.0);
	Acoo.insert(0,0,5.0);

	Bcoo.insert(1,2, 1.3);
	Bcoo.insert(2,1,-2.1);
	Bcoo.insert(2,0, 3.5);
	Bcoo.insert(1,1,-4.4);
	Bcoo.insert(0,0, 5.3);

	cla3p::csc::RdMatrix Acsc = Acoo;
	cla3p::csc::RdMatrix Bcsc = Bcoo;

	std::cout << "A (csc):\n" << Acsc << "\n";
	std::cout << "B (csc):\n" << Bcsc << "\n";

	cla3p::dns::RdMatrix Bdns(5,3);

	Bdns = 2.;

	std::cout << "B (dns):\n" << Bdns << "\n";

	/*
	 * Perform the operation (A * B) using operators and the mult function respectively
	 */

	cla3p::op_t opA = cla3p::op_t::N;
	cla3p::op_t opB = cla3p::op_t::N;

	cla3p::dns::RdMatrix C1 = Acsc * Bdns;
	std::cout << "C1 (dns) = A (csc) * B (dns):\n" << C1;

	cla3p::dns::RdMatrix C2 = cla3p::ops::mult(1., opA, Acsc, Bdns);
	std::cout << "C2 (dns) = mult(1.,opA,A(csc),B(dns)):\n" << C2 << "\n";

	cla3p::csc::RdMatrix C3 = Acsc * Bcsc;
	std::cout << "C3 (csc) = A (csc) * B (csc):\n" << C3 << "\n";

	cla3p::csc::RdMatrix C4 = cla3p::ops::mult(1., opA, Acsc, opB, Bcsc);
	std::cout << "C4 (csc) = mult(1.,opA,A(csc),opB,B(csc)):\n" << C4 << "\n";

	/*
	 * Perform the operation (Cx += A * B) using operators and the mult function respectively
	 */

	C1 += Acsc * Bdns;
	std::cout << "C1 (dns) += A (csc) * B (dns):\n" << C1;

	cla3p::ops::mult(1., opA, Acsc, Bdns, C2);
	std::cout << "mult(1,opA,A(csc),B(dns),C2(dns)):\n" << C2;

	C3 += Acsc * Bcsc;
	std::cout << "C3 (csc) += A (csc) * B (csc):\n" << C3 << "\n";

	return 0;
}
