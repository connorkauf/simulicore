// this file inc
#include "dns_decomp.hpp"

// system

// 3rd

// cla3p
#include "../proxies/blas_proxy.hpp"
#include "../proxies/lapack_proxy.hpp"
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
void itrsm_lun(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1)
{
	if(!n || !nrhs) return;

	for(int_t i = n-1; i >= 0; i--) {

		if(ipiv1[i] > 0) {

			int_t ip = ipiv1[i] - 1;

			if(ip != i) {
				blas::swap(nrhs, ptrmv(ldb,b,i,0), ldb, ptrmv(ldb,b,ip,0), ldb);
			} // swap

			int_t k = i;

			if(k > 0) {
				blas::ger(k, nrhs, -1, ptrmv(lda,a,0,i), 1, ptrmv(ldb,b,i,0), ldb, ptrmv(ldb,b,0,0), ldb);
			} // ger

		} else if(ipiv1[i] < 0) {

			i--;

			int_t ip = - ipiv1[i] - 1;

			if(ip != i) {
				blas::swap(nrhs, ptrmv(ldb,b,i,0), ldb, ptrmv(ldb,b,ip,0), ldb);
			} // swap

			int_t k = i;

			if(k > 0) {
				blas::ger(k, nrhs, -1, ptrmv(lda,a,0,i  ), 1, ptrmv(ldb,b,i  ,0), ldb, ptrmv(ldb,b,0,0), ldb);
				blas::ger(k, nrhs, -1, ptrmv(lda,a,0,i+1), 1, ptrmv(ldb,b,i+1,0), ldb, ptrmv(ldb,b,0,0), ldb);
			} // ger

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
int_t itrsm_lud(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1)
{
	return itrsm_lxd('U', n, a, lda, nrhs, b, ldb, ipiv1);
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
				blas::gemv('T', k, nrhs, -1, ptrmv(ldb,b,i+2,0), ldb, ptrmv(lda,a,i+2,i  ), 1, 1, ptrmv(ldb,b,i  ,0), ldb);
				blas::gemv('T', k, nrhs, -1, ptrmv(ldb,b,i+2,0), ldb, ptrmv(lda,a,i+2,i+1), 1, 1, ptrmv(ldb,b,i+1,0), ldb);
			} // gemv

			if(ip != i+1) {
				blas::swap(nrhs, ptrmv(ldb,b,i+1,0), ldb, ptrmv(ldb,b,ip,0), ldb);
			} // swap

		} // ipiv

	} // i
}
/*-------------------------------------------------*/
void itrsm_lut(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1)
{
	if(!n || !nrhs) return;

	for(int_t i = 0; i < n; i++) {

		if(ipiv1[i] > 0) {

			int_t ip = ipiv1[i] - 1;
			int_t k = i;

			if(k > 0) {
				blas::gemv('T', k, nrhs, -1, ptrmv(ldb,b,0,0), ldb, ptrmv(lda,a,0,i), 1, 1, ptrmv(ldb,b,i,0), ldb);
			} // gemv

			if(ip != i) {
				blas::swap(nrhs, ptrmv(ldb,b,i,0), ldb, ptrmv(ldb,b,ip,0), ldb);
			} // swap

		} else if(ipiv1[i] < 0) {

			int_t ip = - ipiv1[i] - 1;
			int_t k = i;

			if(k > 0) {
				blas::gemv('T', k, nrhs, -1, ptrmv(ldb,b,0,0), ldb, ptrmv(lda,a,0,i  ), 1, 1, ptrmv(ldb,b,i  ,0), ldb);
				blas::gemv('T', k, nrhs, -1, ptrmv(ldb,b,0,0), ldb, ptrmv(lda,a,0,i+1), 1, 1, ptrmv(ldb,b,i+1,0), ldb);
			} // gemv

			if(ip != i) {
				blas::swap(nrhs, ptrmv(ldb,b,i,0), ldb, ptrmv(ldb,b,ip,0), ldb);
			} // swap

			i++;

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
				blas::gemv('N', nrhs, k, -1, ptrmv(ldb,b,0,i+2), ldb, ptrmv(lda,a,i+2,i  ), 1, 1, ptrmv(ldb,b,0,i  ), 1);
				blas::gemv('N', nrhs, k, -1, ptrmv(ldb,b,0,i+2), ldb, ptrmv(lda,a,i+2,i+1), 1, 1, ptrmv(ldb,b,0,i+1), 1);
			} // gemv

			if(ip != i+1) {
				blas::swap(nrhs, ptrmv(ldb,b,0,i+1), 1, ptrmv(ldb,b,0,ip), 1);
			} // swap

		} // ipiv

	} // i
}
/*-------------------------------------------------*/
void itrsm_run(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1)
{
	if(!n || !nrhs) return;

	for(int_t i = 0; i < n; i++) {

		if(ipiv1[i] > 0) {

			int_t ip = ipiv1[i] - 1;
			int_t k = i;

			if(k > 0) {
				blas::gemv('N', nrhs, k, -1, ptrmv(ldb,b,0,0), ldb, ptrmv(lda,a,0,i), 1, 1, ptrmv(ldb,b,0,i), 1);
			} // gemv

			if(ip != i) {
				blas::swap(nrhs, ptrmv(ldb,b,0,i), 1, ptrmv(ldb,b,0,ip), 1);
			} // swap

		} else if(ipiv1[i] < 0) {

			int_t ip = - ipiv1[i] - 1;
			int_t k = i;

			if(k > 0) {
				blas::gemv('N', nrhs, k, -1, ptrmv(ldb,b,0,0), ldb, ptrmv(lda,a,0,i  ), 1, 1, ptrmv(ldb,b,0,i  ), 1);
				blas::gemv('N', nrhs, k, -1, ptrmv(ldb,b,0,0), ldb, ptrmv(lda,a,0,i+1), 1, 1, ptrmv(ldb,b,0,i+1), 1);
			} // gemv

			if(ip != i) {
				blas::swap(nrhs, ptrmv(ldb,b,0,i), 1, ptrmv(ldb,b,0,ip), 1);
			} // swap

			i++;

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
int_t itrsm_rud(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1)
{
	return itrsm_rxd('U', n, a, lda, nrhs, b, ldb, ipiv1);
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
void itrsm_rut(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1)
{
	if(!n || !nrhs) return;

	for(int_t i = n-1; i >= 0; i--) {

		if(ipiv1[i] > 0) {

			int_t ip = ipiv1[i] - 1;

			if(ip != i) {
				blas::swap(nrhs, ptrmv(ldb,b,0,i), 1, ptrmv(ldb,b,0,ip), 1);
			} // swap

			int_t k = i;

			if(k > 0) {
				blas::ger(nrhs, k, -1, ptrmv(ldb,b,0,i), 1, ptrmv(lda,a,0,i), 1, ptrmv(ldb,b,0,0), ldb);
			} // ger

		} else if(ipiv1[i] < 0) {

			i--;

			int_t ip = - ipiv1[i] - 1;

			if(ip != i) {
				blas::swap(nrhs, ptrmv(ldb,b,0,i), 1, ptrmv(ldb,b,0,ip), 1);
			} // swap

			int_t k = i;

			if(k > 0) {
				blas::ger(nrhs, k, -1, ptrmv(ldb,b,0,i  ), 1, ptrmv(lda,a,0,i  ), 1, ptrmv(ldb,b,0,0), ldb);
				blas::ger(nrhs, k, -1, ptrmv(ldb,b,0,i+1), 1, ptrmv(lda,a,0,i+1), 1, ptrmv(ldb,b,0,0), ldb);
			} // ger

		} // ipiv

	} // i
}
/*-------------------------------------------------*/
static void itrperm_lower(int_t n, real_t *a, int_t lda, const int_t *ipiv1)
{
	if(!n) return;

	for(int_t i = 0; i < n; i++) {

		if(ipiv1[i] > 0) {

			real_t *aCol = ptrmv(lda,a,0,i);

			for(int_t k = i+1; k < n; k++) {
				if(ipiv1[k] > 0) {
					int_t kp = ipiv1[k] - 1;
					if(kp != k) {
						//std::swap(entry(lda,a,k,i), entry(lda,a,kp,i));
						std::swap(aCol[k], aCol[kp]);
					} // swap
				} else if(ipiv1[k] < 0) {
					int_t kp = - ipiv1[k] - 1;
					if(kp != k+1) {
						//std::swap(entry(lda,a,k+1,i), entry(lda,a,kp,i));
						std::swap(aCol[k+1], aCol[kp]);
					} // swap
					k++;
				} // ipiv
			} // k

		} else if(ipiv1[i] < 0) {

			real_t *aCol  = ptrmv(lda,a,0,i  );
			real_t *aCol1 = ptrmv(lda,a,0,i+1);

			for(int_t k = i+2; k < n; k++) {
				if(ipiv1[k] > 0) {
					int_t kp = ipiv1[k] - 1;
					if(kp != k) {
						//std::swap(entry(lda,a,k,i  ), entry(lda,a,kp,i  ));
						//std::swap(entry(lda,a,k,i+1), entry(lda,a,kp,i+1));
						std::swap(aCol [k], aCol [kp]);
						std::swap(aCol1[k], aCol1[kp]);
					} // swap
				} else if(ipiv1[k] < 0) {
					int_t kp = - ipiv1[k] - 1;
					if(kp != k+1) {
						//std::swap(entry(lda,a,k+1,i  ), entry(lda,a,kp,i  ));
						//std::swap(entry(lda,a,k+1,i+1), entry(lda,a,kp,i+1));
						std::swap(aCol [k+1], aCol [kp]);
						std::swap(aCol1[k+1], aCol1[kp]);
					} // swap
					k++;
				} // ipiv
			} // k

			//entry(lda,a,i+1,i) = 0;
			aCol[i+1] = 0;

			i++;

		} // ipiv

	} // i
}
/*-------------------------------------------------*/
static void itrperm_upper(int_t n, real_t *a, int_t lda, const int_t *ipiv1)
{
	if(!n) return;

	for(int_t i = n-1; i >= 0; i--) {

		if(ipiv1[i] > 0) {

			real_t *aCol = ptrmv(lda,a,0,i);

			for(int_t k = i-1; k >= 0; k--) {
				if(ipiv1[k] > 0) {
					int_t kp = ipiv1[k] - 1;
					if(kp != k) {
						//std::swap(entry(lda,a,k,i), entry(lda,a,kp,i));
						std::swap(aCol[k], aCol[kp]);
					} // swap
				} else if(ipiv1[k] < 0) {
					k--;
					int_t kp = - ipiv1[k] - 1;
					if(kp != k) {
						//std::swap(entry(lda,a,k,i), entry(lda,a,kp,i));
						std::swap(aCol[k], aCol[kp]);
					} // swap
				} // ipiv
			} // k

		} else if(ipiv1[i] < 0) {

			i--;

			real_t *aCol  = ptrmv(lda,a,0,i  );
			real_t *aCol1 = ptrmv(lda,a,0,i+1);

			for(int_t k = i-1; k >= 0; k--) {
				if(ipiv1[k] > 0) {
					int_t kp = ipiv1[k] - 1;
					if(kp != k) {
						//std::swap(entry(lda,a,k,i  ), entry(lda,a,kp,i  ));
						//std::swap(entry(lda,a,k,i+1), entry(lda,a,kp,i+1));
						std::swap(aCol [k], aCol [kp]);
						std::swap(aCol1[k], aCol1[kp]);
					} // swap
				} else if(ipiv1[k] < 0) {
					k--;
					int_t kp = - ipiv1[k] - 1;
					if(kp != k) {
						//std::swap(entry(lda,a,k,i  ), entry(lda,a,kp,i  ));
						//std::swap(entry(lda,a,k,i+1), entry(lda,a,kp,i+1));
						std::swap(aCol [k], aCol [kp]);
						std::swap(aCol1[k], aCol1[kp]);
					} // swap
				} // ipiv
			} // k

			//entry(lda,a,i,i+1) = 0;
			aCol1[i] = 0;

		} // ipiv

	} // i
}
/*-------------------------------------------------*/
void itrperm(char uplo, int_t n, real_t *a, int_t lda, const int_t *ipiv1)
{
	if(uplo == 'L') itrperm_lower(n, a, lda, ipiv1);
	if(uplo == 'U') itrperm_upper(n, a, lda, ipiv1);
}
/*-------------------------------------------------*/
static void igeperm_forward(int_t off, char trans, int_t m, int_t n, real_t *a, int_t lda, const int_t *ipiv1)
{
	if(!m || !n) return;

	for(int_t i = 0; i < m; i++) {

		if(ipiv1[i] > 0) {

			int_t ip = ipiv1[i] - 1;

			if(ip != i && trans == 'N') blas::swap(n, ptrmv(lda,a,i,0), lda, ptrmv(lda,a,ip,0), lda);
			if(ip != i && trans == 'T') blas::swap(n, ptrmv(lda,a,0,i),   1, ptrmv(lda,a,0,ip),   1);

		} else if(ipiv1[i] < 0) {

			int_t ip = - ipiv1[i] - 1;

			if(ip != i+off && trans == 'N') blas::swap(n, ptrmv(lda,a,i+off,0), lda, ptrmv(lda,a,ip,0), lda);
			if(ip != i+off && trans == 'T') blas::swap(n, ptrmv(lda,a,0,i+off),   1, ptrmv(lda,a,0,ip),   1);

			i++;

		} // ipiv

	} // i
}
/*-------------------------------------------------*/
static void igeperm_backward(int_t off, char trans, int_t m, int_t n, real_t *a, int_t lda, const int_t *ipiv1)
{
	if(!m || !n) return;

	for(int_t i = m-1; i >= 0; i--) {

		if(ipiv1[i] > 0) {

			int_t ip = ipiv1[i] - 1;

			if(ip != i && trans == 'N') blas::swap(n, ptrmv(lda,a,i,0), lda, ptrmv(lda,a,ip,0), lda);
			if(ip != i && trans == 'T') blas::swap(n, ptrmv(lda,a,0,i),   1, ptrmv(lda,a,0,ip),   1);

		} else if(ipiv1[i] < 0) {

			i--;

			int_t ip = - ipiv1[i] - 1;

			if(ip != i+off && trans == 'N') blas::swap(n, ptrmv(lda,a,i+off,0), lda, ptrmv(lda,a,ip,0), lda);
			if(ip != i+off && trans == 'T') blas::swap(n, ptrmv(lda,a,0,i+off),   1, ptrmv(lda,a,0,ip),   1);

		} // ipiv

	} // i
}
/*-------------------------------------------------*/
void igeperm(int_t off, char order, char trans, int_t m, int_t n, real_t *a, int_t lda, const int_t *ipiv1)
{
	if(order == 'F') igeperm_forward (off, trans, m, n, a, lda, ipiv1);
	if(order == 'B') igeperm_backward(off, trans, m, n, a, lda, ipiv1);
}
/*-------------------------------------------------*/
void itrsm_left_blas3(char uplo, int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1, real_t *work)
{
	int_t ldw = n;

	if(uplo == 'L') {
		copy(uplo_t::L, n, n, a, lda, work, ldw);

		itrperm(uplo, n, work, ldw, ipiv1);

		igeperm(1, 'F', 'N', n, nrhs, b, ldb, ipiv1);
		blas::trsm('L', uplo, 'N', 'U', n, nrhs, 1, work, ldw, b, ldb);

		itrsm_lld(n, a, lda, nrhs, b, ldb, ipiv1);

		blas::trsm('L', uplo, 'T', 'U', n, nrhs, 1, work, ldw, b, ldb);
		igeperm(1, 'B', 'N', n, nrhs, b, ldb, ipiv1);
	} // lower

	if(uplo == 'U') {
		copy(uplo_t::U, n, n, a, lda, work, ldw);

		itrperm(uplo, n, work, ldw, ipiv1);

		igeperm(0, 'B', 'N', n, nrhs, b, ldb, ipiv1);
		blas::trsm('L', uplo, 'N', 'U', n, nrhs, 1, work, ldw, b, ldb);

		itrsm_lud(n, a, lda, nrhs, b, ldb, ipiv1);

		blas::trsm('L', uplo, 'T', 'U', n, nrhs, 1, work, ldw, b, ldb);
		igeperm(0, 'F', 'N', n, nrhs, b, ldb, ipiv1);
	} // lower
}
/*-------------------------------------------------*/
void iscal(char uplo, int_t n, int_t k, const real_t *d, int_t ldd, const real_t *x, int_t ldx, real_t *y, int_t ldy, const int_t *ipiv1)
{
	if(!n || !k) return;

	copy(uplo_t::F, n, k, x, ldx, y, ldy);

	for(int_t i = 0; i < k; i++) {

		if(ipiv1[i] > 0) {

			blas::scal(n, entry(ldd,d,i,i), ptrmv(ldy,y,0,i), 1);

		} else if(ipiv1[i] < 0) {

			real_t dOffDiag = (uplo == 'L' ? entry(ldd,d,i+1,i): entry(ldd,d,i,i+1));

			real_t D[4];
			D[0] = entry(ldd,d,i,i);
			D[1] = dOffDiag;
			D[2] = dOffDiag;
			D[3] = entry(ldd,d,i+1,i+1);

			blas::gemm('N', 'N', n, 2, 2, 1, ptrmv(ldx,x,0,i), ldx, D, 2, 0, ptrmv(ldy,y,0,i), ldy);

			i++;

		} // ipiv

	} // i
}
/*-------------------------------------------------*/
void isyrk(char uplo, int_t n, int_t k, real_t alpha,
    const real_t *d, int_t ldd,
    const real_t *x, int_t ldx, const int_t *ipiv1,
    real_t *c, int ldc, real_t *work)
{
	if(!n || !k) return;

	int_t ldw = n;

	iscal(uplo, n, k, d, ldd, x, ldx, work, ldw, ipiv1);

	blas::gemmt(uplo, 'N', 'T', n, k, alpha, work, ldw, x, ldx, 1, c, ldc);
}
/*-------------------------------------------------*/
void igerk(char uplo, int_t m, int_t n, int_t k, real_t alpha,
    const real_t *d, int_t ldd,
    const real_t *x, int_t ldx,
    const real_t *y, int_t ldy, const int_t *ipiv1,
    real_t *c, int ldc, real_t *work)
{
	if(m < n) {

		// C += alpha * (X * D) * Y'

		int_t ldw = m;
		iscal(uplo, m, k, d, ldd, x, ldx, work, ldw, ipiv1);
		blas::gemm('N', 'T', m, n, k, alpha, work, ldw, y, ldy, 1, c, ldc);

	} else {

		// C += alpha * X * (Y * D)'

		int_t ldw = n;
		iscal(uplo, n, k, d, ldd, y, ldy, work, ldw, ipiv1);
		blas::gemm('N', 'T', m, n, k, alpha, y, ldy, work, ldw, 1, c, ldc);

	} // min dim
}
/*-------------------------------------------------*/
int_t qr_blocksize(int_t m, int_t n)
{
	int_t default_ret = 24;
	int_t ret = lapack::laenv(1, "DGEQRF", " ", m, n, -1, -1);

	if(ret < 0) {
		ret = std::min(default_ret, n);
	} // error

	return ret;
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/
