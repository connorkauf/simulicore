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

	cla3p::dns::RdMatrix Ad = cla3p::dns::RdMatrix::random(10,10);
	cla3p::dns::RfMatrix Af = cla3p::dns::RfMatrix::random(10,10);
	cla3p::dns::RiMatrix Ai = cla3p::dns::RiMatrix::random(10,10);

	cla3p::dns::RdVector Xd = cla3p::dns::RdVector::random(10);

	cla3p::PermMatrix P = cla3p::PermMatrix::random(10);

	std::cout << Xd.info("Ad");
	std::cout << Xd;

	std::cout << Ad.info("Ad") << Af.info("Af") << Ai.info("Ai");
	std::cout << Ad << Af << Ai;

	std::cout << P.info("P");
	std::cout << P;
	std::cout << P.inverse();

	Xd.fill(1);
	Ad.fill(1);
	Af.fill(1);
	Ai.fill(1);

	std::cout << Xd;
	std::cout << Ad << Af << Ai;

	return 0;
}
/*-------------------------------------------------*/
