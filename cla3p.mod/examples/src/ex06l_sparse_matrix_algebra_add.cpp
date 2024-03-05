/**
 * @example ex06l_sparse_matrix_algebra_add.cpp
 */

#include <iostream>
#include "cla3p/sparse.hpp"
#include "cla3p/algebra.hpp"

int main()
{
	cla3p::coo::RdMatrix Acoo(5, 5, 10);
	cla3p::coo::RdMatrix Bcoo(5, 5, 10);

	Acoo.insert(0,0,1.0);
	Acoo.insert(1,1,2.0);
	Acoo.insert(2,1,3.0);
	Acoo.insert(1,3,4.0);
	Acoo.insert(0,0,5.0);

	Bcoo.insert(0,0,-1.3);
	Bcoo.insert(1,2, 2.2);
	Bcoo.insert(2,1,-3.1);
	Bcoo.insert(2,4, 4.6);
	Bcoo.insert(1,1,-5.7);

	cla3p::csc::RdMatrix A = Acoo;
	cla3p::csc::RdMatrix B = Bcoo;

	std::cout << A.info("A") << A << "\n";
	std::cout << B.info("B") << B << "\n";

	/*
	 * Perform the operation (A + 2 * B) using operators and the add function respectively
	 */

	cla3p::csc::RdMatrix C1 = A + 2. * B;
	std::cout << "C1 = A + 2*B:\n" << C1 << "\n";

	cla3p::csc::RdMatrix C2 = cla3p::ops::add(2., B, A);
	std::cout << "C2 = add(2,B,A):\n" << C2 << "\n";

	/*
	 * Perform the operation (Cx += 3 * A) using operators and the update function respectively
	 */

	C1 += 3. * A;
	std::cout << "C1 += 3. * A:\n" << C1 << "\n";

	cla3p::ops::update(3., B, C2);
	std::cout << "update(3,B,C2):\n" << C2 << "\n";

	return 0;
}
