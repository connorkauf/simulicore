/**
 * @example ex06b_sparse_matrix_fill.cpp
 */

#include <iostream>
#include "cla3p/sparse.hpp"

int main()
{
	cla3p::coo::RdMatrix A(5, 5);

	/* 
	 * Insert values in A
	 */

	A.insert(0,0,1.0); // insert a '1' in A(0,0)
	A.insert(1,1,2.0); // insert a '2' in A(1,1)
	A.insert(2,1,3.0); // insert a '3' in A(2,1)
	A.insert(1,3,4.0); // insert a '4' in A(1,3)
	A.insert(0,0,5.0); // insert a '5' in A(0,0)

	std::cout << A.info("A") << A << "\n";

	/* 
	 * Create a csc matrix from the coo matrix 
	 * (double entries will be added together)
	 */

	cla3p::csc::RdMatrix B = A;

	std::cout << B.info("B") << B << "\n";

	/* 
	 * Create a csc matrix from the coo matrix 
	 * (the absolute maximum of double entries will be kept)
	 */

	cla3p::csc::RdMatrix C = A.toCsc(cla3p::dup_t::Amax);

	std::cout << C.info("C") << C << "\n";

	return 0;
}
