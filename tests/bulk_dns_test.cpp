// this file inc
#include "bulk_dns_test.hpp"
#include "test_macros.hpp"

// system

// 3rd

// cla3p
#include "cla3p/src/utils.hpp"
#include "cla3p/src/bulk/dns.hpp"
#include "cla3p/src/bulk/dns_io.hpp"

#include "naive_matrix_ops.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace tests {
/*-------------------------------------------------*/
template <class T>
static real_t cmptol()
{
	if (std::is_same<T, real_t>::value) return 1.e-12;
	if (std::is_same<T, real4_t>::value) return 1.e-6;
	if (std::is_same<T, complex_t>::value) return 1.e-12;
	if (std::is_same<T, complex8_t>::value) return 1.e-6;
}
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
static bool element_is_in_active_range(prop_t ptype, uint_t m, uint_t n, uint_t i, uint_t j)
{
	Property prop(ptype);
	bool lower = prop.is_lower();

	return (lower ? (i < m && i >= j) : (i < m && j < n));
}
/*-------------------------------------------------*/
template <class T>
static int_t naive_check_vals(prop_t ptype, uint_t m, uint_t n, const T *a, uint_t lda, T val)
{
	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < lda; i++) {
			T aij = dns::bulk::entry(lda,a,i,j);
			if(element_is_in_active_range(ptype,m,n,i,j) && aij != val) return 1;
		} // i
	} // j

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t naive_check_complementary_vals(prop_t ptype, uint_t m, uint_t n, const T *a, uint_t lda, T ref)
{
	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < lda; i++) {
			T aij = dns::bulk::entry(lda,a,i,j);
			if(!element_is_in_active_range(ptype,m,n,i,j) && aij != ref) return 1;
		} // i
	} // j

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t naive_compare_vals(prop_t ptype, uint_t m, uint_t n, bool trA, bool conjA, const T *a, uint_t lda, const T *b, uint_t ldb, T coeff)
{
	//
	// B = coeff * opA(A)
	// Bij = coeff *      Aij  if !trA && !conjA
	// Bij = coeff * conj(Aij) if !trA &&  conjA
	// Bij = coeff *      Aji  if  trA && !conjA
	// Bij = coeff * conj(Aji) if  trA &&  conjA
	//
	uint_t Bcols = (trA ? m : n);
	uint_t Brows = (trA ? n : m);

	for(uint_t j = 0; j < Bcols; j++) {
		for(uint_t i = 0; i < Brows; i++) {
			T bij = dns::bulk::entry(ldb,b,i,j);
			T aij = T(0.);
			if(!trA && !conjA) aij =      dns::bulk::entry(lda,a,i,j) ;
			if(!trA &&  conjA) aij = conj(dns::bulk::entry(lda,a,i,j));
			if( trA && !conjA) aij =      dns::bulk::entry(lda,a,j,i) ;
			if( trA &&  conjA) aij = conj(dns::bulk::entry(lda,a,j,i));
			real_t diff = std::abs(coeff * aij - bij);
			if(element_is_in_active_range(ptype,Brows,Bcols,i,j) && diff > cmptol<T>()) return 1;
		} // i
	} // j

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t naive_compare_upper_lower_part(bool conjop, uint_t n, const T *a, uint_t lda)
{
	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = j; i < n; i++) {
			T aij = dns::bulk::entry(lda,a,i,j);
			T aji = dns::bulk::entry(lda,a,j,i);
			if(conjop && i > j) aij = conj(aij);
			real_t diff = std::abs(aij - aji);
			if(element_is_in_active_range(prop_t::GENERAL,n,n,i,j) && diff > cmptol<T>()) return 1;
		} // i
	} // j

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_zero_in(prop_t ptype, uint_t m, uint_t n, uint_t lda)
{
	T val = T( 0.);
	T ref = T(-1.);

	Property prop(ptype);
	bool lower = prop.is_lower();
	bool samelda = (lda == m);

	if(lower) {
		m = std::min(m,n);
		n = std::min(m,n);
		if(samelda) lda = m;
	} // lower

	T *a = naive_fill_vals<T>(m, n, lda, ref);
	dns::bulk::zero(ptype, m, n, a, lda);
	if(naive_check_vals              <T>(ptype, m, n, a, lda, val)) return 1;
	if(naive_check_complementary_vals<T>(ptype, m, n, a, lda, ref)) return 1;
	i_free(a);

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_zero(bool strict)
{
	uint_t m = 10;
	uint_t n =  8;

	{
		uint_t lda = m;
		if(test_zero_in<T>(prop_t::GENERAL  , m, n, lda)) fatal_error();
		if(test_zero_in<T>(prop_t::SYMMETRIC, m, n, lda)) fatal_error();
		if(test_zero_in<T>(prop_t::HERMITIAN, m, n, lda)) fatal_error();
	}

	{
		uint_t lda = m + 15;
		if(test_zero_in<T>(prop_t::GENERAL  , m, n, lda)) fatal_error();
		if(test_zero_in<T>(prop_t::SYMMETRIC, m, n, lda)) fatal_error();
		if(test_zero_in<T>(prop_t::HERMITIAN, m, n, lda)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_fill_in(prop_t ptype, uint_t m, uint_t n, uint_t lda)
{
	T val = T( 5.);
	T ref = T(-1.);

	Property prop(ptype);
	bool lower = prop.is_lower();
	bool samelda = (lda == m);

	if(lower) {
		m = std::min(m,n);
		n = std::min(m,n);
		if(samelda) lda = m;
	} // lower

	T *a = naive_fill_vals<T>(m, n, lda, ref);
	dns::bulk::fill(ptype, m, n, a, lda, val);
	if(naive_check_vals              <T>(ptype, m, n, a, lda, val)) return 1;
	if(naive_check_complementary_vals<T>(ptype, m, n, a, lda, ref)) return 1;
	i_free(a);

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_fill(bool strict)
{
	uint_t m = 10;
	uint_t n =  8;

	{
		uint_t lda = m;
		if(test_fill_in<T>(prop_t::GENERAL  , m, n, lda)) fatal_error();
		if(test_fill_in<T>(prop_t::SYMMETRIC, m, n, lda)) fatal_error();
		if(test_fill_in<T>(prop_t::HERMITIAN, m, n, lda)) fatal_error();
	}

	{
		uint_t lda = m + 15;
		if(test_fill_in<T>(prop_t::GENERAL  , m, n, lda)) fatal_error();
		if(test_fill_in<T>(prop_t::SYMMETRIC, m, n, lda)) fatal_error();
		if(test_fill_in<T>(prop_t::HERMITIAN, m, n, lda)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_rand_in(prop_t ptype, uint_t m, uint_t n, uint_t lda)
{
	T ref = T(-100.);
	real4_t low = -1.;
	real4_t high = 1.;

	Property prop(ptype);
	bool lower = prop.is_lower();
	bool samelda = (lda == m);

	if(lower) {
		m = std::min(m,n);
		n = std::min(m,n);
		if(samelda) lda = m;
	} // lower

	T *a = naive_fill_vals<T>(m, n, lda, ref);
	dns::bulk::rand(ptype, m, n, a, lda, low, high);
	if(naive_check_complementary_vals<T>(ptype, m, n, a, lda, ref)) return 1;
	i_free(a);

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_rand(bool strict)
{
	uint_t m = 10;
	uint_t n =  8;

	{
		uint_t lda = m;
		if(test_rand_in<T>(prop_t::GENERAL  , m, n, lda)) fatal_error();
		if(test_rand_in<T>(prop_t::SYMMETRIC, m, n, lda)) fatal_error();
		if(test_rand_in<T>(prop_t::HERMITIAN, m, n, lda)) fatal_error();
	}

	{
		uint_t lda = m + 5;
		if(test_rand_in<T>(prop_t::GENERAL  , m, n, lda)) fatal_error();
		if(test_rand_in<T>(prop_t::SYMMETRIC, m, n, lda)) fatal_error();
		if(test_rand_in<T>(prop_t::HERMITIAN, m, n, lda)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_copy_in(prop_t ptype, uint_t m, uint_t n, uint_t lda, uint_t ldb, real_t coeff)
{
	T ref = T(-100.);
	real4_t low = -1.;
	real4_t high = 1.;

	Property prop(ptype);
	bool lower = prop.is_lower();
	bool samelda = (lda == m);
	bool sameldb = (ldb == m);

	if(lower) {
		m = std::min(m,n);
		n = std::min(m,n);
		if(samelda) lda = m;
		if(sameldb) ldb = m;
	} // lower

	T *a = naive_fill_vals<T>(m, n, lda, ref);
	T *b = naive_fill_vals<T>(m, n, ldb, ref);
	dns::bulk::rand(ptype, m, n, a, lda, low, high);
	dns::bulk::copy(ptype, m, n, a, lda, b, ldb, coeff);
	if(naive_compare_vals<T>(ptype, m, n, false, false, a, lda, b, ldb, coeff)) return 1;
	if(naive_check_complementary_vals<T>(ptype, m, n, a, lda, ref)) return 1;
	if(naive_check_complementary_vals<T>(ptype, m, n, b, ldb, ref)) return 1;
	i_free(a);
	i_free(b);

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_copy(bool strict)
{
	uint_t m = 10;
	uint_t n =  8;

	{
		uint_t lda = m;
		uint_t ldb = m;
		if(test_copy_in<T>(prop_t::GENERAL  , m, n, lda, ldb,  1.)) fatal_error();
		if(test_copy_in<T>(prop_t::SYMMETRIC, m, n, lda, ldb,  1.)) fatal_error();
		if(test_copy_in<T>(prop_t::HERMITIAN, m, n, lda, ldb,  1.)) fatal_error();
		if(test_copy_in<T>(prop_t::GENERAL  , m, n, lda, ldb, -2.)) fatal_error();
		if(test_copy_in<T>(prop_t::SYMMETRIC, m, n, lda, ldb, -2.)) fatal_error();
		if(test_copy_in<T>(prop_t::HERMITIAN, m, n, lda, ldb, -2.)) fatal_error();
	}

	{
		uint_t lda = m +  5;
		uint_t ldb = m + 15;
		if(test_copy_in<T>(prop_t::GENERAL  , m, n, lda, ldb,  1.)) fatal_error();
		if(test_copy_in<T>(prop_t::SYMMETRIC, m, n, lda, ldb,  1.)) fatal_error();
		if(test_copy_in<T>(prop_t::HERMITIAN, m, n, lda, ldb,  1.)) fatal_error();
		if(test_copy_in<T>(prop_t::GENERAL  , m, n, lda, ldb, -2.)) fatal_error();
		if(test_copy_in<T>(prop_t::SYMMETRIC, m, n, lda, ldb, -2.)) fatal_error();
		if(test_copy_in<T>(prop_t::HERMITIAN, m, n, lda, ldb, -2.)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_scale_in(prop_t ptype, uint_t m, uint_t n, uint_t lda, uint_t ldb, real_t coeff)
{
	T ref = T(-100.);
	real4_t low = -1.;
	real4_t high = 1.;

	Property prop(ptype);
	bool lower = prop.is_lower();
	bool samelda = (lda == m);
	bool sameldb = (ldb == m);

	if(lower) {
		m = std::min(m,n);
		n = std::min(m,n);
		if(samelda) lda = m;
		if(sameldb) ldb = m;
	} // lower

	T *a = naive_fill_vals<T>(m, n, lda, ref);
	T *b = naive_fill_vals<T>(m, n, ldb, ref);
	dns::bulk::rand(ptype, m, n, a, lda, low, high);
	dns::bulk::copy(ptype, m, n, a, lda, b, ldb);
	dns::bulk::scale(ptype, m, n, b, ldb, coeff);
	if(naive_compare_vals<T>(ptype, m, n, false, false, a, lda, b, ldb, coeff)) return 1;
	if(naive_check_complementary_vals<T>(ptype, m, n, a, lda, ref)) return 1;
	if(naive_check_complementary_vals<T>(ptype, m, n, b, ldb, ref)) return 1;
	i_free(a);
	i_free(b);

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_scale(bool strict)
{
	uint_t m = 10;
	uint_t n =  8;

	{
		uint_t lda = m;
		uint_t ldb = m;
		if(test_scale_in<T>(prop_t::GENERAL  , m, n, lda, ldb, -5.)) fatal_error();
		if(test_scale_in<T>(prop_t::SYMMETRIC, m, n, lda, ldb, -5.)) fatal_error();
		if(test_scale_in<T>(prop_t::HERMITIAN, m, n, lda, ldb, -5.)) fatal_error();
	}

	{
		uint_t lda = m +  5;
		uint_t ldb = m + 15;
		if(test_scale_in<T>(prop_t::GENERAL  , m, n, lda, ldb, 3.)) fatal_error();
		if(test_scale_in<T>(prop_t::SYMMETRIC, m, n, lda, ldb, 3.)) fatal_error();
		if(test_scale_in<T>(prop_t::HERMITIAN, m, n, lda, ldb, 3.)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_ctranspose_in(uint_t m, uint_t n, uint_t lda, uint_t ldb, real_t coeff, bool conjop)
{
	T ref = T(-100.);
	real4_t low = -1.;
	real4_t high = 1.;
	prop_t ptype = prop_t::GENERAL;

	T *a = naive_fill_vals<T>(m, n, lda, ref);
	T *b = naive_fill_vals<T>(n, m, ldb, ref);
	dns::bulk::rand(ptype, m, n, a, lda, low, high);
	if(conjop) dns::bulk::conjugate_transpose(m, n, a, lda, b, ldb, coeff);
	else       dns::bulk::transpose(m, n, a, lda, b, ldb, coeff);
	if(naive_compare_vals<T>(ptype, m, n, true, conjop, a, lda, b, ldb, coeff)) return 1;
	if(naive_check_complementary_vals<T>(ptype, m, n, a, lda, ref)) return 1;
	if(naive_check_complementary_vals<T>(ptype, n, m, b, ldb, ref)) return 1;
	i_free(a);
	i_free(b);

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_transpose(bool strict)
{
	uint_t m = 10;
	uint_t n =  8;

	{
		uint_t lda = m;
		uint_t ldb = n;
		if(test_ctranspose_in<T>(m, n, lda, ldb,  1., false)) fatal_error();
		if(test_ctranspose_in<T>(m, n, lda, ldb, -5., false)) fatal_error();
	}

	{
		uint_t lda = m +  5;
		uint_t ldb = n + 15;
		if(test_ctranspose_in<T>(m, n, lda, ldb, 1., false)) fatal_error();
		if(test_ctranspose_in<T>(m, n, lda, ldb, 3., false)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_conjugate_transpose(bool strict)
{
	uint_t m = 10;
	uint_t n =  8;

	{
		uint_t lda = m;
		uint_t ldb = n;
		if(test_ctranspose_in<T>(m, n, lda, ldb,  1., true)) fatal_error();
		if(test_ctranspose_in<T>(m, n, lda, ldb, -5., true)) fatal_error();
	}

	{
		uint_t lda = m +  5;
		uint_t ldb = n + 15;
		if(test_ctranspose_in<T>(m, n, lda, ldb, 1., true)) fatal_error();
		if(test_ctranspose_in<T>(m, n, lda, ldb, 3., true)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_conjugate_in(prop_t ptype, uint_t m, uint_t n, uint_t lda, uint_t ldb, real_t coeff)
{
	T ref = T(-100.);
	real4_t low = -1.;
	real4_t high = 1.;

	Property prop(ptype);
	bool lower = prop.is_lower();
	bool samelda = (lda == m);
	bool sameldb = (ldb == m);

	if(lower) {
		m = std::min(m,n);
		n = std::min(m,n);
		if(samelda) lda = m;
		if(sameldb) ldb = m;
	} // lower

	T *a = naive_fill_vals<T>(m, n, lda, ref);
	T *b = naive_fill_vals<T>(m, n, ldb, ref);
	dns::bulk::rand(ptype, m, n, a, lda, low, high);
	dns::bulk::copy(ptype, m, n, a, lda, b, ldb);
	dns::bulk::conjugate(ptype, m, n, b, ldb, coeff);
	if(naive_compare_vals<T>(ptype, m, n, false, true, a, lda, b, ldb, coeff)) return 1;
	if(naive_check_complementary_vals<T>(ptype, m, n, a, lda, ref)) return 1;
	if(naive_check_complementary_vals<T>(ptype, m, n, b, ldb, ref)) return 1;
	i_free(a);
	i_free(b);

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_conjugate(bool strict)
{
	uint_t m = 10;
	uint_t n =  8;

	{
		uint_t lda = m;
		uint_t ldb = m;
		if(test_conjugate_in<T>(prop_t::GENERAL  , m, n, lda, ldb,  1.)) fatal_error();
		if(test_conjugate_in<T>(prop_t::SYMMETRIC, m, n, lda, ldb,  1.)) fatal_error();
		if(test_conjugate_in<T>(prop_t::HERMITIAN, m, n, lda, ldb,  1.)) fatal_error();
		if(test_conjugate_in<T>(prop_t::GENERAL  , m, n, lda, ldb, -5.)) fatal_error();
		if(test_conjugate_in<T>(prop_t::SYMMETRIC, m, n, lda, ldb, -5.)) fatal_error();
		if(test_conjugate_in<T>(prop_t::HERMITIAN, m, n, lda, ldb, -5.)) fatal_error();
	}

	{
		uint_t lda = m +  5;
		uint_t ldb = m + 15;
		if(test_conjugate_in<T>(prop_t::GENERAL  , m, n, lda, ldb, 1.)) fatal_error();
		if(test_conjugate_in<T>(prop_t::SYMMETRIC, m, n, lda, ldb, 1.)) fatal_error();
		if(test_conjugate_in<T>(prop_t::HERMITIAN, m, n, lda, ldb, 1.)) fatal_error();
		if(test_conjugate_in<T>(prop_t::GENERAL  , m, n, lda, ldb, 3.)) fatal_error();
		if(test_conjugate_in<T>(prop_t::SYMMETRIC, m, n, lda, ldb, 3.)) fatal_error();
		if(test_conjugate_in<T>(prop_t::HERMITIAN, m, n, lda, ldb, 3.)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_syhe2ge_in(bool conjop, uint_t n, uint_t lda)
{
	T ref = T(-100.);
	real4_t low = -1.;
	real4_t high = 1.;

	T *a = naive_fill_vals<T>(n, n, lda, ref);
	if(conjop) {
		dns::bulk::rand(prop_t::HERMITIAN, n, n, a, lda, low, high);
		dns::bulk::he2ge(n, a, lda);
	} else {
		dns::bulk::rand(prop_t::SYMMETRIC, n, n, a, lda, low, high);
		dns::bulk::sy2ge(n, a, lda);
	} // conjop
	if(naive_compare_upper_lower_part(conjop, n, a, lda)) return 1;
	if(naive_check_complementary_vals<T>(prop_t::GENERAL, n, n, a, lda, ref)) return 1;
	i_free(a);

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_syhe2ge(bool strict)
{
	uint_t m = 10;
	uint_t n =  8;

	{
		uint_t lda = m;
		if(test_syhe2ge_in<T>(false, n, lda)) fatal_error();
		if(test_syhe2ge_in<T>(true , n, lda)) fatal_error();
	}

	{
		uint_t lda = m + 5;
		if(test_syhe2ge_in<T>(false, n, lda)) fatal_error();
		if(test_syhe2ge_in<T>(true , n, lda)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
enum class WhichNorm{
	TEST_NRM_ONE = 0,
	TEST_NRM_INF    ,
	TEST_NRM_MAX    ,
	TEST_NRM_FRO    
};
/*-------------------------------------------------*/
template <class T>
static int_t test_nrm_in(prop_t ptype, uint_t m, uint_t n, uint_t lda, WhichNorm which)
{
	T ref = T(-100.);
	real4_t low = -1.;
	real4_t high = 1.;

	Property prop(ptype);
	bool lower = prop.is_lower();
	bool samelda = (lda == m);

	if(lower) {
		m = std::min(m,n);
		n = std::min(m,n);
		if(samelda) lda = m;
	} // lower

	T *a = naive_fill_vals<T>(m, n, lda, ref);
	dns::bulk::rand(ptype, m, n, a, lda, low, high);

	real_t ret = 0.;
	real_t ret2 = 0.;

	if(which == WhichNorm::TEST_NRM_ONE) ret = dns::bulk::norm_one(ptype, m, n, a, lda);
	if(which == WhichNorm::TEST_NRM_INF) ret = dns::bulk::norm_inf(ptype, m, n, a, lda);
	if(which == WhichNorm::TEST_NRM_MAX) ret = dns::bulk::norm_max(ptype, m, n, a, lda);
	if(which == WhichNorm::TEST_NRM_FRO) ret = dns::bulk::norm_fro(ptype, m, n, a, lda);

	if(which == WhichNorm::TEST_NRM_ONE) ret2 = naive_norm_one(ptype, m, n, a, lda);
	if(which == WhichNorm::TEST_NRM_INF) ret2 = naive_norm_inf(ptype, m, n, a, lda);
	if(which == WhichNorm::TEST_NRM_MAX) ret2 = naive_norm_max(ptype, m, n, a, lda);
	if(which == WhichNorm::TEST_NRM_FRO) ret2 = naive_norm_fro(ptype, m, n, a, lda);

	real_t diff = std::abs(ret - ret2);
	if(diff > cmptol<T>()) return 1;
	i_free(a);

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_nrmone(bool strict)
{
	uint_t m = 10;
	uint_t n =  8;

	{
		uint_t lda = m;
		if(test_nrm_in<T>(prop_t::GENERAL  , m, n, lda, WhichNorm::TEST_NRM_ONE)) fatal_error();
		if(test_nrm_in<T>(prop_t::SYMMETRIC, m, n, lda, WhichNorm::TEST_NRM_ONE)) fatal_error();
		if(test_nrm_in<T>(prop_t::HERMITIAN, m, n, lda, WhichNorm::TEST_NRM_ONE)) fatal_error();
	}

	{
		uint_t lda = m +  5;
		if(test_nrm_in<T>(prop_t::GENERAL  , m, n, lda, WhichNorm::TEST_NRM_ONE)) fatal_error();
		if(test_nrm_in<T>(prop_t::SYMMETRIC, m, n, lda, WhichNorm::TEST_NRM_ONE)) fatal_error();
		if(test_nrm_in<T>(prop_t::HERMITIAN, m, n, lda, WhichNorm::TEST_NRM_ONE)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_nrminf(bool strict)
{
	uint_t m = 10;
	uint_t n =  8;

	{
		uint_t lda = m;
		if(test_nrm_in<T>(prop_t::GENERAL  , m, n, lda, WhichNorm::TEST_NRM_INF)) fatal_error();
		if(test_nrm_in<T>(prop_t::SYMMETRIC, m, n, lda, WhichNorm::TEST_NRM_INF)) fatal_error();
		if(test_nrm_in<T>(prop_t::HERMITIAN, m, n, lda, WhichNorm::TEST_NRM_INF)) fatal_error();
	}

	{
		uint_t lda = m +  5;
		if(test_nrm_in<T>(prop_t::GENERAL  , m, n, lda, WhichNorm::TEST_NRM_INF)) fatal_error();
		if(test_nrm_in<T>(prop_t::SYMMETRIC, m, n, lda, WhichNorm::TEST_NRM_INF)) fatal_error();
		if(test_nrm_in<T>(prop_t::HERMITIAN, m, n, lda, WhichNorm::TEST_NRM_INF)) fatal_error();
	}

	test_success();
	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_nrmmax(bool strict)
{
	uint_t m = 10;
	uint_t n =  8;

	{
		uint_t lda = m;
		if(test_nrm_in<T>(prop_t::GENERAL  , m, n, lda, WhichNorm::TEST_NRM_MAX)) fatal_error();
		if(test_nrm_in<T>(prop_t::SYMMETRIC, m, n, lda, WhichNorm::TEST_NRM_MAX)) fatal_error();
		if(test_nrm_in<T>(prop_t::HERMITIAN, m, n, lda, WhichNorm::TEST_NRM_MAX)) fatal_error();
	}                                                            
                                                               
	{                                                            
		uint_t lda = m +  5;                                       
		if(test_nrm_in<T>(prop_t::GENERAL  , m, n, lda, WhichNorm::TEST_NRM_MAX)) fatal_error();
		if(test_nrm_in<T>(prop_t::SYMMETRIC, m, n, lda, WhichNorm::TEST_NRM_MAX)) fatal_error();
		if(test_nrm_in<T>(prop_t::HERMITIAN, m, n, lda, WhichNorm::TEST_NRM_MAX)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_nrmfro(bool strict)
{
	uint_t m = 10;
	uint_t n =  8;

	{
		uint_t lda = m;
		if(test_nrm_in<T>(prop_t::GENERAL  , m, n, lda, WhichNorm::TEST_NRM_FRO)) fatal_error();
		if(test_nrm_in<T>(prop_t::SYMMETRIC, m, n, lda, WhichNorm::TEST_NRM_FRO)) fatal_error();
		if(test_nrm_in<T>(prop_t::HERMITIAN, m, n, lda, WhichNorm::TEST_NRM_FRO)) fatal_error();
	}                                                            
                                                               
	{                                                            
		uint_t lda = m +  5;                                       
		if(test_nrm_in<T>(prop_t::GENERAL  , m, n, lda, WhichNorm::TEST_NRM_FRO)) fatal_error();
		if(test_nrm_in<T>(prop_t::SYMMETRIC, m, n, lda, WhichNorm::TEST_NRM_FRO)) fatal_error();
		if(test_nrm_in<T>(prop_t::HERMITIAN, m, n, lda, WhichNorm::TEST_NRM_FRO)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_perms_in(prop_t ptype, uint_t m, uint_t n, uint_t lda, uint_t ldb, uint_t ldc, bool nullP, bool nullQ)
{
	T ref = T(-100.);
	real4_t low = -1.;
	real4_t high = 1.;

	Property prop(ptype);
	bool lower = prop.is_lower();
	bool samelda = (lda == m);
	bool sameldb = (ldb == m);
	bool sameldc = (ldc == m);

	if(lower) {
		m = std::min(m,n);
		n = std::min(m,n);
		if(samelda) lda = m;
		if(sameldb) ldb = m;
		if(sameldc) ldc = m;
	} // lower

	{
		std::vector<uint_t> vecP = create_random_perm(m);
		std::vector<uint_t> vecQ = create_random_perm(n);
		const uint_t *P = (nullP ? nullptr : vecP.data());
		const uint_t *Q = (nullQ ? nullptr : vecQ.data());
		T *a = naive_fill_vals<T>(m, n, lda, ref);
		T *b = naive_fill_vals<T>(m, n, ldb, ref);
		T *c = naive_fill_vals<T>(m, n, ldc, ref);
		dns::bulk::rand(ptype, m, n, a, lda, low, high);
		dns::bulk::permute(ptype, m, n, a, lda, b, ldb, P, Q);
		naive_permute(ptype, m, n, a, lda, c, ldc, P, Q);
		if(naive_compare_vals<T>(ptype, m, n, false, false, b, ldb, c, ldc, 1.)) return 1;
		if(naive_check_complementary_vals<T>(ptype, m, n, b, ldb, ref)) return 1;
		i_free(a);
		i_free(b);
		i_free(c);
	}

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_perms(bool strict)
{
	uint_t m = 10;
	uint_t n =  8;

	{
		uint_t lda = m;
		uint_t ldb = m;
		if(test_perms_in<T>(prop_t::GENERAL  , m, n, lda, ldb, ldb, false, false)) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, m, n, lda, ldb, ldb, false, false)) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, m, n, lda, ldb, ldb, false, false)) fatal_error();
		if(test_perms_in<T>(prop_t::GENERAL  , m, n, lda, ldb, ldb, true , false)) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, m, n, lda, ldb, ldb, true , false)) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, m, n, lda, ldb, ldb, true , false)) fatal_error();
		if(test_perms_in<T>(prop_t::GENERAL  , m, n, lda, ldb, ldb, false, true )) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, m, n, lda, ldb, ldb, false, true )) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, m, n, lda, ldb, ldb, false, true )) fatal_error();
		if(test_perms_in<T>(prop_t::GENERAL  , m, n, lda, ldb, ldb, true , true )) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, m, n, lda, ldb, ldb, true , true )) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, m, n, lda, ldb, ldb, true , true )) fatal_error();
	}

	{
		uint_t lda = m +  5;
		uint_t ldb = m + 15;
		if(test_perms_in<T>(prop_t::GENERAL  , m, n, lda, ldb, ldb, false, false)) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, m, n, lda, ldb, ldb, false, false)) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, m, n, lda, ldb, ldb, false, false)) fatal_error();
		if(test_perms_in<T>(prop_t::GENERAL  , m, n, lda, ldb, ldb, true , false)) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, m, n, lda, ldb, ldb, true , false)) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, m, n, lda, ldb, ldb, true , false)) fatal_error();
		if(test_perms_in<T>(prop_t::GENERAL  , m, n, lda, ldb, ldb, false, true )) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, m, n, lda, ldb, ldb, false, true )) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, m, n, lda, ldb, ldb, false, true )) fatal_error();
		if(test_perms_in<T>(prop_t::GENERAL  , m, n, lda, ldb, ldb, true , true )) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, m, n, lda, ldb, ldb, true , true )) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, m, n, lda, ldb, ldb, true , true )) fatal_error();
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

	numfail += test_rand<cla3p::real_t>(strict); numtests++;
	numfail += test_rand<cla3p::real4_t>(strict); numtests++;
	numfail += test_rand<cla3p::complex_t>(strict); numtests++;
	numfail += test_rand<cla3p::complex8_t>(strict); numtests++;

	numfail += test_copy<cla3p::real_t>(strict); numtests++;
	numfail += test_copy<cla3p::real4_t>(strict); numtests++;
	numfail += test_copy<cla3p::complex_t>(strict); numtests++;
	numfail += test_copy<cla3p::complex8_t>(strict); numtests++;

	numfail += test_scale<cla3p::real_t>(strict); numtests++;
	numfail += test_scale<cla3p::real4_t>(strict); numtests++;
	numfail += test_scale<cla3p::complex_t>(strict); numtests++;
	numfail += test_scale<cla3p::complex8_t>(strict); numtests++;

	numfail += test_transpose<cla3p::real_t>(strict); numtests++;
	numfail += test_transpose<cla3p::real4_t>(strict); numtests++;
	numfail += test_transpose<cla3p::complex_t>(strict); numtests++;
	numfail += test_transpose<cla3p::complex8_t>(strict); numtests++;

	numfail += test_conjugate_transpose<cla3p::real_t>(strict); numtests++;
	numfail += test_conjugate_transpose<cla3p::real4_t>(strict); numtests++;
	numfail += test_conjugate_transpose<cla3p::complex_t>(strict); numtests++;
	numfail += test_conjugate_transpose<cla3p::complex8_t>(strict); numtests++;

	numfail += test_conjugate<cla3p::real_t>(strict); numtests++;
	numfail += test_conjugate<cla3p::real4_t>(strict); numtests++;
	numfail += test_conjugate<cla3p::complex_t>(strict); numtests++;
	numfail += test_conjugate<cla3p::complex8_t>(strict); numtests++;

	numfail += test_syhe2ge<cla3p::real_t>(strict); numtests++;
	numfail += test_syhe2ge<cla3p::real4_t>(strict); numtests++;
	numfail += test_syhe2ge<cla3p::complex_t>(strict); numtests++;
	numfail += test_syhe2ge<cla3p::complex8_t>(strict); numtests++;

	numfail += test_nrmone<cla3p::real_t>(strict); numtests++;
	numfail += test_nrmone<cla3p::real4_t>(strict); numtests++;
	numfail += test_nrmone<cla3p::complex_t>(strict); numtests++;
	numfail += test_nrmone<cla3p::complex8_t>(strict); numtests++;

	numfail += test_nrminf<cla3p::real_t>(strict); numtests++;
	numfail += test_nrminf<cla3p::real4_t>(strict); numtests++;
	numfail += test_nrminf<cla3p::complex_t>(strict); numtests++;
	numfail += test_nrminf<cla3p::complex8_t>(strict); numtests++;

	numfail += test_nrmmax<cla3p::real_t>(strict); numtests++;
	numfail += test_nrmmax<cla3p::real4_t>(strict); numtests++;
	numfail += test_nrmmax<cla3p::complex_t>(strict); numtests++;
	numfail += test_nrmmax<cla3p::complex8_t>(strict); numtests++;

	numfail += test_nrmfro<cla3p::real_t>(strict); numtests++;
	numfail += test_nrmfro<cla3p::real4_t>(strict); numtests++;
	numfail += test_nrmfro<cla3p::complex_t>(strict); numtests++;
	numfail += test_nrmfro<cla3p::complex8_t>(strict); numtests++;

	numfail += test_perms<cla3p::real_t>(strict); numtests++;
	numfail += test_perms<cla3p::real4_t>(strict); numtests++;
	numfail += test_perms<cla3p::complex_t>(strict); numtests++;
	numfail += test_perms<cla3p::complex8_t>(strict); numtests++;

	print_summary();
}
/*-------------------------------------------------*/
} // namespace tests
} // namespace cla3p
/*-------------------------------------------------*/
