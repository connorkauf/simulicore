/**
 * @example ex03d_permutation_matrix_create_random.cpp
 */

#include <iostream>
#include "cla3p/perms.hpp"
#include "cla3p/dense.hpp"

/*-----------------------------------------------------*/
cla3p::dns::RdMatrix permToDense(const cla3p::prm::PiMatrix& P)
{
	cla3p::dns::RdMatrix ret(P.size(), P.size());
	ret = 0;
	for(cla3p::uint_t i = 0; i < P.size(); i++)
		ret(P(i),i) = cla3p::real_t(1);
	return ret;
}
/*-----------------------------------------------------*/
int main()
{
	/* 
	 * (4x4) permutation matrix 
	 * with randomly generated unique values
	 */

	cla3p::prm::PiMatrix P = cla3p::prm::PiMatrix::random(4);

	std::cout << P.info("P") << P;
	std::cout << "As a dense matrix:\n" << permToDense(P);

	return 0;
}
