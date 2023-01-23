// this file inc
#include "dns.hpp"

// system
#include <cstring>
#include <algorithm>

// 3rd

// cla3p
#include "error.hpp"
#include "utils.hpp"
#include "mkl_proxy.hpp"
#include "lapack_proxy.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
void check(uint_t m, uint_t n, const void *a, uint_t lda, ptype_t ptype)
{
	if(!m || !n || !lda) 
		throw Exception("Zero dimensions");

	if(!a) 
		throw Exception("Invalid pointer"); 

	if(lda < m) 
		throw Exception("Invalid leading dimension");

	Property prop(ptype);
	if(!prop.is_valid()) 
		throw Exception("Invalid property");

	bool lower = (prop.is_symmetric() || prop.is_hermitian());
	if(lower && m != n) 
		throw Exception("Non square matrix");
}
/*-------------------------------------------------*/
template <class T>
static void zero_tmpl(uint_t m, uint_t n, T *a, uint_t lda)
{
	if(m == lda) {
		std::memset(a, 0, m * n * sizeof(T));
	} else {
		for(uint_t j = 0; j < n; j++) {
			std::memset(ptrmv(lda,a,0,j), 0, m * sizeof(T));
		} // j
	} // m = lda
}
/*-------------------------------------------------*/
void zero(uint_t m, uint_t n, real_t *a, uint_t lda)
{
	zero_tmpl(m, n, a, lda);
}
/*-------------------------------------------------*/
void zero(uint_t m, uint_t n, complex_t *a, uint_t lda)
{
	zero_tmpl(m, n, a, lda);
}
/*-------------------------------------------------*/
template <class T>
static void fill_tmpl(uint_t m, uint_t n, T *a, uint_t lda, T val)
{
	// TODO: if !val call zero() fix when operators for complex are done
	
	if(m == lda) {
		std::fill_n(a, m * n, val);
	} else {
		for(uint_t j = 0; j < n; j++) {
			std::fill_n(ptrmv(lda,a,0,j), m, val);
		} // j
	} // m = lda
}
/*-------------------------------------------------*/
void fill(uint_t m, uint_t n, real_t *a, uint_t lda, real_t val)
{
	fill_tmpl(m, n, a, lda, val);
}
/*-------------------------------------------------*/
void fill(uint_t m, uint_t n, complex_t *a, uint_t lda, complex_t val)
{
	fill_tmpl(m, n, a, lda, val);
}
/*-------------------------------------------------*/
void rand(uint_t m, uint_t n, real_t *a, uint_t lda, real_t low, real_t high)
{
	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < m; i++) {
			entry(lda,a,i,j) = drand(low, high);
		} // j
	} // j
}
/*-------------------------------------------------*/
void rand(uint_t m, uint_t n, complex_t *a, uint_t lda, real_t low, real_t high)
{
	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < m; i++) {
			entry(lda,a,i,j) = zrand(low, high);
		} // j
	} // j
}
/*-------------------------------------------------*/
template <class T>
static void copy_tmpl(uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, T scale)
{
	mkl::omatcopy('C', 'N', m, n, scale, a, lda, b, ldb);
}
/*-------------------------------------------------*/
void copy(uint_t m, uint_t n, const real_t *a, uint_t lda, real_t *b, uint_t ldb, real_t scale)
{
	copy_tmpl(m, n, a, lda, b, ldb, scale);
}
/*-------------------------------------------------*/
void copy(uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, complex_t scale)
{
	copy_tmpl(m, n, a, lda, b, ldb, scale);
}
/*-------------------------------------------------*/
template <class T>
static void transpose_tmpl(uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, T scale)
{
	mkl::omatcopy('C', 'T', m, n, scale, a, lda, b, ldb);
}
/*-------------------------------------------------*/
void transpose(uint_t m, uint_t n, const real_t *a, uint_t lda, real_t *b, uint_t ldb, real_t scale)
{
	transpose_tmpl(m, n, a, lda, b, ldb, scale);
}
/*-------------------------------------------------*/
void transpose(uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, complex_t scale)
{
	transpose_tmpl(m, n, a, lda, b, ldb, scale);
}
/*-------------------------------------------------*/
template <class T>
static void conjugate_transpose_tmpl(uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, T scale)
{
	mkl::omatcopy('C', 'C', m, n, scale, a, lda, b, ldb);
}
/*-------------------------------------------------*/
void conjugate_transpose(uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, complex_t scale)
{
	conjugate_transpose_tmpl(m, n, a, lda, b, ldb, scale);
}
/*-------------------------------------------------*/
template <class T>
static void conjugate_tmpl(uint_t m, uint_t n, const T *a, uint_t lda, T *b, uint_t ldb, T scale)
{
	mkl::omatcopy('C', 'R', m, n, scale, a, lda, b, ldb);
}
/*-------------------------------------------------*/
void conjugate(uint_t m, uint_t n, const complex_t *a, uint_t lda, complex_t *b, uint_t ldb, complex_t scale)
{
	conjugate_tmpl(m, n, a, lda, b, ldb, scale);
}
/*-------------------------------------------------*/
template <class T>
static void conjugate_tmpl(uint_t m, uint_t n, T *a, uint_t lda, T scale)
{
	mkl::imatcopy('C', 'R', m, n, scale, a, lda, lda);
}
/*-------------------------------------------------*/
void conjugate(uint_t m, uint_t n, complex_t *a, uint_t lda, complex_t scale)
{
	conjugate_tmpl(m, n, a, lda, scale);
}
/*-------------------------------------------------*/
template <class Tout, class Tin>
static Tout norm_one_tmpl(uint_t m, uint_t n, const Tin *a, uint_t lda, ptype_t ptype)
{
	check(m, n, a, lda, ptype);

	Property prop(ptype);
	/**/ if(prop.is_general()  ) return lapack::lange('1',  m , n, a, lda);
	else if(prop.is_symmetric()) return lapack::lansy('1', 'L', n, a, lda);
	else if(prop.is_hermitian()) return lapack::lanhe('1', 'L', n, a, lda);
	
	return 0.;
}
/*-------------------------------------------------*/
template <class Tout, class Tin>
static Tout norm_inf_tmpl(uint_t m, uint_t n, const Tin *a, uint_t lda, ptype_t ptype)
{
	check(m, n, a, lda, ptype);

	Property prop(ptype);
	/**/ if(prop.is_general()  ) return lapack::lange('I',  m , n, a, lda);
	else if(prop.is_symmetric()) return lapack::lansy('I', 'L', n, a, lda);
	else if(prop.is_hermitian()) return lapack::lanhe('I', 'L', n, a, lda);
	
	return 0.;
}
/*-------------------------------------------------*/
template <class Tout, class Tin>
static Tout norm_max_tmpl(uint_t m, uint_t n, const Tin *a, uint_t lda, ptype_t ptype)
{
	check(m, n, a, lda, ptype);

	Property prop(ptype);
	/**/ if(prop.is_general()  ) return lapack::lange('M',  m , n, a, lda);
	else if(prop.is_symmetric()) return lapack::lansy('M', 'L', n, a, lda);
	else if(prop.is_hermitian()) return lapack::lanhe('M', 'L', n, a, lda);
	
	return 0.;
}
/*-------------------------------------------------*/
template <class Tout, class Tin>
static Tout norm_fro_tmpl(uint_t m, uint_t n, const Tin *a, uint_t lda, ptype_t ptype)
{
	check(m, n, a, lda, ptype);

	Property prop(ptype);
	/**/ if(prop.is_general()  ) return lapack::lange('F',  m , n, a, lda);
	else if(prop.is_symmetric()) return lapack::lansy('F', 'L', n, a, lda);
	else if(prop.is_hermitian()) return lapack::lanhe('F', 'L', n, a, lda);
	
	return 0.;
}
/*-------------------------------------------------*/
real_t norm_one(uint_t m, uint_t n, const real_t *a, uint_t lda, ptype_t ptype){ return norm_one_tmpl<real_t,real_t>(m,n,a,lda,ptype); }
real_t norm_inf(uint_t m, uint_t n, const real_t *a, uint_t lda, ptype_t ptype){ return norm_inf_tmpl<real_t,real_t>(m,n,a,lda,ptype); }
real_t norm_max(uint_t m, uint_t n, const real_t *a, uint_t lda, ptype_t ptype){ return norm_max_tmpl<real_t,real_t>(m,n,a,lda,ptype); }
real_t norm_fro(uint_t m, uint_t n, const real_t *a, uint_t lda, ptype_t ptype){ return norm_fro_tmpl<real_t,real_t>(m,n,a,lda,ptype); }
/*-------------------------------------------------*/
real_t norm_one(uint_t m, uint_t n, const complex_t *a, uint_t lda, ptype_t ptype){ return norm_one_tmpl<real_t,complex_t>(m,n,a,lda,ptype); }
real_t norm_inf(uint_t m, uint_t n, const complex_t *a, uint_t lda, ptype_t ptype){ return norm_inf_tmpl<real_t,complex_t>(m,n,a,lda,ptype); }
real_t norm_max(uint_t m, uint_t n, const complex_t *a, uint_t lda, ptype_t ptype){ return norm_max_tmpl<real_t,complex_t>(m,n,a,lda,ptype); }
real_t norm_fro(uint_t m, uint_t n, const complex_t *a, uint_t lda, ptype_t ptype){ return norm_fro_tmpl<real_t,complex_t>(m,n,a,lda,ptype); }
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
