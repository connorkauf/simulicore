/**
 * @example ex03c_permutation_matrix_create_identity.cpp
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
	 * (5x5) permutation matrix (identity -> Q[i] = i)
	 */

	cla3p::prm::PiMatrix Q = cla3p::prm::PiMatrix::identity(5);

	std::cout << Q.info("Q") << Q;
	std::cout << "As a dense matrix:\n" << permToDense(Q);

	return 0;
}
