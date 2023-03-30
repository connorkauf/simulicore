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

			if(ip != i+1) {
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
static int_t itrsm_lxd(char uplo, int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1)
{
	if(uplo != 'L' && uplo != 'U') {
		return -1;
	} // uplo check
	
	if(!n || !nrhs) return 0;

	int_t info = 0;

	for(int_t i = 0; i < n; i++) {

		if(ipiv1[i] > 0) {

			real_t dii = 0;
			real_t aii = entry(lda,a,i,i);

			if(!aii) {
				if(!info) info = (i+1);
			} else {
				dii = 1.0 / aii;
			} // aii

			blas::scal(nrhs, dii, ptrmv(ldb,b,i,0), ldb);

		} else if(ipiv1[i] < 0) {

			real_t D[4];
			real_t invD[4] = {0};

			real_t dOffDiag = (uplo == 'L' ? entry(lda,a,i+1,i): entry(lda,a,i,i+1));

			D[0] = entry(lda,a,i,i);
			D[1] = dOffDiag;
			D[2] = dOffDiag;
			D[3] = entry(lda,a,i+1,i+1);

			real_t detD = D[0] * D[3] - D[1] * D[2];

			if(!detD) {
				if(!info) info = (i+1);
			} else {
				real_t detDinv = 1.0 / detD;
				invD[0] =   detDinv * D[3];
				invD[1] = - detDinv * D[1];
				invD[2] = - detDinv * D[2];
				invD[3] =   detDinv * D[0];
			} // detD

			for(int_t j = 0; j < nrhs; j++) {
				real_t B[2] = {entry(ldb,b,i,j), entry(ldb,b,i+1,j)};
				entry(ldb,b,i  ,j) = invD[0] * B[0] + invD[2] * B[1];
				entry(ldb,b,i+1,j) = invD[1] * B[0] + invD[3] * B[1];
			} // j

			i++;

		} // ipiv

	} // i

	return info;
}
/*-------------------------------------------------*/
int_t itrsm_lld(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1)
{
	return itrsm_lxd('L', n, a, lda, nrhs, b, ldb, ipiv1);
}
/*-------------------------------------------------*/
void itrsm_llt(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1)
{
	if(!n || !nrhs) return;

	for(int_t i = n-1; i >= 0; i--) {

		if(ipiv1[i] > 0) {

			int_t ip = ipiv1[i] - 1;
			int_t k = n - (i+1);

			if(k > 0) {
				blas::gemv('T', k, nrhs, -1, ptrmv(ldb,b,i+1,0), ldb, ptrmv(lda,a,i+1,i), 1, 1, ptrmv(ldb,b,i,0), ldb);
			} // gemv

			if(ip != i) {
				blas::swap(nrhs, ptrmv(ldb,b,i,0), ldb, ptrmv(ldb,b,ip,0), ldb);
			} // swap

		} else if(ipiv1[i] < 0) {

			i--;

			int_t ip = - ipiv1[i] - 1;
			int_t k = n - (i+2);

			if(k > 0) {
				blas::gemv('T', k, nrhs, -1, ptrmv(ldb,b,i+2,0), ldb, ptrmv(lda,a,i+2,i+1), 1, 1, ptrmv(ldb,b,i+1,0), ldb);
				blas::gemv('T', k, nrhs, -1, ptrmv(ldb,b,i+2,0), ldb, ptrmv(lda,a,i+2,i  ), 1, 1, ptrmv(ldb,b,i  ,0), ldb);
			} // gemv

			if(ip != i+1) {
				blas::swap(nrhs, ptrmv(ldb,b,i+1,0), ldb, ptrmv(ldb,b,ip,0), ldb);
			} // swap

		} // ipiv

	} // i
}
/*-------------------------------------------------*/
void itrsm_rln(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1)
{
	if(!n || !nrhs) return;

	for(int_t i = n-1; i >= 0; i--) {

		if(ipiv1[i] > 0) {

			int_t ip = ipiv1[i] - 1;
			int_t k = n - (i+1);

			if(k > 0) {
				blas::gemv('N', nrhs, k, -1, ptrmv(ldb,b,0,i+1), ldb, ptrmv(lda,a,i+1,i), 1, 1, ptrmv(ldb,b,0,i), 1);
			} // gemv

			if(ip != i) {
				blas::swap(nrhs, ptrmv(ldb,b,0,i), 1, ptrmv(ldb,b,0,ip), 1);
			} // swap

		} else if(ipiv1[i] < 0) {

			i--;

			int_t ip = - ipiv1[i] - 1;
			int_t k = n - (i+2);

			if(k > 0) {
				blas::gemv('N', nrhs, k, -1, ptrmv(ldb,b,0,i+2), ldb, ptrmv(lda,a,i+2,i+1), 1, 1, ptrmv(ldb,b,0,i+1), 1);
				blas::gemv('N', nrhs, k, -1, ptrmv(ldb,b,0,i+2), ldb, ptrmv(lda,a,i+2,i  ), 1, 1, ptrmv(ldb,b,0,i  ), 1);
			} // gemv

			if(ip != i+1) {
				blas::swap(nrhs, ptrmv(ldb,b,0,i+1), 1, ptrmv(ldb,b,0,ip), 1);
			} // swap

		} // ipiv

	} // i
}
/*-------------------------------------------------*/
static int_t itrsm_rxd(char uplo, int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1)
{
	if(uplo != 'L' && uplo != 'U') {
		return -1;
	} // uplo check
	
	if(!n || !nrhs) return 0;

	int_t info = 0;

	for(int_t i = 0; i < n; i++) {

		if(ipiv1[i] > 0) {

			real_t dii = 0;
			real_t aii = entry(lda,a,i,i);

			if(!aii) {
				if(!info) info = (i+1);
			} else {
				dii = 1.0 / aii;
			} // aii

			blas::scal(nrhs, dii, ptrmv(ldb,b,0,i), 1);

		} else if(ipiv1[i] < 0) {

			real_t D[4];
			real_t invD[4] = {0};

			real_t dOffDiag = (uplo == 'L' ? entry(lda,a,i+1,i): entry(lda,a,i,i+1));

			D[0] = entry(lda,a,i,i);
			D[1] = dOffDiag;
			D[2] = dOffDiag;
			D[3] = entry(lda,a,i+1,i+1);

			real_t detD = D[0] * D[3] - D[1] * D[2];

			if(!detD) {
				if(!info) info = (i+1);
			} else {
				real_t detDinv = 1.0 / detD;
				invD[0] =   detDinv * D[3];
				invD[1] = - detDinv * D[1];
				invD[2] = - detDinv * D[2];
				invD[3] =   detDinv * D[0];
			} // detD

			for(int_t j = 0; j < nrhs; j++) {
				real_t B[2] = {entry(ldb,b,j,i), entry(ldb,b,j,i+1)};
				entry(ldb,b,j,i  ) = invD[0] * B[0] + invD[2] * B[1];
				entry(ldb,b,j,i+1) = invD[1] * B[0] + invD[3] * B[1];
			} // j

			i++;

		} // ipiv

	} // i

	return info;
}
/*-------------------------------------------------*/
int_t itrsm_rld(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1)
{
	return itrsm_rxd('L', n, a, lda, nrhs, b, ldb, ipiv1);
}
/*-------------------------------------------------*/
void itrsm_rlt(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1)
{
	if(!n || !nrhs) return;

	for(int_t i = 0; i < n; i++) {

		if(ipiv1[i] > 0) {

			int_t ip = ipiv1[i] - 1;

			if(ip != i) {
				blas::swap(nrhs, ptrmv(ldb,b,0,i), 1, ptrmv(ldb,b,0,ip), 1);
			} // swap

			int_t k = n - (i+1);

			if(k > 0) {
				blas::ger(nrhs, k, -1, ptrmv(ldb,b,0,i), 1, ptrmv(lda,a,i+1,i), 1, ptrmv(ldb,b,0,i+1), ldb);
			} // ger

		} else if(ipiv1[i] < 0) {

			int_t ip = - ipiv1[i] - 1;

			if(ip != i+1) {
				blas::swap(nrhs, ptrmv(ldb,b,0,i+1), 1, ptrmv(ldb,b,0,ip), 1);
			} // swap

			int_t k = n - (i+2);

			if(k > 0) {
				blas::ger(nrhs, k, -1, ptrmv(ldb,b,0,i  ), 1, ptrmv(lda,a,i+2,i  ), 1, ptrmv(ldb,b,0,i+2), ldb);
				blas::ger(nrhs, k, -1, ptrmv(ldb,b,0,i+1), 1, ptrmv(lda,a,i+2,i+1), 1, ptrmv(ldb,b,0,i+2), ldb);
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
