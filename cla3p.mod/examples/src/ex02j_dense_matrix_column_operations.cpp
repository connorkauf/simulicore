/**
 * @example ex02j_dense_matrix_column_operations.cpp
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
	 * Get a copy of column 1 of A as a vector
	 * Get a shallow copy of column 3 of A as a vector
	 */

	cla3p::dns::RdVector Xc = A.column(1);
	cla3p::dns::RdVector Xr = A.rcolumn(3);

	std::cout << "Xc:\n" << Xc;
	std::cout << "Xr:\n" << Xr;

	/*
	 * Get a guarded shallow copy of column 3 of Aref as a vector
	 */

	const cla3p::dns::RdMatrix& Aref = A;

	cla3p::Guard<cla3p::dns::RdVector> Xg = Aref.rcolumn(3);

	std::cout << "Xg:\n" << Xg.get() << "\n";

	/*
	 * Change values in columns
	 */

	Xr = -1;

	std::cout << "A:\n" << A;

	/*
	 * Set values of Xc to A, at column 2
	 */

	Xc = -2;
	A.rcolumn(2) = Xc;

	std::cout << "A:\n" << A;

	return 0;
}
