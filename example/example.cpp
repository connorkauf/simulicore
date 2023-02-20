#include <iostream>
//#include <cstdio>
//#include <complex>

//#include <omp.h>

#include "cla3p/src/dense.hpp"
#include "cla3p/src/support.hpp"
#include "cla3p/src/perms.hpp"

#include "cla3p/src/support/error_internal.hpp"

/*-------------------------------------------------*/

int main()
{
	cla3p::enable_dbg_messages();

	cla3p::uint_t n = 3;

	cla3p::dns::RdMatrix Ad = cla3p::dns::RdMatrix::random(n,n);
	cla3p::dns::RfMatrix Af = cla3p::dns::RfMatrix::random(n,n);
	cla3p::dns::RiMatrix Ai = cla3p::dns::RiMatrix::random(n,n);

	cla3p::dns::RdVector Xd = cla3p::dns::RdVector::random(n);
	cla3p::dns::RfVector Xf = cla3p::dns::RfVector::random(n);
	cla3p::dns::RiVector Xi = cla3p::dns::RiVector::random(n);

	cla3p::PermMatrix P = cla3p::PermMatrix::random(n);

	std::cout << Xd.info("Xd") << Xf.info("Xf") << Xi.info("Xi");
	std::cout << Xd << Xf << Xi;

	std::cout << Ad.info("Ad") << Af.info("Af") << Ai.info("Ai");
	std::cout << Ad << Af << Ai;

	std::cout << P.info("P");
	std::cout << P;
	std::cout << P.inverse();

	Xd.fill(1);
	Xf.fill(1);
	Xi.fill(1);
	Ad.fill(1);
	Af.fill(1);
	Ai.fill(1);

	std::cout << Xd << Xf << Xi;
	std::cout << Ad << Af << Ai;

	return 0;
}
/*-------------------------------------------------*/
