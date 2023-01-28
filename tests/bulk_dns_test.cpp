// this file inc
#include "bulk_dns_test.hpp"
#include "test_macros.hpp"

// system

// 3rd

// cla3p
#include "cla3p/src/bulk/dns.hpp"
//#include "cla3p/src/bulk/dns_io.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace tests {
/*-------------------------------------------------*/
template <class T>
static T* naive_fill_vals(uint_t m, uint_t n, uint_t lda, T ref)
{
	T *a = dns::bulk::alloc<T>(m, n, lda);

	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < lda; i++) {
			dns::bulk::entry(lda,a,i,j) = ref;
		} // j
	} // j
	return a;
}
/*-------------------------------------------------*/
template <class T>
static int_t naive_check_vals(prop_t ptype, uint_t m, uint_t n, const T *a, uint_t lda, T val, T ref)
{
	T rval;
	Property prop(ptype);
	bool lower = prop.is_lower();

	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < m; i++) {
			T aij = dns::bulk::entry(lda,a,i,j);
			if(lower) 
				if(i >= j) rval = val;
				else       rval = ref;
			else
				rval = val;
			if(aij != rval) return 1;
		} // j

		for(uint_t i = m + 1; i < lda; i++) {
			T aij = dns::bulk::entry(lda,a,i,j);
			if(aij != ref) return 1;
		} // j
	} // j

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_zero(bool strict)
{
	uint_t m = 10;
	uint_t n =  8;
	T val = T( 0.);
	T ref = T(-1.);

	{
		uint_t lda = m;
		{
			prop_t ptype = prop_t::GENERAL;
			T *a = naive_fill_vals<T>(m, n, lda, ref);
			dns::bulk::zero(ptype, m, n, a, lda);
			if(naive_check_vals<T>(ptype, m, n, a, lda, val, ref)) fatal_error();
			i_free(a);
		}
		{
			prop_t ptype = prop_t::SYMMETRIC;
			T *a = naive_fill_vals<T>(m, m, lda, ref);
			dns::bulk::zero(ptype, m, m, a, lda);
			if(naive_check_vals<T>(ptype, m, n, a, lda, val, ref)) fatal_error();
			i_free(a);
		}
		{
			prop_t ptype = prop_t::HERMITIAN;
			T *a = naive_fill_vals<T>(m, m, lda, ref);
			dns::bulk::zero(ptype, m, m, a, lda);
			if(naive_check_vals<T>(ptype, m, n, a, lda, val, ref)) fatal_error();
			i_free(a);
		}
	}

	{
		uint_t lda = m + 15;
		{
			prop_t ptype = prop_t::GENERAL;
			T *a = naive_fill_vals<T>(m, n, lda, ref);
			dns::bulk::zero(ptype, m, n, a, lda);
			if(naive_check_vals<T>(ptype, m, n, a, lda, val, ref)) fatal_error();
			i_free(a);
		}
		{
			prop_t ptype = prop_t::SYMMETRIC;
			T *a = naive_fill_vals<T>(m, m, lda, ref);
			dns::bulk::zero(ptype, m, m, a, lda);
			if(naive_check_vals<T>(ptype, m, n, a, lda, val, ref)) fatal_error();
			i_free(a);
		}
		{
			prop_t ptype = prop_t::HERMITIAN;
			T *a = naive_fill_vals<T>(m, m, lda, ref);
			dns::bulk::zero(ptype, m, m, a, lda);
			if(naive_check_vals<T>(ptype, m, n, a, lda, val, ref)) fatal_error();
			i_free(a);
		}
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_fill(bool strict)
{
	uint_t m = 10;
	uint_t n =  8;
	T val = T( 5.);
	T ref = T(-1.);

	{
		uint_t lda = m;
		{
			prop_t ptype = prop_t::GENERAL;
			T *a = naive_fill_vals<T>(m, n, lda, ref);
			dns::bulk::fill(ptype, m, n, a, lda, val);
			if(naive_check_vals<T>(ptype, m, n, a, lda, val, ref)) fatal_error();
			i_free(a);
		}
		{
			prop_t ptype = prop_t::SYMMETRIC;
			T *a = naive_fill_vals<T>(m, m, lda, ref);
			dns::bulk::fill(ptype, m, m, a, lda, val);
			if(naive_check_vals<T>(ptype, m, m, a, lda, val, ref)) fatal_error();
			i_free(a);
		}
		{
			prop_t ptype = prop_t::HERMITIAN;
			T *a = naive_fill_vals<T>(m, m, lda, ref);
			dns::bulk::fill(ptype, m, m, a, lda, val);
			if(naive_check_vals<T>(ptype, m, m, a, lda, val, ref)) fatal_error();
			i_free(a);
		}
	}

	{
		uint_t lda = m + 15;
		{
			prop_t ptype = prop_t::GENERAL;
			T *a = naive_fill_vals<T>(m, n, lda, ref);
			dns::bulk::fill(ptype, m, n, a, lda, val);
			if(naive_check_vals<T>(ptype, m, n, a, lda, val, ref)) fatal_error();
			i_free(a);
		}
		{
			prop_t ptype = prop_t::SYMMETRIC;
			T *a = naive_fill_vals<T>(m, m, lda, ref);
			dns::bulk::fill(ptype, m, m, a, lda, val);
			if(naive_check_vals<T>(ptype, m, m, a, lda, val, ref)) fatal_error();
			i_free(a);
		}
		{
			prop_t ptype = prop_t::HERMITIAN;
			T *a = naive_fill_vals<T>(m, m, lda, ref);
			dns::bulk::fill(ptype, m, m, a, lda, val);
			if(naive_check_vals<T>(ptype, m, m, a, lda, val, ref)) fatal_error();
			i_free(a);
		}
	}

	test_success();
}
/*-------------------------------------------------*/
int_t bulk_dns(bool strict)
{
	int_t numtests = 0;
	int_t numfail = 0;

	numfail += test_zero<cla3p::real_t>(strict); numtests++;
	numfail += test_zero<cla3p::real4_t>(strict); numtests++;
	numfail += test_zero<cla3p::complex_t>(strict); numtests++;
	numfail += test_zero<cla3p::complex8_t>(strict); numtests++;

	numfail += test_fill<cla3p::real_t>(strict); numtests++;
	numfail += test_fill<cla3p::real4_t>(strict); numtests++;
	numfail += test_fill<cla3p::complex_t>(strict); numtests++;
	numfail += test_fill<cla3p::complex8_t>(strict); numtests++;

	print_summary();
}
/*-------------------------------------------------*/
} // namespace tests
} // namespace cla3p
/*-------------------------------------------------*/
