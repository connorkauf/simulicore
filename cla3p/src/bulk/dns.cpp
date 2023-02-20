// this file inc
#include "dns.hpp"

// system
#include <functional>

// 3rd

// cla3p
#include "../checks/all_checks.hpp"
#include "../proxies/blas_proxy.hpp"
#include "../proxies/lapack_proxy.hpp"
#include "../proxies/mkl_proxy.hpp"
#include "../support/error.hpp"
#include "../support/error_internal.hpp"
#include "../support/utils.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace dns {
/*-------------------------------------------------*/
static uint_t recursive_min_dim()
{
	return 256;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void fill_tmpl(prop_t ptype, uint_t m, uint_t n, T *a, uint_t lda, T val)
{
	if(!m || !n) return;

	dns_consistency_check(ptype, m, n, a, lda);

	bool lower = Property(ptype).is_lower();

	if(m == lda && !lower) {
		std::fill_n(a, m * n, val);
	} else {
		for(uint_t j = 0; j < n; j++) {
			uint_t ibgn = lower ?     j : 0;
			uint_t ilen = lower ? m - j : m;
			std::fill_n(ptrmv(lda,a,ibgn,j), ilen, val);
		} // j
	} // m = lda
}
/*-------------------------------------------------*/
void fill(prop_t ptype, uint_t m, uint_t n, int_t      *a, uint_t lda, int_t      val){ fill_tmpl(ptype, m, n, a, lda, val); }
void fill(prop_t ptype, uint_t m, uint_t n, uint_t     *a, uint_t lda, uint_t     val){ fill_tmpl(ptype, m, n, a, lda, val); }
void fill(prop_t ptype, uint_t m, uint_t n, real_t     *a, uint_t lda, real_t     val){ fill_tmpl(ptype, m, n, a, lda, val); }
void fill(prop_t ptype, uint_t m, uint_t n, real4_t    *a, uint_t lda, real4_t    val){ fill_tmpl(ptype, m, n, a, lda, val); }
void fill(prop_t ptype, uint_t m, uint_t n, complex_t  *a, uint_t lda, complex_t  val){ fill_tmpl(ptype, m, n, a, lda, val); }
void fill(prop_t ptype, uint_t m, uint_t n, complex8_t *a, uint_t lda, complex8_t val){ fill_tmpl(ptype, m, n, a, lda, val); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename Tin, typename Tout>
static void rand_tmpl(prop_t ptype, uint_t m, uint_t n, Tout *a, uint_t lda, 
		Tin low, Tin high, const std::function<Tout (Tin low, Tin high)>& randfun)
{
	if(!m || !n) return;

	dns_consistency_check(ptype, m, n, a, lda);

	bool lower = Property(ptype).is_lower();

	for(uint_t j = 0; j < n; j++) {
		uint_t ibgn = lower ? j : 0;
		for(uint_t i = ibgn; i < m; i++) {
			entry(lda,a,i,j) = randfun(low, high);
		} // j
	} // j
	
	if(ptype == prop_t::HERMITIAN) {
		for(uint_t j = 0; j < n; j++) {
			setim(entry(lda,a,j,j), 0.);
		} // j
	} // hermitian
}
/*-------------------------------------------------*/
void rand(prop_t ptype, uint_t m, uint_t n, int_t      *a, uint_t lda, int_t   low, int_t   high){ rand_tmpl<int_t  ,int_t     >(ptype, m, n, a, lda, low, high, irand); }
void rand(prop_t ptype, uint_t m, uint_t n, uint_t     *a, uint_t lda, uint_t  low, uint_t  high){ rand_tmpl<uint_t ,uint_t    >(ptype, m, n, a, lda, low, high, urand); }
void rand(prop_t ptype, uint_t m, uint_t n, real_t     *a, uint_t lda, real_t  low, real_t  high){ rand_tmpl<real_t ,real_t    >(ptype, m, n, a, lda, low, high, drand); }
void rand(prop_t ptype, uint_t m, uint_t n, real4_t    *a, uint_t lda, real4_t low, real4_t high){ rand_tmpl<real4_t,real4_t   >(ptype, m, n, a, lda, low, high, srand); }
void rand(prop_t ptype, uint_t m, uint_t n, complex_t  *a, uint_t lda, real_t  low, real_t  high){ rand_tmpl<real_t ,complex_t >(ptype, m, n, a, lda, low, high, zrand); }
void rand(prop_t ptype, uint_t m, uint_t n, complex8_t *a, uint_t lda, real4_t low, real4_t high){ rand_tmpl<real4_t,complex8_t>(ptype, m, n, a, lda, low, high, crand); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void copy_tmpl(prop_t ptype, uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, T coeff);
/*-------------------------------------------------*/
template <typename T>
static void copy_recursive_tmpl(uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, T coeff)
{
	if(!n) return;

	if(n < recursive_min_dim()) {

		for(uint_t j = 0; j < n; j++) {
			copy_tmpl(prop_t::GENERAL, n-j, 1, ptrmv(lda,a,j,j), lda, ptrmv(ldb,b,j,j), ldb, coeff);
		} // j

	} else {

		uint_t n0 = n/2;
		uint_t n1 = n - n0;

		copy_recursive_tmpl(n0, ptrmv(lda,a, 0, 0), lda, ptrmv(ldb,b, 0, 0), ldb, coeff);
		copy_recursive_tmpl(n1, ptrmv(lda,a,n0,n0), lda, ptrmv(ldb,b,n0,n0), ldb, coeff);

		copy_tmpl(prop_t::GENERAL, n1, n0, ptrmv(lda,a,n0,0), lda, ptrmv(ldb,b,n0,0), ldb, coeff);

	} // dim check
}
/*-------------------------------------------------*/
template <typename T>
static void copy_tmpl(prop_t ptype, uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, T coeff)
{
	if(!m || !n) return;

	dns_consistency_check(ptype, m, n, a, lda);

	bool lower = Property(ptype).is_lower();

	if(lower) {
		copy_recursive_tmpl(n, a, lda, b, ldb, coeff);
	} else {
		mkl::omatcopy('C', 'N', m, n, coeff, a, lda, b, ldb);
	} // lower
}
/*-------------------------------------------------*/
template <typename T>
static void naive_copy_tmpl(prop_t ptype, uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, T coeff)
{
	if(!m || !n) return;

	dns_consistency_check(ptype, m, n, a, lda);

	bool lower = Property(ptype).is_lower();

	for(uint_t j = 0; j < n; j++) {
		uint_t ibgn = lower ? j : 0;
		for(uint_t i = ibgn; i < m; i++) {
			entry(ldb,b,i,j) = coeff * entry(lda,a,i,j);
		} // i
	} // j
}
/*-------------------------------------------------*/
void copy(prop_t ptype, uint_t m, uint_t n, const int_t *a, uint_t lda, int_t *b, uint_t ldb, int_t coeff)
{
	naive_copy_tmpl(ptype, m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void copy(prop_t ptype, uint_t m, uint_t n, const uint_t *a, uint_t lda, uint_t *b, uint_t ldb, uint_t coeff)
{
	naive_copy_tmpl(ptype, m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void copy(prop_t ptype, uint_t m, uint_t n, const real_t *a, uint_t lda, real_t *b, uint_t ldb, real_t coeff)
{
	copy_tmpl(ptype, m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void copy(prop_t ptype, uint_t m, uint_t n, const real4_t *a, uint_t lda, real4_t *b, uint_t ldb, real4_t coeff)
{ 
	copy_tmpl(ptype, m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void copy(prop_t ptype, uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, complex_t coeff)
{
	copy_tmpl(ptype, m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void copy(prop_t ptype, uint_t m, uint_t n, const complex8_t *a, uint_t lda, complex8_t *b, uint_t ldb, complex8_t coeff)
{ 
	copy_tmpl(ptype, m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void scale_tmpl(prop_t ptype, uint_t m, uint_t n, T *a, uint_t lda, T coeff);
/*-------------------------------------------------*/
template <typename T>
static void scale_recursive_tmpl(uint_t n, T *a, uint_t lda, T coeff)
{
	if(!n) return;

	if(n < recursive_min_dim()) {

		for(uint_t j = 0; j < n; j++) {
			scale_tmpl(prop_t::GENERAL, n-j, 1, ptrmv(lda,a,j,j), lda, coeff);
		} // j

	} else {

		uint_t n0 = n/2;
		uint_t n1 = n - n0;

		scale_recursive_tmpl(n0, ptrmv(lda,a, 0, 0), lda, coeff);
		scale_recursive_tmpl(n1, ptrmv(lda,a,n0,n0), lda, coeff);

		scale_tmpl(prop_t::GENERAL, n1, n0, ptrmv(lda,a,n0,0), lda, coeff);

	} // dim check
}
/*-------------------------------------------------*/
template <typename T>
static void scale_tmpl(prop_t ptype, uint_t m, uint_t n, T *a, uint_t lda, T coeff)
{
	if(!m || !n) return;

	dns_consistency_check(ptype, m, n, a, lda);

	bool lower = Property(ptype).is_lower();

	T coeff_one = 1;
	if(coeff == coeff_one) {
		return;
	} // coeff = 1

	T coeff_zero = 0;
	if(coeff == coeff_zero) {
		zero(ptype, m, n, a, lda);
		return;
	} // coeff = 0

	if(lower) {
		scale_recursive_tmpl(n, a, lda, coeff);
	} else {
		mkl::imatcopy('C', 'N', m, n, coeff, a, lda, lda);
	} // lower
}
/*-------------------------------------------------*/
template <typename T>
static void naive_scale_tmpl(prop_t ptype, uint_t m, uint_t n, T *a, uint_t lda, T coeff)
{
	if(!m || !n) return;

	dns_consistency_check(ptype, m, n, a, lda);

	bool lower = Property(ptype).is_lower();

	T coeff_one = 1;
	if(coeff == coeff_one) {
		return;
	} // coeff = 1

	T coeff_zero = 0;
	if(coeff == coeff_zero) {
		zero(ptype, m, n, a, lda);
		return;
	} // coeff = 0

	for(uint_t j = 0; j < n; j++) {
		uint_t ibgn = lower ? j : 0;
		for(uint_t i = ibgn; i < m; i++) {
			entry(lda,a,i,j) = coeff * entry(lda,a,i,j);
		} // i
	} // j
}
/*-------------------------------------------------*/
void scale(prop_t ptype, uint_t m, uint_t n, int_t      *a, uint_t lda, int_t      coeff) { naive_scale_tmpl(ptype, m, n, a, lda, coeff); }
void scale(prop_t ptype, uint_t m, uint_t n, uint_t     *a, uint_t lda, uint_t     coeff) { naive_scale_tmpl(ptype, m, n, a, lda, coeff); }
void scale(prop_t ptype, uint_t m, uint_t n, real_t     *a, uint_t lda, real_t     coeff) {       scale_tmpl(ptype, m, n, a, lda, coeff); }
void scale(prop_t ptype, uint_t m, uint_t n, real4_t    *a, uint_t lda, real4_t    coeff) {       scale_tmpl(ptype, m, n, a, lda, coeff); }
void scale(prop_t ptype, uint_t m, uint_t n, complex_t  *a, uint_t lda, complex_t  coeff) {       scale_tmpl(ptype, m, n, a, lda, coeff); }
void scale(prop_t ptype, uint_t m, uint_t n, complex8_t *a, uint_t lda, complex8_t coeff) {       scale_tmpl(ptype, m, n, a, lda, coeff); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void transpose_tmpl(uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, T coeff)
{
	if(!m || !n) return;

	mkl::omatcopy('C', 'T', m, n, coeff, a, lda, b, ldb);
}
/*-------------------------------------------------*/
template <typename T>
static void naive_transpose_tmpl(uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, T coeff)
{
	if(!m || !n) return;

	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < m; i++) {
			entry(ldb,b,j,i) = coeff * entry(lda,a,i,j);
		} // i
	} // j
}
/*-------------------------------------------------*/
void transpose(uint_t m, uint_t n, const int_t *a, uint_t lda, int_t *b, uint_t ldb, int_t coeff)
{ 
	naive_transpose_tmpl(m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void transpose(uint_t m, uint_t n, const uint_t *a, uint_t lda, uint_t *b, uint_t ldb, uint_t coeff)
{ 
	naive_transpose_tmpl(m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void transpose(uint_t m, uint_t n, const real_t *a, uint_t lda, real_t *b, uint_t ldb, real_t coeff)
{ 
	transpose_tmpl(m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void transpose(uint_t m, uint_t n, const real4_t *a, uint_t lda, real4_t *b, uint_t ldb, real4_t coeff)
{ 
	transpose_tmpl(m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void transpose(uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, complex_t coeff)
{
	transpose_tmpl(m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void transpose(uint_t m, uint_t n, const complex8_t *a, uint_t lda, complex8_t *b, uint_t ldb, complex8_t coeff)
{ 
	transpose_tmpl(m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void conjugate_transpose_tmpl(uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, T coeff)
{
	if(!m || !n) return;

	mkl::omatcopy('C', 'C', m, n, coeff, a, lda, b, ldb);
}
/*-------------------------------------------------*/
void conjugate_transpose(uint_t m, uint_t n, const int_t *a, uint_t lda, int_t *b, uint_t ldb, int_t coeff)
{ 
	WarningNoReach();
	transpose(m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void conjugate_transpose(uint_t m, uint_t n, const uint_t *a, uint_t lda, uint_t *b, uint_t ldb, uint_t coeff)
{ 
	WarningNoReach();
	transpose(m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void conjugate_transpose(uint_t m, uint_t n, const real_t *a, uint_t lda, real_t *b, uint_t ldb, real_t coeff)
{ 
	WarningNoReach();
	transpose(m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void conjugate_transpose(uint_t m, uint_t n, const real4_t *a, uint_t lda, real4_t *b, uint_t ldb, real4_t coeff)
{ 
	WarningNoReach();
	transpose(m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void conjugate_transpose(uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, complex_t coeff)
{ 
	conjugate_transpose_tmpl(m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void conjugate_transpose(uint_t m, uint_t n, const complex8_t *a, uint_t lda, complex8_t *b, uint_t ldb, complex8_t coeff)
{ 
	conjugate_transpose_tmpl(m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void conjugate_tmpl(prop_t ptype, uint_t m, uint_t n, T *a, uint_t lda, T coeff);
/*-------------------------------------------------*/
template <typename T>
static void conjugate_recursive_tmpl(uint_t n, T *a, uint_t lda, T coeff)
{
	if(!n) return;

	if(n < recursive_min_dim()) {

		for(uint_t j = 0; j < n; j++) {
			conjugate_tmpl(prop_t::GENERAL, n-j, 1, ptrmv(lda,a,j,j), lda, coeff);
		} // j

	} else {

		uint_t n0 = n/2;
		uint_t n1 = n - n0;

		conjugate_recursive_tmpl(n0, ptrmv(lda,a, 0, 0), lda, coeff);
		conjugate_recursive_tmpl(n1, ptrmv(lda,a,n0,n0), lda, coeff);

		conjugate_tmpl(prop_t::GENERAL, n1, n0, ptrmv(lda,a,n0,0), lda, coeff);

	} // dim check
}
/*-------------------------------------------------*/
template <typename T>
static void conjugate_tmpl(prop_t ptype, uint_t m, uint_t n, T *a, uint_t lda, T coeff)
{
	if(!m || !n) return;

	dns_consistency_check(ptype, m, n, a, lda);

	bool lower = Property(ptype).is_lower();

	if(lower) {
		conjugate_recursive_tmpl(n, a, lda, coeff);
	} else {
		mkl::imatcopy('C', 'R', m, n, coeff, a, lda, lda);
	} // lower
}
/*-------------------------------------------------*/
void conjugate(prop_t ptype, uint_t m, uint_t n, real_t *a, uint_t lda, real_t coeff)
{
	WarningNoReach();
	scale(ptype, m, n, a, lda, coeff);
}
/*-------------------------------------------------*/
void conjugate(prop_t ptype, uint_t m, uint_t n, real4_t *a, uint_t lda, real4_t coeff)
{
	WarningNoReach();
	scale(ptype, m, n, a, lda, coeff);
}
/*-------------------------------------------------*/
void conjugate(prop_t ptype, uint_t m, uint_t n, complex_t *a, uint_t lda, complex_t coeff)
{ 
	conjugate_tmpl(ptype, m, n, a, lda, coeff); 
}
/*-------------------------------------------------*/
void conjugate(prop_t ptype, uint_t m, uint_t n, complex8_t *a, uint_t lda, complex8_t coeff)
{ 
	conjugate_tmpl(ptype, m, n, a, lda, coeff); 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void syhe2ge_tmpl(uint_t n, T *a, uint_t lda, bool conjop);
/*-------------------------------------------------*/
template <typename T>
static void syhe2ge_recursive_tmpl(uint_t n, T *a, uint_t lda, bool conjop)
{
	if(!n) return;

	if(n < recursive_min_dim()) {

		if(conjop) {
			for(uint_t j = 0; j < n; j++) {
				for(uint_t i = j+1; i < n; i++) {
					entry(lda,a,j,i) = conj(entry(lda,a,i,j));
				} // i
			} // j
		} else {
			for(uint_t j = 0; j < n; j++) {
				for(uint_t i = j+1; i < n; i++) {
					entry(lda,a,j,i) = entry(lda,a,i,j);
				} // i
			} // j
		} // conjop

	} else {

		uint_t n0 = n/2;
		uint_t n1 = n - n0;

		syhe2ge_recursive_tmpl(n0, ptrmv(lda,a, 0, 0), lda, conjop);
		syhe2ge_recursive_tmpl(n1, ptrmv(lda,a,n0,n0), lda, conjop);

		if(conjop) {
			conjugate_transpose(n0, n1, ptrmv(lda,a,n0,0), lda, ptrmv(lda,a,0,n0), lda);
		} else {
			transpose(n0, n1, ptrmv(lda,a,n0,0), lda, ptrmv(lda,a,0,n0), lda);
		} // conjop

	} // dim check
}
/*-------------------------------------------------*/
template <typename T>
static void syhe2ge_tmpl(uint_t n, T *a, uint_t lda, bool conjop)
{
	syhe2ge_recursive_tmpl(n, a, lda, conjop);
}
/*-------------------------------------------------*/
void sy2ge(uint_t n, real_t *a, uint_t lda) 
{ 
	syhe2ge_tmpl(n, a, lda, false); 
}
/*-------------------------------------------------*/
void sy2ge(uint_t n, real4_t *a, uint_t lda)
{ 
	syhe2ge_tmpl(n, a, lda, false); 
}
/*-------------------------------------------------*/
void sy2ge(uint_t n, complex_t *a, uint_t lda)
{ 
	syhe2ge_tmpl(n, a, lda, false); 
}
/*-------------------------------------------------*/
void sy2ge(uint_t n, complex8_t *a, uint_t lda)
{ 
	syhe2ge_tmpl(n, a, lda, false); 
}
/*-------------------------------------------------*/
void he2ge(uint_t n, real_t *a, uint_t lda)
{ 
	WarningNoReach();
	sy2ge(n, a, lda); 
}
/*-------------------------------------------------*/
void he2ge(uint_t n, real4_t *a, uint_t lda)
{ 
	WarningNoReach();
	sy2ge(n, a, lda); 
}
/*-------------------------------------------------*/
void he2ge(uint_t n, complex_t *a, uint_t lda)
{ 
	syhe2ge_tmpl(n, a, lda, true); 
}
/*-------------------------------------------------*/
void he2ge(uint_t n, complex8_t *a, uint_t lda)
{ 
	syhe2ge_tmpl(n, a, lda, true); 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename Tout, typename Tin>
static Tout norm_one_tmpl(prop_t ptype, uint_t m, uint_t n, const Tin *a, uint_t lda)
{
	if(!m || !n) return 0.;

	Property prop(ptype);
	/**/ if(prop.is_general()  ) return lapack::lange('1',  m , n, a, lda);
	else if(prop.is_symmetric()) return lapack::lansy('1', 'L', n, a, lda);
	else if(prop.is_hermitian()) return lapack::lanhe('1', 'L', n, a, lda);
	
	throw Exception("Invalid property: " + prop.name());
	return 0.;
}
/*-------------------------------------------------*/
template <typename Tout, typename Tin>
static Tout norm_inf_tmpl(prop_t ptype, uint_t m, uint_t n, const Tin *a, uint_t lda)
{
	if(!m || !n) return 0.;

	Property prop(ptype);
	/**/ if(prop.is_general()  ) return lapack::lange('I',  m , n, a, lda);
	else if(prop.is_symmetric()) return lapack::lansy('I', 'L', n, a, lda);
	else if(prop.is_hermitian()) return lapack::lanhe('I', 'L', n, a, lda);
	
	throw Exception("Invalid property: " + prop.name());
	return 0.;
}
/*-------------------------------------------------*/
template <typename Tout, typename Tin>
static Tout norm_max_tmpl(prop_t ptype, uint_t m, uint_t n, const Tin *a, uint_t lda)
{
	if(!m || !n) return 0.;

	Property prop(ptype);
	/**/ if(prop.is_general()  ) return lapack::lange('M',  m , n, a, lda);
	else if(prop.is_symmetric()) return lapack::lansy('M', 'L', n, a, lda);
	else if(prop.is_hermitian()) return lapack::lanhe('M', 'L', n, a, lda);
	
	throw Exception("Invalid property: " + prop.name());
	return 0.;
}
/*-------------------------------------------------*/
template <typename Tout, typename Tin>
static Tout norm_fro_tmpl(prop_t ptype, uint_t m, uint_t n, const Tin *a, uint_t lda)
{
	if(!m || !n) return 0.;

	Property prop(ptype);
	/**/ if(prop.is_general()  ) return lapack::lange('F',  m , n, a, lda);
	else if(prop.is_symmetric()) return lapack::lansy('F', 'L', n, a, lda);
	else if(prop.is_hermitian()) return lapack::lanhe('F', 'L', n, a, lda);
	
	throw Exception("Invalid property: " + prop.name());
	return 0.;
}
/*-------------------------------------------------*/
int_t norm_one(prop_t, uint_t, uint_t, const int_t*, uint_t){ throw Exception("Integer norms not implemented"); return 0; }
int_t norm_inf(prop_t, uint_t, uint_t, const int_t*, uint_t){ throw Exception("Integer norms not implemented"); return 0; }
int_t norm_max(prop_t, uint_t, uint_t, const int_t*, uint_t){ throw Exception("Integer norms not implemented"); return 0; }
int_t norm_fro(prop_t, uint_t, uint_t, const int_t*, uint_t){ throw Exception("Integer norms not implemented"); return 0; }
/*-------------------------------------------------*/
uint_t norm_one(prop_t, uint_t, uint_t, const uint_t*, uint_t){ throw Exception("Integer norms not implemented"); return 0; }
uint_t norm_inf(prop_t, uint_t, uint_t, const uint_t*, uint_t){ throw Exception("Integer norms not implemented"); return 0; }
uint_t norm_max(prop_t, uint_t, uint_t, const uint_t*, uint_t){ throw Exception("Integer norms not implemented"); return 0; }
uint_t norm_fro(prop_t, uint_t, uint_t, const uint_t*, uint_t){ throw Exception("Integer norms not implemented"); return 0; }
/*-------------------------------------------------*/
real_t norm_one(prop_t ptype, uint_t m, uint_t n, const real_t *a, uint_t lda){ return norm_one_tmpl<real_t,real_t>(ptype,m,n,a,lda); }
real_t norm_inf(prop_t ptype, uint_t m, uint_t n, const real_t *a, uint_t lda){ return norm_inf_tmpl<real_t,real_t>(ptype,m,n,a,lda); }
real_t norm_max(prop_t ptype, uint_t m, uint_t n, const real_t *a, uint_t lda){ return norm_max_tmpl<real_t,real_t>(ptype,m,n,a,lda); }
real_t norm_fro(prop_t ptype, uint_t m, uint_t n, const real_t *a, uint_t lda){ return norm_fro_tmpl<real_t,real_t>(ptype,m,n,a,lda); }
/*-------------------------------------------------*/
real4_t norm_one(prop_t ptype, uint_t m, uint_t n, const real4_t *a, uint_t lda){ return norm_one_tmpl<real4_t,real4_t>(ptype,m,n,a,lda); }
real4_t norm_inf(prop_t ptype, uint_t m, uint_t n, const real4_t *a, uint_t lda){ return norm_inf_tmpl<real4_t,real4_t>(ptype,m,n,a,lda); }
real4_t norm_max(prop_t ptype, uint_t m, uint_t n, const real4_t *a, uint_t lda){ return norm_max_tmpl<real4_t,real4_t>(ptype,m,n,a,lda); }
real4_t norm_fro(prop_t ptype, uint_t m, uint_t n, const real4_t *a, uint_t lda){ return norm_fro_tmpl<real4_t,real4_t>(ptype,m,n,a,lda); }
/*-------------------------------------------------*/
real_t norm_one(prop_t ptype, uint_t m, uint_t n, const complex_t *a, uint_t lda){ return norm_one_tmpl<real_t,complex_t>(ptype,m,n,a,lda); }
real_t norm_inf(prop_t ptype, uint_t m, uint_t n, const complex_t *a, uint_t lda){ return norm_inf_tmpl<real_t,complex_t>(ptype,m,n,a,lda); }
real_t norm_max(prop_t ptype, uint_t m, uint_t n, const complex_t *a, uint_t lda){ return norm_max_tmpl<real_t,complex_t>(ptype,m,n,a,lda); }
real_t norm_fro(prop_t ptype, uint_t m, uint_t n, const complex_t *a, uint_t lda){ return norm_fro_tmpl<real_t,complex_t>(ptype,m,n,a,lda); }
/*-------------------------------------------------*/
real4_t norm_one(prop_t ptype, uint_t m, uint_t n, const complex8_t *a, uint_t lda){ return norm_one_tmpl<real4_t,complex8_t>(ptype,m,n,a,lda); }
real4_t norm_inf(prop_t ptype, uint_t m, uint_t n, const complex8_t *a, uint_t lda){ return norm_inf_tmpl<real4_t,complex8_t>(ptype,m,n,a,lda); }
real4_t norm_max(prop_t ptype, uint_t m, uint_t n, const complex8_t *a, uint_t lda){ return norm_max_tmpl<real4_t,complex8_t>(ptype,m,n,a,lda); }
real4_t norm_fro(prop_t ptype, uint_t m, uint_t n, const complex8_t *a, uint_t lda){ return norm_fro_tmpl<real4_t,complex8_t>(ptype,m,n,a,lda); }
/*-------------------------------------------------*/
int_t   norm_euc(uint_t, const int_t *) { throw Exception("Integer norms not implemented"); return 0; }
uint_t  norm_euc(uint_t, const uint_t*) { throw Exception("Integer norms not implemented"); return 0; }
/*-------------------------------------------------*/
real_t  norm_euc(uint_t n, const real_t     *a) { return blas::nrm2(n, a, 1); }
real4_t norm_euc(uint_t n, const real4_t    *a) { return blas::nrm2(n, a, 1); }
real_t  norm_euc(uint_t n, const complex_t  *a) { return blas::nrm2(n, a, 1); }
real4_t norm_euc(uint_t n, const complex8_t *a) { return blas::nrm2(n, a, 1); }
/*-------------------------------------------------*/
template <typename T>
static void permute_ge_right_tmpl(uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, const uint_t *P)
{
	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < m; i++) {
			entry(ldb, b, P[i], j) = entry(lda, a, i, j);
		} // i
	} // j
}
/*-------------------------------------------------*/
template <typename T>
static void permute_ge_left_tmpl(uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, const uint_t *Q)
{
	for(uint_t j = 0; j < n; j++) {
		copy(prop_t::GENERAL, m, 1, ptrmv(lda,a,0,j), lda, ptrmv(ldb,b,0,Q[j]), ldb);
	} // j
}
/*-------------------------------------------------*/
template <typename T>
static void permute_ge_both_tmpl(uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, const uint_t *P, const uint_t *Q)
{
	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < m; i++) {
			entry(ldb, b, P[i], Q[j]) = entry(lda, a, i, j);
		} // i
	} // j
}
/*-------------------------------------------------*/
template <typename T>
static void permute_syhe_tmpl(uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, const uint_t *P, bool conjop)
{
	uint_t Pi;
	uint_t Pj;
	T      Aij;

	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = j; i < n; i++) {

			Pi  = P[i];
			Pj  = P[j];
			Aij = entry(lda,a,i,j);

			if(Pj > Pi) {
				entry(ldb,b,Pj,Pi) = (conjop ? conj(Aij) : Aij);
			} else {
				entry(ldb,b,Pi,Pj) = Aij;
			} // upper/lower 

		} // i
	} // j
}
/*-------------------------------------------------*/
template <typename T>
static void permute_tmpl(prop_t ptype, uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, const uint_t *P, const uint_t *Q)
{
	if(!m || !n) return;

	dns_consistency_check(ptype, m, n, a, lda);

	Property prop(ptype);

	if(prop.is_general()) {

		/**/ if( P &&  Q) permute_ge_both_tmpl (m, n, a, lda, b, ldb, P, Q);
		else if( P && !Q) permute_ge_right_tmpl(m, n, a, lda, b, ldb, P);
		else if(!P &&  Q) permute_ge_left_tmpl (m, n, a, lda, b, ldb, Q);
		else              copy(ptype, m, n, a, lda, b, ldb);

	} else if(prop.is_symmetric()) {

		if(P) permute_syhe_tmpl(n, a, lda, b, ldb, P, false);
		else  copy(ptype, m, n, a, lda, b, ldb);

	} else if(prop.is_hermitian()) {

		if(P) permute_syhe_tmpl(n, a, lda, b, ldb, P, true);
		else  copy(ptype, m, n, a, lda, b, ldb);

	} else {

		throw Exception("Invalid property: " + prop.name());

	} // prop
}
/*-------------------------------------------------*/
void permute(prop_t ptype, uint_t m, uint_t n, const int_t *a, uint_t lda, int_t *b, uint_t ldb, const uint_t *P, const uint_t *Q)
{
	permute_tmpl(ptype, m, n, a, lda, b, ldb, P, Q); 
}
/*-------------------------------------------------*/
void permute(prop_t ptype, uint_t m, uint_t n, const uint_t *a, uint_t lda, uint_t *b, uint_t ldb, const uint_t *P, const uint_t *Q)
{
	permute_tmpl(ptype, m, n, a, lda, b, ldb, P, Q); 
}
/*-------------------------------------------------*/
void permute(prop_t ptype, uint_t m, uint_t n, const real_t *a, uint_t lda, real_t *b, uint_t ldb, const uint_t *P, const uint_t *Q)
{
	permute_tmpl(ptype, m, n, a, lda, b, ldb, P, Q); 
}
/*-------------------------------------------------*/
void permute(prop_t ptype, uint_t m, uint_t n, const real4_t *a, uint_t lda, real4_t *b, uint_t ldb, const uint_t *P, const uint_t *Q)
{
	permute_tmpl(ptype, m, n, a, lda, b, ldb, P, Q); 
}
/*-------------------------------------------------*/
void permute(prop_t ptype, uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, const uint_t *P, const uint_t *Q)
{
	permute_tmpl(ptype, m, n, a, lda, b, ldb, P, Q); 
}
/*-------------------------------------------------*/
void permute(prop_t ptype, uint_t m, uint_t n, const complex8_t *a, uint_t lda, complex8_t *b, uint_t ldb, const uint_t *P, const uint_t *Q)
{ 
	permute_tmpl(ptype, m, n, a, lda, b, ldb, P, Q); 
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/
