// this file inc
#include "lowrank.hpp"

// system

// 3rd

// cla3p
#include "../bulk/dns_decomp.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace lrk {
/*-------------------------------------------------*/
uint_t sv2rank(uint_t n, const real_t *s, real_t tol, real_t ref)
{
	if(!n) return 0;

	uint_t k0 = 0;
	real_t r = 0;

	if(ref < 0) {
		k0 = 1;
		r = s[0];
	} else {
		r = ref;
	} // ref

	if(!r) return 0;

	real_t abstol = r * tol;

	for(uint_t k = k0; k < n; k++) {
		if(s[k] < abstol) {
			return k;
		} // tol
	} // k

	return n;
}
/*-------------------------------------------------*/
void fr2lr_svd(uint_t m, uint_t n, const real_t * /*a*/, uint_t /*lda*/, real_t tol, real_t ref)
{
	// svd on a
	real_t *s = nullptr;
	//real_t *u = nullptr;
	//real_t *v = nullptr;
	uint_t l = std::min(m,n);

	uint_t k = sv2rank(l, s, tol, ref);
	k++; // for the warning

	// CROP k COLUMNS FROM U&V
}
/*-------------------------------------------------*/
void fr2lr_qr3(uint_t m, uint_t n, const real_t * /*a*/, uint_t lda, real_t tol, real_t ref)
{
	// bool transa = false;
	//
	// if m < n transpose a, mark transa = true & continue
	//

	real_t tol2 = tol * std::sqrt(tol); // conservative tol
	int_t nb = dns::qr_blocksize(m, n);
	real_t *work = nullptr; // 2n + (n+1)nb
	int_t *pvt = nullptr; // n
	real_t *tau = nullptr; // n

	int_t offset = 0;
	uint_t rhint = dns::qr_partial(&offset, m, n, /*a*/nullptr, lda, pvt, tau, tol2, nb, work);

	// svd on R(0:rhint,0:n)
	real_t *s = nullptr;
	//real_t *u = nullptr;
	//real_t *v = nullptr;
	uint_t l = std::min(rhint,n);
	uint_t k = sv2rank(l, s, tol, ref);

	if(k == rhint) {

		rhint = dns::qr_partial(&offset, m, n, /*a*/nullptr, lda, pvt, tau, 0, nb, work); // resume until end
																																			// svd on R(0:rhint,0:n)
		l = std::min(rhint,n);
		k = sv2rank(l, s, tol, ref);

	} // need more ranks

	if(k) {

		// CROP k COLUMNS FROM U&V
		//
		// PERMUTE V using pvt
		// UPDATE U TO QU (dormqr(L,N,m,k,rhint,Q,tau,QU))

	} // ranks found
}
/*-------------------------------------------------*/
static uint_t add_part1_qq()
{
	// A = [a1|a2]
	// B = [b1|b2]
	// A -> QRa
	// B -> QRb
	//
	// C = Ra * Rb' (for loop with dger)
	//
	// C -> LR
	// UPDATE NEW A TO (QaA) (dormqr)
	// UPDATE NEW B TO (QbB) (dormqr)

	return 0;
}
/*-------------------------------------------------*/
static uint_t add_part1_qb()
{
	// A = [a1|a2]
	// B = [b1|b2]
	// A -> QR
	//
	// B = B * R'
	// B -> LR
	// UPDATE NEW A TO (QA) (dormqr)

	return 0;
}
/*-------------------------------------------------*/
static uint_t add_part1_aq()
{
	// A = [a1|a2]
	// B = [b1|b2]
	// B -> QR
	//
	// A = A * R'
	// A -> LR
	// UPDATE NEW B TO (QB) (dormqr)

	return 0;
}
/*-------------------------------------------------*/
static uint_t add_part1_ab()
{
	// C = a1*b1' + a2*b2'
	// C -> LR

	return 0;
}
/*-------------------------------------------------*/
uint_t add_part1(uint_t m, uint_t n,
		//uint_t k1, const real_t *a1, uint_t lda1, const real_t *b1, uint_t ldb1,
		//uint_t k2, const real_t *a2, uint_t lda2, const real_t *b2, uint_t ldb2)
		uint_t k1, const real_t*, uint_t, const real_t*, uint_t,
		uint_t k2, const real_t*, uint_t, const real_t*, uint_t)
{
	uint_t ret = 0;
	uint_t k = k1 + k2;

	if(k < m) {

		if(k < n) {
			ret = add_part1_qq();
		} else {
			ret = add_part1_qb();
		} // k/n dimcheck

	} else {

		if(k < n) {
			ret = add_part1_aq();
		} else {
			ret = add_part1_ab();
		} // k/n dimcheck

	} // k/m dimcheck

	return ret;
}
/*-------------------------------------------------*/
} // namespace lrk
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/
