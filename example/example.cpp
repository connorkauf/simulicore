#include <iostream>
//#include <cstdio>
//#include <complex>

//#include <omp.h>

#include "cla3p/src/dense.hpp"
#include "cla3p/src/support.hpp"
#include "cla3p/src/perms.hpp"

#include "cla3p/src/bulk/dns.hpp"
#include "cla3p/src/bulk/dns_io.hpp"
#include "cla3p/src/proxies/lapack_proxy.hpp"
#include "cla3p/src/support/error_internal.hpp"

/*-------------------------------------------------*/
template <typename T>
void print_test()
{
	cla3p::uint_t m = 3;
	cla3p::uint_t n = 101;
	cla3p::uint_t lda = m + 10;

	T *a = cla3p::bulk::dns::alloc<T>(m,n,lda);

	cla3p::bulk::dns::fill(cla3p::uplo_t::F, lda, n, a, lda, 0);
	cla3p::bulk::dns::print(cla3p::uplo_t::F, m, n, a, lda, 1);

	//cla3p::bulk::dns::fill(cla3p::uplo_t::U, lda, n, a, lda, 1);
	//cla3p::bulk::dns::print(cla3p::uplo_t::F, m, n, a, lda, 1);
	//
	//cla3p::bulk::dns::fill(cla3p::uplo_t::L, lda, n, a, lda, 2);
	//cla3p::bulk::dns::print(cla3p::uplo_t::F, m, n, a, lda, 1);
	//
	//cla3p::bulk::dns::print(cla3p::uplo_t::U, m, n, a, lda);
	//cla3p::bulk::dns::print(cla3p::uplo_t::L, m, n, a, lda, 1);

	cla3p::i_free(a);
}
/*-------------------------------------------------*/

int main()
{
	cla3p::enable_dbg_messages();

	print_test<cla3p::int_t>();
	//print_test<cla3p::uint_t>();
	//print_test<cla3p::real_t>();
	//print_test<cla3p::real4_t>();
	//print_test<cla3p::complex_t>();
	//print_test<cla3p::complex8_t>();

	return 0;
}
/*-------------------------------------------------*/
