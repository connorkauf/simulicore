/**
 * @example ex02i_dense_matrix_block_operations.cpp
 */

#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	cla3p::dns::RdMatrix A(5,5);

	for(cla3p::uint_t j = 0, icnt = 0; j < 5; j++)
		for(cla3p::uint_t i = 0; i < 5; i++)
			A(i,j) = icnt++;

	std::cout << "A:\n" << A << "\n";

	/*
	 * Get a (2x2) copy of the contents of A starting at (1,2)
	 * Get a (3x2) reference of the contents of A starting at (2,0)
	 */

	cla3p::dns::RdMatrix Ab = A.block(1, 2, 2, 2);
	cla3p::dns::RdMatrix Ar = A.rblock(2, 0, 3, 2);

	std::cout << "Ab:\n" << Ab;
	std::cout << "Ar:\n" << Ar;

	/*
	 * Get a (3x2) guarded reference of the contents of Aref starting at (2,0)
	 */

	const cla3p::dns::RdMatrix& Aref = A;

	cla3p::Guard<cla3p::dns::RdMatrix> Ag = Aref.rblock(2, 0, 3, 2);

	std::cout << "Ag:\n" << Ag.get() << "\n";

	/*
	 * Change values in blocks
	 */

	Ar = -1;
	std::cout << "A:\n" << A;

	/*
	 * Set values of Ab to A, starting at (1,1)
	 */

	Ab = -2;
	A.setBlock(1, 1, Ab);

	std::cout << "A:\n" << A;

	/*
	 * Set values of Ab to A, starting at (2,3)
	 */

	Ab = -3;
	A.rblock(2, 3, 2, 2) = Ab;

	std::cout << "A:\n" << A;

	return 0;
}
