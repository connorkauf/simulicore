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
static void naive_fill_tmpl(uplo_t uplo, uint_t m, uint_t n, T *a, uint_t lda, T val, T dval)
{
	if(!m || !n) return;

	if(m == lda && uplo == uplo_t::F) {
		std::fill_n(a, m * n, val);
	} else {
		for(uint_t j = 0; j < n; j++) {
			RowRange ir = irange(uplo, m, j);
			if(ir.ilen) {
				std::fill_n(ptrmv(lda,a,ir.ibgn,j), ir.ilen, val);
			} // ilen
		} // j
	} // m = lda

	for(uint_t j = 0; j < std::min(m,n); j++) {
		entry(lda,a,j,j) = dval;
	} // j
}
/*-------------------------------------------------*/
template <typename T>
static void fill_tmpl(uplo_t uplo, uint_t m, uint_t n, T *a, uint_t lda, T val, T dval)
{
	if(!m || !n) return;

	int_t info = lapack::laset(static_cast<char>(uplo), m, n, val, dval, a, lda);

	if(info) {
		throw Exception(msg::lapack_error() + " (info:" + std::to_string(info) + ")");
	} // info
}
/*-------------------------------------------------*/
void fill(uplo_t uplo, uint_t m, uint_t n, int_t      *a, uint_t lda, int_t      val){ naive_fill_tmpl(uplo, m, n, a, lda, val, val); }
void fill(uplo_t uplo, uint_t m, uint_t n, uint_t     *a, uint_t lda, uint_t     val){ naive_fill_tmpl(uplo, m, n, a, lda, val, val); }
void fill(uplo_t uplo, uint_t m, uint_t n, real_t     *a, uint_t lda, real_t     val){       fill_tmpl(uplo, m, n, a, lda, val, val); }
void fill(uplo_t uplo, uint_t m, uint_t n, real4_t    *a, uint_t lda, real4_t    val){       fill_tmpl(uplo, m, n, a, lda, val, val); }
void fill(uplo_t uplo, uint_t m, uint_t n, complex_t  *a, uint_t lda, complex_t  val){       fill_tmpl(uplo, m, n, a, lda, val, val); }
void fill(uplo_t uplo, uint_t m, uint_t n, complex8_t *a, uint_t lda, complex8_t val){       fill_tmpl(uplo, m, n, a, lda, val, val); }
/*-------------------------------------------------*/
void fill(uplo_t uplo, uint_t m, uint_t n, int_t      *a, uint_t lda, int_t      val, int_t      dval){ naive_fill_tmpl(uplo, m, n, a, lda, val, dval); }
void fill(uplo_t uplo, uint_t m, uint_t n, uint_t     *a, uint_t lda, uint_t     val, uint_t     dval){ naive_fill_tmpl(uplo, m, n, a, lda, val, dval); }
void fill(uplo_t uplo, uint_t m, uint_t n, real_t     *a, uint_t lda, real_t     val, real_t     dval){       fill_tmpl(uplo, m, n, a, lda, val, dval); }
void fill(uplo_t uplo, uint_t m, uint_t n, real4_t    *a, uint_t lda, real4_t    val, real4_t    dval){       fill_tmpl(uplo, m, n, a, lda, val, dval); }
void fill(uplo_t uplo, uint_t m, uint_t n, complex_t  *a, uint_t lda, complex_t  val, complex_t  dval){       fill_tmpl(uplo, m, n, a, lda, val, dval); }
void fill(uplo_t uplo, uint_t m, uint_t n, complex8_t *a, uint_t lda, complex8_t val, complex8_t dval){       fill_tmpl(uplo, m, n, a, lda, val, dval); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T, typename Tr>
static void rand_tmpl(uplo_t uplo, uint_t m, uint_t n, T *a, uint_t lda, 
		Tr low, Tr high, const std::function<T (Tr low, Tr high)>& randfun)
{
	if(!m || !n) return;

	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange(uplo, m, j);
		for(uint_t i = ir.ibgn; i < ir.iend; i++) {
			entry(lda,a,i,j) = randfun(low, high);
		} // j
	} // j
}
/*-------------------------------------------------*/
void rand(uplo_t uplo, uint_t m, uint_t n, int_t      *a, uint_t lda, int_t   low, int_t   high){ rand_tmpl<int_t     ,int_t  >(uplo, m, n, a, lda, low, high, irand); }
void rand(uplo_t uplo, uint_t m, uint_t n, uint_t     *a, uint_t lda, uint_t  low, uint_t  high){ rand_tmpl<uint_t    ,uint_t >(uplo, m, n, a, lda, low, high, urand); }
void rand(uplo_t uplo, uint_t m, uint_t n, real_t     *a, uint_t lda, real_t  low, real_t  high){ rand_tmpl<real_t    ,real_t >(uplo, m, n, a, lda, low, high, drand); }
void rand(uplo_t uplo, uint_t m, uint_t n, real4_t    *a, uint_t lda, real4_t low, real4_t high){ rand_tmpl<real4_t   ,real4_t>(uplo, m, n, a, lda, low, high, srand); }
void rand(uplo_t uplo, uint_t m, uint_t n, complex_t  *a, uint_t lda, real_t  low, real_t  high){ rand_tmpl<complex_t ,real_t >(uplo, m, n, a, lda, low, high, zrand); }
void rand(uplo_t uplo, uint_t m, uint_t n, complex8_t *a, uint_t lda, real4_t low, real4_t high){ rand_tmpl<complex8_t,real4_t>(uplo, m, n, a, lda, low, high, crand); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void copy_tmpl(uplo_t uplo, uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, T coeff)
{
	if(!m || !n) return;

	if(uplo == uplo_t::F) {
		mkl::omatcopy('C', 'N', m, n, coeff, a, lda, b, ldb);
	} else {
		int_t info = lapack::lacpy(static_cast<char>(uplo), m, n, a, lda, b, ldb);
		if(info) {
			throw Exception(msg::lapack_error() + " (info:" + std::to_string(info) + ")");
		} // info
		scale(uplo, m, n, b, ldb, coeff);
	} // uplo
}
/*-------------------------------------------------*/
template <typename T>
static void naive_copy_tmpl(uplo_t uplo, uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, T coeff)
{
	// 
	// TODO: more efficiently
	//
	if(!m || !n) return;

	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange(uplo, m, j);
		for(uint_t i = ir.ibgn; i < ir.iend; i++) {
			entry(ldb,b,i,j) = coeff * entry(lda,a,i,j);
		} // i
	} // j
}
/*-------------------------------------------------*/
void copy(uplo_t uplo, uint_t m, uint_t n, const int_t *a, uint_t lda, int_t *b, uint_t ldb, int_t coeff)
{
	naive_copy_tmpl(uplo, m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void copy(uplo_t uplo, uint_t m, uint_t n, const uint_t *a, uint_t lda, uint_t *b, uint_t ldb, uint_t coeff)
{
	naive_copy_tmpl(uplo, m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void copy(uplo_t uplo, uint_t m, uint_t n, const real_t *a, uint_t lda, real_t *b, uint_t ldb, real_t coeff)
{
	copy_tmpl(uplo, m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void copy(uplo_t uplo, uint_t m, uint_t n, const real4_t *a, uint_t lda, real4_t *b, uint_t ldb, real4_t coeff)
{ 
	copy_tmpl(uplo, m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void copy(uplo_t uplo, uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, complex_t coeff)
{
	copy_tmpl(uplo, m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
void copy(uplo_t uplo, uint_t m, uint_t n, const complex8_t *a, uint_t lda, complex8_t *b, uint_t ldb, complex8_t coeff)
{ 
	copy_tmpl(uplo, m, n, a, lda, b, ldb, coeff); 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T, typename Tr>
static void get_real_part_tmpl(uplo_t uplo, uint_t m, uint_t n, const T *a, uint_t lda, Tr *b, uint_t ldb)
{
	if(!m || !n) return;

	if(uplo == uplo_t::F) {
		mkl::omatcopy('C', 'N', m, n, 1, reinterpret_cast<const Tr*>(a), 2 * lda, 2, b, ldb, 1);
	} else {
		for(uint_t j = 0; j < n; j++) {
			RowRange ir = irange(uplo, m, j);
			blas::copy(ir.ilen, reinterpret_cast<const Tr*>(ptrmv(lda,a,j,j)), 2, b, 1);
		} // j
	}
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
static void set_real_part_tmpl(uplo_t uplo, uint_t m, uint_t n, const Tr *a, uint_t lda, T *b, uint_t ldb)
{
	if(!m || !n) return;

	if(uplo == uplo_t::F) {
		mkl::omatcopy('C', 'N', m, n, 1, a, lda, 1, reinterpret_cast<Tr*>(b), 2 * ldb, 2);
	} else {
		for(uint_t j = 0; j < n; j++) {
			RowRange ir = irange(uplo, m, j);
			blas::copy(ir.ilen, a, 1, reinterpret_cast<Tr*>(ptrmv(lda,b,j,j)), 2);
		} // j
	}
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
static void get_imag_part_tmpl(uplo_t uplo, uint_t m, uint_t n, const T *a, uint_t lda, Tr *b, uint_t ldb)
{
	if(!m || !n) return;

	if(uplo == uplo_t::F) {
		mkl::omatcopy('C', 'N', m, n, 1, reinterpret_cast<const Tr*>(a) + 1, 2 * lda, 2, b, ldb, 1);
	} else {
		for(uint_t j = 0; j < n; j++) {
			RowRange ir = irange(uplo, m, j);
			blas::copy(ir.ilen, reinterpret_cast<const Tr*>(ptrmv(lda,a,j,j)) + 1, 2, b, 1);
		} // j
	}
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
static void set_imag_part_tmpl(uplo_t uplo, uint_t m, uint_t n, const Tr *a, uint_t lda, T *b, uint_t ldb)
{
	if(!m || !n) return;

	if(uplo == uplo_t::F) {
		mkl::omatcopy('C', 'N', m, n, 1, a, lda, 1, reinterpret_cast<Tr*>(b) + 1, 2 * ldb, 2);
	} else {
		for(uint_t j = 0; j < n; j++) {
			RowRange ir = irange(uplo, m, j);
			blas::copy(ir.ilen, a, 1, reinterpret_cast<Tr*>(ptrmv(lda,b,j,j)) + 1, 2);
		} // j
	}
}
/*-------------------------------------------------*/
void get_real(uplo_t, uint_t, uint_t, const int_t  *, uint_t, int_t  *, uint_t) { throw Exception(msg::op_not_allowed()); }
void get_real(uplo_t, uint_t, uint_t, const uint_t *, uint_t, uint_t *, uint_t) { throw Exception(msg::op_not_allowed()); }
void get_real(uplo_t, uint_t, uint_t, const real_t *, uint_t, real_t *, uint_t) { throw Exception(msg::op_not_allowed()); }
void get_real(uplo_t, uint_t, uint_t, const real4_t*, uint_t, real4_t*, uint_t) { throw Exception(msg::op_not_allowed()); }
/*-------------------------------------------------*/
void get_imag(uplo_t, uint_t, uint_t, const int_t  *, uint_t, int_t  *, uint_t) { throw Exception(msg::op_not_allowed()); }
void get_imag(uplo_t, uint_t, uint_t, const uint_t *, uint_t, uint_t *, uint_t) { throw Exception(msg::op_not_allowed()); }
void get_imag(uplo_t, uint_t, uint_t, const real_t *, uint_t, real_t *, uint_t) { throw Exception(msg::op_not_allowed()); }
void get_imag(uplo_t, uint_t, uint_t, const real4_t*, uint_t, real4_t*, uint_t) { throw Exception(msg::op_not_allowed()); }
/*-------------------------------------------------*/
void set_real(uplo_t, uint_t, uint_t, const int_t  *, uint_t, int_t  *, uint_t) { throw Exception(msg::op_not_allowed()); }
void set_real(uplo_t, uint_t, uint_t, const uint_t *, uint_t, uint_t *, uint_t) { throw Exception(msg::op_not_allowed()); }
void set_real(uplo_t, uint_t, uint_t, const real_t *, uint_t, real_t *, uint_t) { throw Exception(msg::op_not_allowed()); }
void set_real(uplo_t, uint_t, uint_t, const real4_t*, uint_t, real4_t*, uint_t) { throw Exception(msg::op_not_allowed()); }
/*-------------------------------------------------*/
void set_imag(uplo_t, uint_t, uint_t, const int_t  *, uint_t, int_t  *, uint_t) { throw Exception(msg::op_not_allowed()); }
void set_imag(uplo_t, uint_t, uint_t, const uint_t *, uint_t, uint_t *, uint_t) { throw Exception(msg::op_not_allowed()); }
void set_imag(uplo_t, uint_t, uint_t, const real_t *, uint_t, real_t *, uint_t) { throw Exception(msg::op_not_allowed()); }
void set_imag(uplo_t, uint_t, uint_t, const real4_t*, uint_t, real4_t*, uint_t) { throw Exception(msg::op_not_allowed()); }
/*-------------------------------------------------*/
void get_real(uplo_t uplo, uint_t m, uint_t n, const complex_t  *a, uint_t lda, real_t  *b, uint_t ldb) { get_real_part_tmpl(uplo, m, n, a, lda, b, ldb); }
void get_real(uplo_t uplo, uint_t m, uint_t n, const complex8_t *a, uint_t lda, real4_t *b, uint_t ldb) { get_real_part_tmpl(uplo, m, n, a, lda, b, ldb); }
void get_imag(uplo_t uplo, uint_t m, uint_t n, const complex_t  *a, uint_t lda, real_t  *b, uint_t ldb) { get_imag_part_tmpl(uplo, m, n, a, lda, b, ldb); }
void get_imag(uplo_t uplo, uint_t m, uint_t n, const complex8_t *a, uint_t lda, real4_t *b, uint_t ldb) { get_imag_part_tmpl(uplo, m, n, a, lda, b, ldb); }
/*-------------------------------------------------*/
void set_real(uplo_t uplo, uint_t m, uint_t n, const real_t  *a, uint_t lda, complex_t  *b, uint_t ldb) { set_real_part_tmpl(uplo, m, n, a, lda, b, ldb); }
void set_real(uplo_t uplo, uint_t m, uint_t n, const real4_t *a, uint_t lda, complex8_t *b, uint_t ldb) { set_real_part_tmpl(uplo, m, n, a, lda, b, ldb); }
void set_imag(uplo_t uplo, uint_t m, uint_t n, const real_t  *a, uint_t lda, complex_t  *b, uint_t ldb) { set_imag_part_tmpl(uplo, m, n, a, lda, b, ldb); }
void set_imag(uplo_t uplo, uint_t m, uint_t n, const real4_t *a, uint_t lda, complex8_t *b, uint_t ldb) { set_imag_part_tmpl(uplo, m, n, a, lda, b, ldb); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template<typename T>
static void recursive_scale_tmpl(uplo_t uplo, uint_t n, T *a, uint_t lda, T coeff)
{
	if(!n) return;

	if(n < recursive_min_dim()) {

		for(uint_t j = 0; j < n; j++) {
			RowRange ir = irange(uplo, n, j);
			mkl::imatcopy('C', 'N', ir.ilen, 1, coeff, ptrmv(lda,a,ir.ibgn,j), lda, lda);
		} // j

	} else {

		uint_t n0 = n/2;
		uint_t n1 = n - n0;

		recursive_scale_tmpl(uplo, n0, ptrmv(lda,a, 0, 0), lda, coeff);
		recursive_scale_tmpl(uplo, n1, ptrmv(lda,a,n0,n0), lda, coeff);

		if(uplo == uplo_t::U) scale(uplo_t::F, n0, n1, ptrmv(lda,a,0,n0), lda, coeff);
		if(uplo == uplo_t::L) scale(uplo_t::F, n1, n0, ptrmv(lda,a,n0,0), lda, coeff);

	} // dim check
}
/*-------------------------------------------------*/
template <typename T>
static void scale_tmpl(uplo_t uplo, uint_t m, uint_t n, T *a, uint_t lda, T coeff)
{
	if(!m || !n) return;

	T coeff_one = 1;
	if(coeff == coeff_one) {
		return;
	} // coeff = 1

	T coeff_zero = 0;
	if(coeff == coeff_zero) {
		zero(uplo, m, n, a, lda);
		return;
	} // coeff = 0
	
	if(uplo == uplo_t::F) {
		mkl::imatcopy('C', 'N', m, n, coeff, a, lda, lda);
	} else {
		uint_t k = std::min(m,n);
		recursive_scale_tmpl(uplo, k, a, lda, coeff);
		if(uplo == uplo_t::U) scale(uplo_t::F, m  , n-k, ptrmv(lda,a,0,k), lda, coeff);
		if(uplo == uplo_t::L) scale(uplo_t::F, m-k, n  , ptrmv(lda,a,k,0), lda, coeff);
	} // uplo
}
/*-------------------------------------------------*/
template <typename T>
static void naive_scale_tmpl(uplo_t uplo, uint_t m, uint_t n, T *a, uint_t lda, T coeff)
{
	// 
	// TODO: more efficiently
	//
	if(!m || !n) return;

	T coeff_one = 1;
	if(coeff == coeff_one) {
		return;
	} // coeff = 1

	T coeff_zero = 0;
	if(coeff == coeff_zero) {
		zero(uplo, m, n, a, lda);
		return;
	} // coeff = 0

	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange(uplo, m, j);
		for(uint_t i = ir.ibgn; i < ir.iend; i++) {
			entry(lda,a,i,j) = coeff * entry(lda,a,i,j);
		} // i
	} // j
}
/*-------------------------------------------------*/
void scale(uplo_t uplo, uint_t m, uint_t n, int_t      *a, uint_t lda, int_t      coeff) { naive_scale_tmpl(uplo, m, n, a, lda, coeff); }
void scale(uplo_t uplo, uint_t m, uint_t n, uint_t     *a, uint_t lda, uint_t     coeff) { naive_scale_tmpl(uplo, m, n, a, lda, coeff); }
void scale(uplo_t uplo, uint_t m, uint_t n, real_t     *a, uint_t lda, real_t     coeff) {       scale_tmpl(uplo, m, n, a, lda, coeff); }
void scale(uplo_t uplo, uint_t m, uint_t n, real4_t    *a, uint_t lda, real4_t    coeff) {       scale_tmpl(uplo, m, n, a, lda, coeff); }
void scale(uplo_t uplo, uint_t m, uint_t n, complex_t  *a, uint_t lda, complex_t  coeff) {       scale_tmpl(uplo, m, n, a, lda, coeff); }
void scale(uplo_t uplo, uint_t m, uint_t n, complex8_t *a, uint_t lda, complex8_t coeff) {       scale_tmpl(uplo, m, n, a, lda, coeff); }
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
	// 
	// TODO: more efficiently
	//
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
void conjugate_transpose(uint_t, uint_t, const int_t  *, uint_t, int_t  *, uint_t, int_t  ) { throw Exception(msg::op_not_allowed()); }
void conjugate_transpose(uint_t, uint_t, const uint_t *, uint_t, uint_t *, uint_t, uint_t ) { throw Exception(msg::op_not_allowed()); }
void conjugate_transpose(uint_t, uint_t, const real_t *, uint_t, real_t *, uint_t, real_t ) { throw Exception(msg::op_not_allowed()); }
void conjugate_transpose(uint_t, uint_t, const real4_t*, uint_t, real4_t*, uint_t, real4_t) { throw Exception(msg::op_not_allowed()); }
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
template<typename T>
static void recursive_conjugate_tmpl(uplo_t uplo, uint_t n, T *a, uint_t lda, T coeff)
{
	if(!n) return;

	if(n < recursive_min_dim()) {

		for(uint_t j = 0; j < n; j++) {
			RowRange ir = irange(uplo, n, j);
			mkl::imatcopy('C', 'R', ir.ilen, 1, coeff, ptrmv(lda,a,ir.ibgn,j), lda, lda);
		} // j

	} else {

		uint_t n0 = n/2;
		uint_t n1 = n - n0;

		recursive_conjugate_tmpl(uplo, n0, ptrmv(lda,a, 0, 0), lda, coeff);
		recursive_conjugate_tmpl(uplo, n1, ptrmv(lda,a,n0,n0), lda, coeff);

		if(uplo == uplo_t::U) conjugate(uplo_t::F, n0, n1, ptrmv(lda,a,0,n0), lda, coeff);
		if(uplo == uplo_t::L) conjugate(uplo_t::F, n1, n0, ptrmv(lda,a,n0,0), lda, coeff);

	} // dim check
}
/*-------------------------------------------------*/
template <typename T>
static void conjugate_tmpl(uplo_t uplo, uint_t m, uint_t n, T *a, uint_t lda, T coeff)
{
	if(!m || !n) return;

	if(uplo == uplo_t::F) {
		mkl::imatcopy('C', 'R', m, n, coeff, a, lda, lda);
	} else {
		uint_t k = std::min(m,n);
		recursive_conjugate_tmpl(uplo, k, a, lda, coeff);
		if(uplo == uplo_t::U) conjugate(uplo_t::F, m  , n-k, ptrmv(lda,a,0,k), lda, coeff);
		if(uplo == uplo_t::L) conjugate(uplo_t::F, m-k, n  , ptrmv(lda,a,k,0), lda, coeff);
	} // lower
}
/*-------------------------------------------------*/
void conjugate(uplo_t, uint_t, uint_t, real_t *, uint_t, real_t ) { throw Exception(msg::op_not_allowed()); }
void conjugate(uplo_t, uint_t, uint_t, real4_t*, uint_t, real4_t) { throw Exception(msg::op_not_allowed()); }
/*-------------------------------------------------*/
void conjugate(uplo_t uplo, uint_t m, uint_t n, complex_t *a, uint_t lda, complex_t coeff)
{ 
	conjugate_tmpl(uplo, m, n, a, lda, coeff); 
}
/*-------------------------------------------------*/
void conjugate(uplo_t uplo, uint_t m, uint_t n, complex8_t *a, uint_t lda, complex8_t coeff)
{ 
	conjugate_tmpl(uplo, m, n, a, lda, coeff); 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T>
static void syhe2ge_tmpl(uint_t n, T *a, uint_t lda, bool conjop);
/*-------------------------------------------------*/
template <typename T>
static void syhe2ge_recursive_tmpl(uplo_t uplo, uint_t n, T *a, uint_t lda, bool conjop)
{
	if(!n) return;

	if(n < recursive_min_dim()) {

		if(conjop) {
			for(uint_t j = 0; j < n; j++) {
				RowRange ir = irange(uplo, n, j);
				for(uint_t i = ir.ibgn; i < ir.iend; i++) {
					entry(lda,a,j,i) = conj(entry(lda,a,i,j));
				} // i
			} // j
		} else {
			for(uint_t j = 0; j < n; j++) {
				RowRange ir = irange(uplo, n, j);
				for(uint_t i = ir.ibgn; i < ir.iend; i++) {
					entry(lda,a,j,i) = entry(lda,a,i,j);
				} // i
			} // j
		} // conjop

	} else {

		uint_t n0 = n/2;
		uint_t n1 = n - n0;

		syhe2ge_recursive_tmpl(uplo, n0, ptrmv(lda,a, 0, 0), lda, conjop);
		syhe2ge_recursive_tmpl(uplo, n1, ptrmv(lda,a,n0,n0), lda, conjop);

		if(conjop) {
			if(uplo == uplo_t::U) conjugate_transpose(n0, n1, ptrmv(lda,a,0,n0), lda, ptrmv(lda,a,n0,0), lda);
			if(uplo == uplo_t::L) conjugate_transpose(n1, n0, ptrmv(lda,a,n0,0), lda, ptrmv(lda,a,0,n0), lda);
		} else {
			if(uplo == uplo_t::U) transpose(n0, n1, ptrmv(lda,a,0,n0), lda, ptrmv(lda,a,n0,0), lda);
			if(uplo == uplo_t::L) transpose(n1, n0, ptrmv(lda,a,n0,0), lda, ptrmv(lda,a,0,n0), lda);
		} // conjop

	} // dim check
}
/*-------------------------------------------------*/
template <typename T>
static void syhe2ge_tmpl(uplo_t uplo, uint_t n, T *a, uint_t lda, bool conjop)
{
	syhe2ge_recursive_tmpl(uplo, n, a, lda, conjop);
}
/*-------------------------------------------------*/
void sy2ge(uplo_t uplo, uint_t n, int_t      *a, uint_t lda) { syhe2ge_tmpl(uplo, n, a, lda, false); }
void sy2ge(uplo_t uplo, uint_t n, uint_t     *a, uint_t lda) { syhe2ge_tmpl(uplo, n, a, lda, false); }
void sy2ge(uplo_t uplo, uint_t n, real_t     *a, uint_t lda) { syhe2ge_tmpl(uplo, n, a, lda, false); }
void sy2ge(uplo_t uplo, uint_t n, real4_t    *a, uint_t lda) { syhe2ge_tmpl(uplo, n, a, lda, false); }
void sy2ge(uplo_t uplo, uint_t n, complex_t  *a, uint_t lda) { syhe2ge_tmpl(uplo, n, a, lda, false); }
void sy2ge(uplo_t uplo, uint_t n, complex8_t *a, uint_t lda) { syhe2ge_tmpl(uplo, n, a, lda, false); }
/*-------------------------------------------------*/
void he2ge(uplo_t, uint_t, int_t  *, uint_t) { throw Exception(msg::op_not_allowed()); }
void he2ge(uplo_t, uint_t, uint_t *, uint_t) { throw Exception(msg::op_not_allowed()); }
void he2ge(uplo_t, uint_t, real_t *, uint_t) { throw Exception(msg::op_not_allowed()); }
void he2ge(uplo_t, uint_t, real4_t*, uint_t) { throw Exception(msg::op_not_allowed()); }
/*-------------------------------------------------*/
void he2ge(uplo_t uplo, uint_t n, complex_t  *a, uint_t lda) { syhe2ge_tmpl(uplo, n, a, lda, true); }
void he2ge(uplo_t uplo, uint_t n, complex8_t *a, uint_t lda) { syhe2ge_tmpl(uplo, n, a, lda, true); }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename Tout, typename Tin>
static Tout norm_one_tmpl(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const Tin *a, uint_t lda)
{
	if(!m || !n) return 0.;

	Property prop(ptype, uplo);
	/**/ if(prop.isGeneral()  ) return lapack::lange('1', m, n, a, lda);
	else if(prop.isSymmetric()) return lapack::lansy('1', prop.cuplo(), n, a, lda);
	else if(prop.isHermitian()) return lapack::lanhe('1', prop.cuplo(), n, a, lda);
	
	throw Exception("Invalid property: " + prop.name());
	return 0.;
}
/*-------------------------------------------------*/
template <typename Tout, typename Tin>
static Tout norm_inf_tmpl(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const Tin *a, uint_t lda)
{
	if(!m || !n) return 0.;

	Property prop(ptype, uplo);
	/**/ if(prop.isGeneral()  ) return lapack::lange('I', m, n, a, lda);
	else if(prop.isSymmetric()) return lapack::lansy('I', prop.cuplo(), n, a, lda);
	else if(prop.isHermitian()) return lapack::lanhe('I', prop.cuplo(), n, a, lda);
	
	throw Exception("Invalid property: " + prop.name());
	return 0.;
}
/*-------------------------------------------------*/
template <typename Tout, typename Tin>
static Tout norm_max_tmpl(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const Tin *a, uint_t lda)
{
	if(!m || !n) return 0.;

	Property prop(ptype, uplo);
	/**/ if(prop.isGeneral()  ) return lapack::lange('M', m, n, a, lda);
	else if(prop.isSymmetric()) return lapack::lansy('M', prop.cuplo(), n, a, lda);
	else if(prop.isHermitian()) return lapack::lanhe('M', prop.cuplo(), n, a, lda);
	
	throw Exception("Invalid property: " + prop.name());
	return 0.;
}
/*-------------------------------------------------*/
//
// FRO NORM FOR SYMMETRIC/HERMITIAN WRONG IN LAPACK FOR N >=128
// TODO: more efficient
//
template <typename Tout, typename Tin>
static Tout naive_syhe_norm_fro_tmpl(uplo_t uplo, uint_t n, const Tin *a, uint_t lda)
{
	Tout sum = 0;
	Tout two = 2;
	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange(uplo, n, j);
		for(uint_t i = ir.ibgn; i < ir.iend; i++) {
			Tout aij = std::abs(entry(lda,a,i,j));
			sum += (i != j) ? two * aij * aij : aij * aij;
		} // i
	} // j
	return std::sqrt(sum);
}
/*-------------------------------------------------*/
template <typename Tout, typename Tin>
static Tout norm_fro_tmpl(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const Tin *a, uint_t lda)
{
	if(!m || !n) return 0.;

	Property prop(ptype, uplo);
	/**/ if(prop.isGeneral()  ) return lapack::lange('F', m, n, a, lda);
	else if(prop.isSymmetric()) return (n >= 128 ? naive_syhe_norm_fro_tmpl<Tout,Tin>(uplo, n, a, lda) : lapack::lansy('F', prop.cuplo(), n, a, lda));
	else if(prop.isHermitian()) return (n >= 128 ? naive_syhe_norm_fro_tmpl<Tout,Tin>(uplo, n, a, lda) : lapack::lanhe('F', prop.cuplo(), n, a, lda));
	
	throw Exception("Invalid property: " + prop.name());
	return 0.;
}
/*-------------------------------------------------*/
int_t norm_one(prop_t, uplo_t, uint_t, uint_t, const int_t*, uint_t){ throw Exception(msg::op_not_allowed()); return 0; }
int_t norm_inf(prop_t, uplo_t, uint_t, uint_t, const int_t*, uint_t){ throw Exception(msg::op_not_allowed()); return 0; }
int_t norm_max(prop_t, uplo_t, uint_t, uint_t, const int_t*, uint_t){ throw Exception(msg::op_not_allowed()); return 0; }
int_t norm_fro(prop_t, uplo_t, uint_t, uint_t, const int_t*, uint_t){ throw Exception(msg::op_not_allowed()); return 0; }
/*-------------------------------------------------*/
uint_t norm_one(prop_t, uplo_t, uint_t, uint_t, const uint_t*, uint_t){ throw Exception(msg::op_not_allowed()); return 0; }
uint_t norm_inf(prop_t, uplo_t, uint_t, uint_t, const uint_t*, uint_t){ throw Exception(msg::op_not_allowed()); return 0; }
uint_t norm_max(prop_t, uplo_t, uint_t, uint_t, const uint_t*, uint_t){ throw Exception(msg::op_not_allowed()); return 0; }
uint_t norm_fro(prop_t, uplo_t, uint_t, uint_t, const uint_t*, uint_t){ throw Exception(msg::op_not_allowed()); return 0; }
/*-------------------------------------------------*/
real_t norm_one(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const real_t *a, uint_t lda){ return norm_one_tmpl<real_t,real_t>(ptype,uplo,m,n,a,lda); }
real_t norm_inf(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const real_t *a, uint_t lda){ return norm_inf_tmpl<real_t,real_t>(ptype,uplo,m,n,a,lda); }
real_t norm_max(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const real_t *a, uint_t lda){ return norm_max_tmpl<real_t,real_t>(ptype,uplo,m,n,a,lda); }
real_t norm_fro(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const real_t *a, uint_t lda){ return norm_fro_tmpl<real_t,real_t>(ptype,uplo,m,n,a,lda); }
/*-------------------------------------------------*/
real4_t norm_one(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const real4_t *a, uint_t lda){ return norm_one_tmpl<real4_t,real4_t>(ptype,uplo,m,n,a,lda); }
real4_t norm_inf(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const real4_t *a, uint_t lda){ return norm_inf_tmpl<real4_t,real4_t>(ptype,uplo,m,n,a,lda); }
real4_t norm_max(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const real4_t *a, uint_t lda){ return norm_max_tmpl<real4_t,real4_t>(ptype,uplo,m,n,a,lda); }
real4_t norm_fro(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const real4_t *a, uint_t lda){ return norm_fro_tmpl<real4_t,real4_t>(ptype,uplo,m,n,a,lda); }
/*-------------------------------------------------*/
real_t norm_one(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const complex_t *a, uint_t lda){ return norm_one_tmpl<real_t,complex_t>(ptype,uplo,m,n,a,lda); }
real_t norm_inf(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const complex_t *a, uint_t lda){ return norm_inf_tmpl<real_t,complex_t>(ptype,uplo,m,n,a,lda); }
real_t norm_max(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const complex_t *a, uint_t lda){ return norm_max_tmpl<real_t,complex_t>(ptype,uplo,m,n,a,lda); }
real_t norm_fro(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const complex_t *a, uint_t lda){ return norm_fro_tmpl<real_t,complex_t>(ptype,uplo,m,n,a,lda); }
/*-------------------------------------------------*/
real4_t norm_one(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const complex8_t *a, uint_t lda){ return norm_one_tmpl<real4_t,complex8_t>(ptype,uplo,m,n,a,lda); }
real4_t norm_inf(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const complex8_t *a, uint_t lda){ return norm_inf_tmpl<real4_t,complex8_t>(ptype,uplo,m,n,a,lda); }
real4_t norm_max(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const complex8_t *a, uint_t lda){ return norm_max_tmpl<real4_t,complex8_t>(ptype,uplo,m,n,a,lda); }
real4_t norm_fro(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const complex8_t *a, uint_t lda){ return norm_fro_tmpl<real4_t,complex8_t>(ptype,uplo,m,n,a,lda); }
/*-------------------------------------------------*/
int_t  norm_euc(uint_t, const int_t *) { throw Exception(msg::op_not_allowed()); return 0; }
uint_t norm_euc(uint_t, const uint_t*) { throw Exception(msg::op_not_allowed()); return 0; }
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
		copy(uplo_t::F, m, 1, ptrmv(lda,a,0,j), lda, ptrmv(ldb,b,0,Q[j]), ldb);
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
static void permute_syhe_tmpl(uplo_t uplo, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, const uint_t *P, bool conjop)
{
	uint_t Pi;
	uint_t Pj;
	T      Aij;

	for(uint_t j = 0; j < n; j++) {
		RowRange ir = irange(uplo, n, j);
		for(uint_t i = ir.ibgn; i < ir.iend; i++) {

			Pi  = P[i];
			Pj  = P[j];
			Aij = entry(lda,a,i,j);

			/**/ if(uplo == uplo_t::U && Pj < Pi) entry(ldb,b,Pj,Pi) = (conjop ? conj(Aij) : Aij);
			else if(uplo == uplo_t::L && Pj > Pi) entry(ldb,b,Pj,Pi) = (conjop ? conj(Aij) : Aij);
			else                                  entry(ldb,b,Pi,Pj) = Aij;

		} // i
	} // j
}
/*-------------------------------------------------*/
template <typename T>
static void permute_tmpl(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, const uint_t *P, const uint_t *Q)
{
	if(!m || !n) return;

	Property prop(ptype, uplo);

	if(prop.isGeneral()) {

		/**/ if( P &&  Q) permute_ge_both_tmpl (m, n, a, lda, b, ldb, P, Q);
		else if( P && !Q) permute_ge_right_tmpl(m, n, a, lda, b, ldb, P);
		else if(!P &&  Q) permute_ge_left_tmpl (m, n, a, lda, b, ldb, Q);
		else              copy(uplo_t::F, m, n, a, lda, b, ldb);

	} else if(prop.isSymmetric()) {

		square_check(m,n);

		if(P) {
			permute_syhe_tmpl(uplo, n, a, lda, b, ldb, P, false);
		} else {
			copy(uplo, m, n, a, lda, b, ldb);
		} // P

	} else if(prop.isHermitian()) {

		square_check(m,n);

		if(P) {
			permute_syhe_tmpl(uplo, n, a, lda, b, ldb, P, true);
		} else {
			copy(uplo, m, n, a, lda, b, ldb);
		} // P

	} else {

		throw Exception("Invalid property: " + prop.name());

	} // prop
}
/*-------------------------------------------------*/
void permute(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const int_t *a, uint_t lda, int_t *b, uint_t ldb, const uint_t *P, const uint_t *Q)
{
	permute_tmpl(ptype, uplo, m, n, a, lda, b, ldb, P, Q); 
}
/*-------------------------------------------------*/
void permute(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const uint_t *a, uint_t lda, uint_t *b, uint_t ldb, const uint_t *P, const uint_t *Q)
{
	permute_tmpl(ptype, uplo, m, n, a, lda, b, ldb, P, Q); 
}
/*-------------------------------------------------*/
void permute(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const real_t *a, uint_t lda, real_t *b, uint_t ldb, const uint_t *P, const uint_t *Q)
{
	permute_tmpl(ptype, uplo, m, n, a, lda, b, ldb, P, Q); 
}
/*-------------------------------------------------*/
void permute(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const real4_t *a, uint_t lda, real4_t *b, uint_t ldb, const uint_t *P, const uint_t *Q)
{
	permute_tmpl(ptype, uplo, m, n, a, lda, b, ldb, P, Q); 
}
/*-------------------------------------------------*/
void permute(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, const uint_t *P, const uint_t *Q)
{
	permute_tmpl(ptype, uplo, m, n, a, lda, b, ldb, P, Q); 
}
/*-------------------------------------------------*/
void permute(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, const complex8_t *a, uint_t lda, complex8_t *b, uint_t ldb, const uint_t *P, const uint_t *Q)
{ 
	permute_tmpl(ptype, uplo, m, n, a, lda, b, ldb, P, Q); 
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/
