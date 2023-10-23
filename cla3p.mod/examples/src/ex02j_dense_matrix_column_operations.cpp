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

	const cla3p::dns::RdMatrix& Aref = A;

	std::cout << "A:\n" << A << "\n";

	/*
	 * Get a copy of column 1 of A as a vector
	 * Get a shallow copy of column 3 of A as a vector
	 */

	cla3p::dns::RdVector Acol1 = A.column(1);
	cla3p::dns::RdVector Aref3 = A.rcolumn(3);

	std::cout << "column 1 (copy):\n" << Acol1;
	std::cout << "column 3 (reference):\n" << Aref3;

	/*
	 * Get a guarded shallow copy of column 3 of Aref as a vector
	 */

	cla3p::Guard<cla3p::dns::RdVector> Agcol3 = Aref.rcolumn(3);

	std::cout << "column 3 (guarded reference):\n" << Agcol3.get() << "\n";

	/*
	 * Change values in columns
	 */

	Acol1 = -2;
	Aref3 = -1;

	std::cout << "A after value changes in Acol1 & Aref3:\n" << A;

	return 0;
}
