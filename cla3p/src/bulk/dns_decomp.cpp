// this file inc
#include "dns_decomp.hpp"

// system

// 3rd

// cla3p
#include "../proxies/blas_proxy.hpp"
#include "dns.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace dns {
/*-------------------------------------------------*/
void itrsm_lln(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1)
{
	if(!n || !nrhs) return;

	for(int_t i = 0; i < n; i++) {

		if(ipiv1[i] > 0) {

			int_t ip = ipiv1[i] - 1;

			if(ip != i) {
				blas::swap(nrhs, ptrmv(ldb,b,i,0), ldb, ptrmv(ldb,b,ip,0), ldb);
			} // swap

			int_t k = n - (i+1);

			if(k > 0) {
				blas::ger(k, nrhs, -1, ptrmv(lda,a,i+1,i), 1, ptrmv(ldb,b,i,0), ldb, ptrmv(ldb,b,i+1,0), ldb);
			} // ger

		} else if(ipiv1[i] < 0) {

			int_t ip = - ipiv1[i] - 1;

			if(ip != i) {
				blas::swap(nrhs, ptrmv(ldb,b,i+1,0), ldb, ptrmv(ldb,b,ip,0), ldb);
			} // swap

			int_t k = n - (i+2);

			if(k > 0) {
				blas::ger(k, nrhs, -1, ptrmv(lda,a,i+2,i  ), 1, ptrmv(ldb,b,i  ,0), ldb, ptrmv(ldb,b,i+2,0), ldb);
				blas::ger(k, nrhs, -1, ptrmv(lda,a,i+2,i+1), 1, ptrmv(ldb,b,i+1,0), ldb, ptrmv(ldb,b,i+2,0), ldb);
			} // ger

			i++;

		} // ipiv

	} // i
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/
