#include <iostream>

#include "cla3p/src/dense.hpp"
#include "cla3p/src/perms.hpp"
#include "cla3p/src/operations.hpp"
#include "cla3p/src/linsol.hpp"

/*-------------------------------------------------*/
static void linsol_mat()
{
	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(10,10);
	cla3p::dns::RdMatrix B = cla3p::dns::RdMatrix::random(10,3);

	{
		cla3p::dns::RdMatrix X = B.copy();
		X /= A;
		std::cout << (A * X - B).normInf() << std::endl;
	}

	{
		cla3p::dns::RdMatrix X = B / A;
		std::cout << (A * X - B).normInf() << std::endl;
	}
}
/*-------------------------------------------------*/
static void linsol_vec()
{
	cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(10,10);
	cla3p::dns::RdVector B = cla3p::dns::RdVector::random(10);

	{
		cla3p::dns::RdVector X = B.copy();
		X /= A;
		std::cout << (A * X - B).normInf() << std::endl;
	}

	{
		cla3p::dns::RdVector X = B / A;
		std::cout << (A * X - B).normInf() << std::endl;
	}
}
/*-------------------------------------------------*/

int main()
{
	linsol_mat();
	linsol_vec();

	return 0;
}
/*-------------------------------------------------*/
