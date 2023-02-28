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
#include "cla3p/src/support/utils.hpp"

/*-------------------------------------------------*/
template <typename T, typename Tr>
static Tr naive_syhe_norm_fro_tmpl(cla3p::uplo_t uplo, cla3p::uint_t n, const T *a, cla3p::uint_t lda)
{
  Tr sum = 0;
  Tr two = 2;
  for(cla3p::uint_t j = 0; j < n; j++) {
		cla3p::RowRange ir = irange(uplo, n, j);
    for(cla3p::uint_t i = ir.ibgn; i < ir.iend; i++) {
      Tr aij = std::abs(cla3p::bulk::dns::entry(lda,a,i,j));
      sum += (i != j) ? two * aij * aij : aij * aij;
    } // i
  } // j
  return std::sqrt(sum);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void fro_test()
{
	cla3p::uint_t m = 128;
	cla3p::uint_t n = 128;
	cla3p::uint_t lda = m + 10;

	T *a = cla3p::bulk::dns::alloc<T>(m,n,lda);

	cla3p::bulk::dns::rand(cla3p::uplo_t::F, lda, n, a, lda, 0);

	cla3p::uplo_t uplo = cla3p::uplo_t::U;
	Tr ret  = cla3p::bulk::dns::norm_fro(cla3p::prop_t::SYMMETRIC, uplo, m, n, a, lda);
	Tr ret2 = naive_syhe_norm_fro_tmpl<T,Tr>(uplo, n, a, lda);

	std::cout << "Error: " << (std::abs(ret-ret2)/ret2) << std::endl;

	cla3p::i_free(a);
}
/*-------------------------------------------------*/

int main()
{
	cla3p::enable_dbg_messages();

	fro_test<cla3p::real_t,cla3p::real_t>();

	return 0;
}
/*-------------------------------------------------*/
