// this file inc
#include "bulk_dns_test.hpp"
#include "test_macros.hpp"

// system

// 3rd

// cla3p
#include "cla3p/src/support/utils.hpp"
#include "cla3p/src/bulk/dns.hpp"
#include "cla3p/src/bulk/dns_io.hpp"

#include "naive_matrix_ops.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace tests {
/*-------------------------------------------------*/
static uint_t staticm = 0;
static uint_t staticn = 0;
/*-------------------------------------------------*/
template <class T>
static real_t cmptol()
{
	if (std::is_same<T, int_t>::value) return 0;
	if (std::is_same<T, uint_t>::value) return 0;
	if (std::is_same<T, real_t>::value) return 1.e-12;
	if (std::is_same<T, real4_t>::value) return 1.e-6;
	if (std::is_same<T, complex_t>::value) return 1.e-12;
	if (std::is_same<T, complex8_t>::value) return 1.e-6;

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static T* naive_fill_vals(uint_t m, uint_t n, uint_t lda, T ref)
{
	T *a = bulk::dns::alloc<T>(m, n, lda);

	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < lda; i++) {
			bulk::dns::entry(lda,a,i,j) = ref;
		} // j
	} // j
	return a;
}
/*-------------------------------------------------*/
static bool element_is_in_active_range(uplo_t uplo, uint_t m, uint_t n, uint_t i, uint_t j)
{
	/**/ if(uplo == uplo_t::U) return (i < m && i <= j);
	else if(uplo == uplo_t::L) return (i < m && i >= j);

	return (i < m && j < n);
}
/*-------------------------------------------------*/
template <class T>
static int_t naive_check_vals(uplo_t uplo, uint_t m, uint_t n, const T *a, uint_t lda, T val)
{
	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < lda; i++) {
			T aij = bulk::dns::entry(lda,a,i,j);
			if(element_is_in_active_range(uplo,m,n,i,j) && aij != val) return 1;
		} // i
	} // j

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t naive_check_complementary_vals(uplo_t uplo, uint_t m, uint_t n, const T *a, uint_t lda, T ref)
{
	for(uint_t j = 0; j < n; j++) {
		for(uint_t i = 0; i < lda; i++) {
			T aij = bulk::dns::entry(lda,a,i,j);
			if(!element_is_in_active_range(uplo,m,n,i,j) && aij != ref) return 1;
		} // i
	} // j

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t naive_compare_vals(uplo_t uplo, uint_t m, uint_t n, bool trA, bool conjA, const T *a, uint_t lda, const T *b, uint_t ldb, T coeff)
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
			T bij = bulk::dns::entry(ldb,b,i,j);
			T aij = T(0);
			if(!trA && !conjA) aij =      bulk::dns::entry(lda,a,i,j) ;
			if(!trA &&  conjA) aij = conj(bulk::dns::entry(lda,a,i,j));
			if( trA && !conjA) aij =      bulk::dns::entry(lda,a,j,i) ;
			if( trA &&  conjA) aij = conj(bulk::dns::entry(lda,a,j,i));
			real_t diff = ddabs<T,real_t>(coeff * aij - bij);
			if(element_is_in_active_range(uplo,Brows,Bcols,i,j) && diff > cmptol<T>()) return 1;
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
			T aij = bulk::dns::entry(lda,a,i,j);
			T aji = bulk::dns::entry(lda,a,j,i);
			if(conjop && i > j) aij = conj(aij);
			real_t diff = ddabs<T,real_t>(aij - aji);
			if(element_is_in_active_range(uplo_t::F,n,n,i,j) && diff > cmptol<T>()) return 1;
		} // i
	} // j

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_zero_in(uplo_t uplo, uint_t m, uint_t n, uint_t lda)
{
	T val = T(0);
	T ref = T(1);

	T *a = naive_fill_vals<T>(m, n, lda, ref);
	bulk::dns::zero(uplo, m, n, a, lda);
	if(naive_check_vals              <T>(uplo, m, n, a, lda, val)) return 1;
	if(naive_check_complementary_vals<T>(uplo, m, n, a, lda, ref)) return 1;
	i_free(a);

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_zero(bool strict)
{
	uint_t m = staticm;
	uint_t n = staticn;

	{
		uint_t lda = m;
		if(test_zero_in<T>(uplo_t::F, m, n, lda)) fatal_error();
		if(test_zero_in<T>(uplo_t::U, m, n, lda)) fatal_error();
		if(test_zero_in<T>(uplo_t::L, m, n, lda)) fatal_error();
	}

	{
		uint_t lda = m + 15;
		if(test_zero_in<T>(uplo_t::F, m, n, lda)) fatal_error();
		if(test_zero_in<T>(uplo_t::U, m, n, lda)) fatal_error();
		if(test_zero_in<T>(uplo_t::L, m, n, lda)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_fill_in(uplo_t uplo, uint_t m, uint_t n, uint_t lda)
{
	T val = T(5);
	T ref = T(1);

	T *a = naive_fill_vals<T>(m, n, lda, ref);
	bulk::dns::fill(uplo, m, n, a, lda, val);
	if(naive_check_vals              <T>(uplo, m, n, a, lda, val)) return 1;
	if(naive_check_complementary_vals<T>(uplo, m, n, a, lda, ref)) return 1;
	i_free(a);

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_fill(bool strict)
{
	uint_t m = staticm;
	uint_t n = staticn;

	{
		uint_t lda = m;
		if(test_fill_in<T>(uplo_t::F, m, n, lda)) fatal_error();
		if(test_fill_in<T>(uplo_t::U, m, n, lda)) fatal_error();
		if(test_fill_in<T>(uplo_t::L, m, n, lda)) fatal_error();
	}

	{
		uint_t lda = m + 15;
		if(test_fill_in<T>(uplo_t::F, m, n, lda)) fatal_error();
		if(test_fill_in<T>(uplo_t::U, m, n, lda)) fatal_error();
		if(test_fill_in<T>(uplo_t::L, m, n, lda)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_rand_in(uplo_t uplo, uint_t m, uint_t n, uint_t lda)
{
	T ref = T(1000);

	T *a = naive_fill_vals<T>(m, n, lda, ref);
	bulk::dns::rand(uplo, m, n, a, lda);
	if(naive_check_complementary_vals<T>(uplo, m, n, a, lda, ref)) return 1;
	i_free(a);

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_rand(bool strict)
{
	uint_t m = staticm;
	uint_t n = staticn;

	{
		uint_t lda = m;
		if(test_rand_in<T>(uplo_t::F, m, n, lda)) fatal_error();
		if(test_rand_in<T>(uplo_t::U, m, n, lda)) fatal_error();
		if(test_rand_in<T>(uplo_t::L, m, n, lda)) fatal_error();
	}

	{
		uint_t lda = m + 5;
		if(test_rand_in<T>(uplo_t::F, m, n, lda)) fatal_error();
		if(test_rand_in<T>(uplo_t::U, m, n, lda)) fatal_error();
		if(test_rand_in<T>(uplo_t::L, m, n, lda)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_copy_in(uplo_t uplo, uint_t m, uint_t n, uint_t lda, uint_t ldb, T coeff)
{
	T ref = T(1000);

	T *a = naive_fill_vals<T>(m, n, lda, ref);
	T *b = naive_fill_vals<T>(m, n, ldb, ref);
	bulk::dns::rand(uplo, m, n, a, lda);
	bulk::dns::copy(uplo, m, n, a, lda, b, ldb, coeff);
	if(naive_compare_vals<T>(uplo, m, n, false, false, a, lda, b, ldb, coeff)) return 1;
	if(naive_check_complementary_vals<T>(uplo, m, n, a, lda, ref)) return 1;
	if(naive_check_complementary_vals<T>(uplo, m, n, b, ldb, ref)) return 1;
	i_free(a);
	i_free(b);

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_copy(bool strict)
{
	uint_t m = staticm;
	uint_t n = staticn;

	{
		uint_t lda = m;
		uint_t ldb = m;
		if(test_copy_in<T>(uplo_t::F, m, n, lda, ldb, 1)) fatal_error();
		if(test_copy_in<T>(uplo_t::U, m, n, lda, ldb, 1)) fatal_error();
		if(test_copy_in<T>(uplo_t::L, m, n, lda, ldb, 1)) fatal_error();
		if(test_copy_in<T>(uplo_t::F, m, n, lda, ldb, 2)) fatal_error();
		if(test_copy_in<T>(uplo_t::U, m, n, lda, ldb, 2)) fatal_error();
		if(test_copy_in<T>(uplo_t::L, m, n, lda, ldb, 2)) fatal_error();
	}

	{
		uint_t lda = m +  5;
		uint_t ldb = m + 15;
		if(test_copy_in<T>(uplo_t::F, m, n, lda, ldb, 1)) fatal_error();
		if(test_copy_in<T>(uplo_t::U, m, n, lda, ldb, 1)) fatal_error();
		if(test_copy_in<T>(uplo_t::L, m, n, lda, ldb, 1)) fatal_error();
		if(test_copy_in<T>(uplo_t::F, m, n, lda, ldb, 2)) fatal_error();
		if(test_copy_in<T>(uplo_t::U, m, n, lda, ldb, 2)) fatal_error();
		if(test_copy_in<T>(uplo_t::L, m, n, lda, ldb, 2)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T, class Tr>
static int_t test_real_imag_in(uplo_t uplo, uint_t m, uint_t n, uint_t lda, uint_t ldb)
{
	T cref = T(1000);
	Tr rref = Tr(1000);

	uint_t ldar = (ldb == m ? m : ldb + 10);
	uint_t ldai = (ldb == m ? m : ldb + 12);

	T *a = naive_fill_vals<T>(m, n, lda, cref);
	T *b = naive_fill_vals<T>(m, n, ldb, cref);
	Tr *a_real = naive_fill_vals<Tr>(m, n, ldar, rref);
	Tr *a_imag = naive_fill_vals<Tr>(m, n, ldai, rref);
	bulk::dns::rand(uplo, m, n, a, lda);
	bulk::dns::get_real(uplo, m, n, a, lda, a_real, ldar);
	bulk::dns::get_imag(uplo, m, n, a, lda, a_imag, ldai);
	bulk::dns::set_real(uplo, m, n, a_real, ldar, b, ldb);
	bulk::dns::set_imag(uplo, m, n, a_imag, ldai, b, ldb);
	if(naive_compare_vals<T>(uplo, m, n, false, false, a, lda, b, ldb, 1)) return 1;
	if(naive_check_complementary_vals<T>(uplo, m, n, a, lda, cref)) return 1;
	if(naive_check_complementary_vals<T>(uplo, m, n, b, ldb, cref)) return 1;
	if(naive_check_complementary_vals<Tr>(uplo, m, n, a_real, ldar, rref)) return 1;
	if(naive_check_complementary_vals<Tr>(uplo, m, n, a_imag, ldai, rref)) return 1;
	i_free(a);
	i_free(b);
	i_free(a_real);
	i_free(a_imag);

	return 0;
}
/*-------------------------------------------------*/
template <class T, class Tr>
static int_t test_real_imag(bool strict)
{
	uint_t m = staticm;
	uint_t n = staticn;

	{
		uint_t lda = m;
		uint_t ldb = m;
		if(test_real_imag_in<T,Tr>(uplo_t::F, m, n, lda, ldb)) fatal_error();
		if(test_real_imag_in<T,Tr>(uplo_t::U, m, n, lda, ldb)) fatal_error();
		if(test_real_imag_in<T,Tr>(uplo_t::L, m, n, lda, ldb)) fatal_error();
		if(test_real_imag_in<T,Tr>(uplo_t::F, m, n, lda, ldb)) fatal_error();
		if(test_real_imag_in<T,Tr>(uplo_t::U, m, n, lda, ldb)) fatal_error();
		if(test_real_imag_in<T,Tr>(uplo_t::L, m, n, lda, ldb)) fatal_error();
	}

	{
		uint_t lda = m +  5;
		uint_t ldb = m + 15;
		if(test_real_imag_in<T,Tr>(uplo_t::F, m, n, lda, ldb)) fatal_error();
		if(test_real_imag_in<T,Tr>(uplo_t::U, m, n, lda, ldb)) fatal_error();
		if(test_real_imag_in<T,Tr>(uplo_t::L, m, n, lda, ldb)) fatal_error();
		if(test_real_imag_in<T,Tr>(uplo_t::F, m, n, lda, ldb)) fatal_error();
		if(test_real_imag_in<T,Tr>(uplo_t::U, m, n, lda, ldb)) fatal_error();
		if(test_real_imag_in<T,Tr>(uplo_t::L, m, n, lda, ldb)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_scale_in(uplo_t uplo, uint_t m, uint_t n, uint_t lda, uint_t ldb, T coeff)
{
	T ref = T(1000);

	T *a = naive_fill_vals<T>(m, n, lda, ref);
	T *b = naive_fill_vals<T>(m, n, ldb, ref);
	bulk::dns::rand(uplo, m, n, a, lda);
	bulk::dns::copy(uplo, m, n, a, lda, b, ldb);
	bulk::dns::scale(uplo, m, n, b, ldb, coeff);
	if(naive_compare_vals<T>(uplo, m, n, false, false, a, lda, b, ldb, coeff)) return 1;
	if(naive_check_complementary_vals<T>(uplo, m, n, a, lda, ref)) return 1;
	if(naive_check_complementary_vals<T>(uplo, m, n, b, ldb, ref)) return 1;
	i_free(a);
	i_free(b);

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_scale(bool strict)
{
	uint_t m = staticm;
	uint_t n = staticn;

	{
		uint_t lda = m;
		uint_t ldb = m;
		if(test_scale_in<T>(uplo_t::F, m, n, lda, ldb, 5)) fatal_error();
		if(test_scale_in<T>(uplo_t::U, m, n, lda, ldb, 5)) fatal_error();
		if(test_scale_in<T>(uplo_t::L, m, n, lda, ldb, 5)) fatal_error();
	}

	{
		uint_t lda = m +  5;
		uint_t ldb = m + 15;
		if(test_scale_in<T>(uplo_t::F, m, n, lda, ldb, 3)) fatal_error();
		if(test_scale_in<T>(uplo_t::U, m, n, lda, ldb, 3)) fatal_error();
		if(test_scale_in<T>(uplo_t::L, m, n, lda, ldb, 3)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_ctranspose_in(uint_t m, uint_t n, uint_t lda, uint_t ldb, T coeff, bool conjop)
{
	T ref = T(1000);
	uplo_t uplo = uplo_t::F;

	T *a = naive_fill_vals<T>(m, n, lda, ref);
	T *b = naive_fill_vals<T>(n, m, ldb, ref);
	bulk::dns::rand(uplo, m, n, a, lda);
	if(conjop) bulk::dns::conjugate_transpose(m, n, a, lda, b, ldb, coeff);
	else       bulk::dns::transpose(m, n, a, lda, b, ldb, coeff);
	if(naive_compare_vals<T>(uplo, m, n, true, conjop, a, lda, b, ldb, coeff)) return 1;
	if(naive_check_complementary_vals<T>(uplo, m, n, a, lda, ref)) return 1;
	if(naive_check_complementary_vals<T>(uplo, n, m, b, ldb, ref)) return 1;
	i_free(a);
	i_free(b);

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_transpose(bool strict)
{
	uint_t m = staticm;
	uint_t n = staticn;

	{
		uint_t lda = m;
		uint_t ldb = n;
		if(test_ctranspose_in<T>(m, n, lda, ldb, 1., false)) fatal_error();
		if(test_ctranspose_in<T>(m, n, lda, ldb, 5., false)) fatal_error();
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
	uint_t m = staticm;
	uint_t n = staticn;

	{
		uint_t lda = m;
		uint_t ldb = n;
		if(test_ctranspose_in<T>(m, n, lda, ldb,  1, true)) fatal_error();
		if(test_ctranspose_in<T>(m, n, lda, ldb, -5, true)) fatal_error();
	}

	{
		uint_t lda = m +  5;
		uint_t ldb = n + 15;
		if(test_ctranspose_in<T>(m, n, lda, ldb, 1, true)) fatal_error();
		if(test_ctranspose_in<T>(m, n, lda, ldb, 3, true)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_conjugate_in(uplo_t uplo, uint_t m, uint_t n, uint_t lda, uint_t ldb, real_t coeff)
{
	T ref = T(1000);

	T *a = naive_fill_vals<T>(m, n, lda, ref);
	T *b = naive_fill_vals<T>(m, n, ldb, ref);
	bulk::dns::rand(uplo, m, n, a, lda);
	bulk::dns::copy(uplo, m, n, a, lda, b, ldb);
	bulk::dns::conjugate(uplo, m, n, b, ldb, coeff);
	if(naive_compare_vals<T>(uplo, m, n, false, true, a, lda, b, ldb, coeff)) return 1;
	if(naive_check_complementary_vals<T>(uplo, m, n, a, lda, ref)) return 1;
	if(naive_check_complementary_vals<T>(uplo, m, n, b, ldb, ref)) return 1;
	i_free(a);
	i_free(b);

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_conjugate(bool strict)
{
	uint_t m = staticm;
	uint_t n = staticn;

	{
		uint_t lda = m;
		uint_t ldb = m;
		if(test_conjugate_in<T>(uplo_t::F, m, n, lda, ldb,  1)) fatal_error();
		if(test_conjugate_in<T>(uplo_t::U, m, n, lda, ldb,  1)) fatal_error();
		if(test_conjugate_in<T>(uplo_t::L, m, n, lda, ldb,  1)) fatal_error();
		if(test_conjugate_in<T>(uplo_t::F, m, n, lda, ldb, -5)) fatal_error();
		if(test_conjugate_in<T>(uplo_t::U, m, n, lda, ldb, -5)) fatal_error();
		if(test_conjugate_in<T>(uplo_t::L, m, n, lda, ldb, -5)) fatal_error();
	}

	{
		uint_t lda = m +  5;
		uint_t ldb = m + 15;
		if(test_conjugate_in<T>(uplo_t::F, m, n, lda, ldb, 1)) fatal_error();
		if(test_conjugate_in<T>(uplo_t::U, m, n, lda, ldb, 1)) fatal_error();
		if(test_conjugate_in<T>(uplo_t::L, m, n, lda, ldb, 1)) fatal_error();
		if(test_conjugate_in<T>(uplo_t::F, m, n, lda, ldb, 3)) fatal_error();
		if(test_conjugate_in<T>(uplo_t::U, m, n, lda, ldb, 3)) fatal_error();
		if(test_conjugate_in<T>(uplo_t::L, m, n, lda, ldb, 3)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_syhe2ge_in(bool conjop, uplo_t uplo, uint_t n, uint_t lda)
{
	T ref = T(1000);

	T *a = naive_fill_vals<T>(n, n, lda, ref);
	if(conjop) {
		bulk::dns::rand(uplo, n, n, a, lda);
		bulk::dns::he2ge(uplo, n, a, lda);
	} else {
		bulk::dns::rand(uplo, n, n, a, lda);
		bulk::dns::sy2ge(uplo, n, a, lda);
	} // conjop
	if(naive_compare_upper_lower_part(conjop, n, a, lda)) return 1;
	if(naive_check_complementary_vals<T>(uplo_t::F, n, n, a, lda, ref)) return 1;
	i_free(a);

	return 0;
}
/*-------------------------------------------------*/
template <class T>
static int_t test_sy2ge(bool strict)
{
	uint_t m = staticm;
	uint_t n = m;

	{
		uint_t lda = m;
		if(test_syhe2ge_in<T>(false, uplo_t::U, n, lda)) fatal_error();
		if(test_syhe2ge_in<T>(false, uplo_t::L, n, lda)) fatal_error();
	}

	{
		uint_t lda = m + 5;
		if(test_syhe2ge_in<T>(false, uplo_t::U, n, lda)) fatal_error();
		if(test_syhe2ge_in<T>(false, uplo_t::L, n, lda)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_he2ge(bool strict)
{
	uint_t m = staticm;
	uint_t n = m;

	{
		uint_t lda = m;
		if(test_syhe2ge_in<T>(true, uplo_t::U, n, lda)) fatal_error();
		if(test_syhe2ge_in<T>(true, uplo_t::L, n, lda)) fatal_error();
	}                                      
                                         
	{                                      
		uint_t lda = m + 5;                  
		if(test_syhe2ge_in<T>(true, uplo_t::U, n, lda)) fatal_error();
		if(test_syhe2ge_in<T>(true, uplo_t::L, n, lda)) fatal_error();
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
template <class T, class Tr>
static int_t test_nrm_in(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, uint_t lda, WhichNorm which)
{
	if(ptype == prop_t::HERMITIAN) {
		if (!(std::is_same<T,complex_t>::value || std::is_same<T,complex8_t>::value)) {
			return 0;
		}
	}

	T ref = T(1000);

	Property prop(ptype, uplo);
	bool square = prop.isSquare();
	bool samelda = (lda == m);

	if(square) {
		m = std::min(m,n);
		n = std::min(m,n);
		if(samelda) lda = m;
	} // square

	T *a = naive_fill_vals<T>(m, n, lda, ref);
	bulk::dns::rand(uplo, m, n, a, lda);
	if(ptype == prop_t::HERMITIAN) {
		for(uint_t j = 0; j < n; j++) {
			cla3p::setim(cla3p::bulk::dns::entry(lda,a,j,j),0);
		} // j
	}

	Tr ret = 0.;
	Tr ret2 = 0.;

	if(which == WhichNorm::TEST_NRM_ONE) ret = bulk::dns::norm_one(ptype, uplo, m, n, a, lda);
	if(which == WhichNorm::TEST_NRM_INF) ret = bulk::dns::norm_inf(ptype, uplo, m, n, a, lda);
	if(which == WhichNorm::TEST_NRM_MAX) ret = bulk::dns::norm_max(ptype, uplo, m, n, a, lda);
	if(which == WhichNorm::TEST_NRM_FRO) ret = bulk::dns::norm_fro(ptype, uplo, m, n, a, lda);

	if(which == WhichNorm::TEST_NRM_ONE) ret2 = naive_norm_one<T,Tr>(ptype, uplo, m, n, a, lda);
	if(which == WhichNorm::TEST_NRM_INF) ret2 = naive_norm_inf<T,Tr>(ptype, uplo, m, n, a, lda);
	if(which == WhichNorm::TEST_NRM_MAX) ret2 = naive_norm_max<T,Tr>(ptype, uplo, m, n, a, lda);
	if(which == WhichNorm::TEST_NRM_FRO) ret2 = naive_norm_fro<T,Tr>(ptype, uplo, m, n, a, lda);

	real_t diff = ddabs<T,real_t>(ret - ret2) / (std::sqrt(m*n) * ret2);
	if(diff > cmptol<T>()){
		return 1;
	}
	i_free(a);

	return 0;
}
/*-------------------------------------------------*/
template <class T, class Tr>
static int_t test_nrmone(bool strict)
{
	uint_t m = staticm;
	uint_t n = staticn;

	{
		uint_t lda = m;
		if(test_nrm_in<T,Tr>(prop_t::GENERAL  , uplo_t::F, m, n, lda, WhichNorm::TEST_NRM_ONE)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::SYMMETRIC, uplo_t::U, m, n, lda, WhichNorm::TEST_NRM_ONE)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::HERMITIAN, uplo_t::U, m, n, lda, WhichNorm::TEST_NRM_ONE)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::SYMMETRIC, uplo_t::L, m, n, lda, WhichNorm::TEST_NRM_ONE)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::HERMITIAN, uplo_t::L, m, n, lda, WhichNorm::TEST_NRM_ONE)) fatal_error();
	}

	{
		uint_t lda = m +  5;
		if(test_nrm_in<T,Tr>(prop_t::GENERAL  , uplo_t::F, m, n, lda, WhichNorm::TEST_NRM_ONE)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::SYMMETRIC, uplo_t::U, m, n, lda, WhichNorm::TEST_NRM_ONE)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::HERMITIAN, uplo_t::U, m, n, lda, WhichNorm::TEST_NRM_ONE)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::SYMMETRIC, uplo_t::L, m, n, lda, WhichNorm::TEST_NRM_ONE)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::HERMITIAN, uplo_t::L, m, n, lda, WhichNorm::TEST_NRM_ONE)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T, class Tr>
static int_t test_nrminf(bool strict)
{
	uint_t m = staticm;
	uint_t n = staticn;

	{
		uint_t lda = m;
		if(test_nrm_in<T,Tr>(prop_t::GENERAL  , uplo_t::F, m, n, lda, WhichNorm::TEST_NRM_INF)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::SYMMETRIC, uplo_t::U, m, n, lda, WhichNorm::TEST_NRM_INF)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::HERMITIAN, uplo_t::U, m, n, lda, WhichNorm::TEST_NRM_INF)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::SYMMETRIC, uplo_t::L, m, n, lda, WhichNorm::TEST_NRM_INF)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::HERMITIAN, uplo_t::L, m, n, lda, WhichNorm::TEST_NRM_INF)) fatal_error();
	}

	{
		uint_t lda = m +  5;
		if(test_nrm_in<T,Tr>(prop_t::GENERAL  , uplo_t::F, m, n, lda, WhichNorm::TEST_NRM_INF)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::SYMMETRIC, uplo_t::U, m, n, lda, WhichNorm::TEST_NRM_INF)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::HERMITIAN, uplo_t::U, m, n, lda, WhichNorm::TEST_NRM_INF)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::SYMMETRIC, uplo_t::L, m, n, lda, WhichNorm::TEST_NRM_INF)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::HERMITIAN, uplo_t::L, m, n, lda, WhichNorm::TEST_NRM_INF)) fatal_error();
	}

	test_success();
	test_success();
}
/*-------------------------------------------------*/
template <class T, class Tr>
static int_t test_nrmmax(bool strict)
{
	uint_t m = staticm;
	uint_t n = staticn;

	{
		uint_t lda = m;
		if(test_nrm_in<T,Tr>(prop_t::GENERAL  , uplo_t::F, m, n, lda, WhichNorm::TEST_NRM_MAX)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::SYMMETRIC, uplo_t::U, m, n, lda, WhichNorm::TEST_NRM_MAX)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::HERMITIAN, uplo_t::U, m, n, lda, WhichNorm::TEST_NRM_MAX)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::SYMMETRIC, uplo_t::L, m, n, lda, WhichNorm::TEST_NRM_MAX)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::HERMITIAN, uplo_t::L, m, n, lda, WhichNorm::TEST_NRM_MAX)) fatal_error();
	}                                                            
                                                               
	{                                                            
		uint_t lda = m +  5;                                       
		if(test_nrm_in<T,Tr>(prop_t::GENERAL  , uplo_t::F, m, n, lda, WhichNorm::TEST_NRM_MAX)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::SYMMETRIC, uplo_t::U, m, n, lda, WhichNorm::TEST_NRM_MAX)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::HERMITIAN, uplo_t::U, m, n, lda, WhichNorm::TEST_NRM_MAX)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::SYMMETRIC, uplo_t::L, m, n, lda, WhichNorm::TEST_NRM_MAX)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::HERMITIAN, uplo_t::L, m, n, lda, WhichNorm::TEST_NRM_MAX)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T, class Tr>
static int_t test_nrmfro(bool strict)
{
	uint_t m = staticm;
	uint_t n = staticn;

	{
		uint_t lda = m;
		if(test_nrm_in<T,Tr>(prop_t::GENERAL  , uplo_t::F, m, n, lda, WhichNorm::TEST_NRM_FRO)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::SYMMETRIC, uplo_t::U, m, n, lda, WhichNorm::TEST_NRM_FRO)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::HERMITIAN, uplo_t::U, m, n, lda, WhichNorm::TEST_NRM_FRO)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::SYMMETRIC, uplo_t::L, m, n, lda, WhichNorm::TEST_NRM_FRO)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::HERMITIAN, uplo_t::L, m, n, lda, WhichNorm::TEST_NRM_FRO)) fatal_error();
	}                                                            
                                                               
	{                                                            
		uint_t lda = m +  5;                                       
		if(test_nrm_in<T,Tr>(prop_t::GENERAL  , uplo_t::F, m, n, lda, WhichNorm::TEST_NRM_FRO)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::SYMMETRIC, uplo_t::U, m, n, lda, WhichNorm::TEST_NRM_FRO)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::HERMITIAN, uplo_t::U, m, n, lda, WhichNorm::TEST_NRM_FRO)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::SYMMETRIC, uplo_t::L, m, n, lda, WhichNorm::TEST_NRM_FRO)) fatal_error();
		if(test_nrm_in<T,Tr>(prop_t::HERMITIAN, uplo_t::L, m, n, lda, WhichNorm::TEST_NRM_FRO)) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
template <class T>
static int_t test_perms_in(prop_t ptype, uplo_t uplo, uint_t m, uint_t n, uint_t lda, uint_t ldb, uint_t ldc, bool nullP, bool nullQ)
{
	if(ptype == prop_t::HERMITIAN) {
		if (!(std::is_same<T,complex_t>::value || std::is_same<T,complex8_t>::value)) {
			return 0;
		}
	}

	T ref = T(1000);

	Property prop(ptype, uplo);
	bool square = prop.isSquare();
	bool samelda = (lda == m);
	bool sameldb = (ldb == m);
	bool sameldc = (ldc == m);

	if(square) {
		m = std::min(m,n);
		n = std::min(m,n);
		if(samelda) lda = m;
		if(sameldb) ldb = m;
		if(sameldc) ldc = m;
	} // square

	{
		std::vector<uint_t> vecP = create_random_perm(m);
		std::vector<uint_t> vecQ = create_random_perm(n);
		const uint_t *P = (nullP ? nullptr : vecP.data());
		const uint_t *Q = (nullQ ? nullptr : vecQ.data());
		T *a = naive_fill_vals<T>(m, n, lda, ref);
		T *b = naive_fill_vals<T>(m, n, ldb, ref);
		T *c = naive_fill_vals<T>(m, n, ldc, ref);
		bulk::dns::rand(uplo, m, n, a, lda);
		if(ptype == prop_t::HERMITIAN) {
			for(uint_t j = 0; j < n; j++) {
				cla3p::setim(cla3p::bulk::dns::entry(lda,a,j,j),0);
			} // j
		}
		bulk::dns::permute(ptype, uplo, m, n, a, lda, b, ldb, P, Q);
		naive_permute(ptype, uplo, m, n, a, lda, c, ldc, P, Q);
		if(naive_compare_vals<T>(uplo, m, n, false, false, b, ldb, c, ldc, 1.)) return 1;
		if(naive_check_complementary_vals<T>(uplo, m, n, b, ldb, ref)) return 1;
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
	uint_t m = staticm;
	uint_t n = staticn;

	{
		uint_t lda = m;
		uint_t ldb = m;
		if(test_perms_in<T>(prop_t::GENERAL  , uplo_t::F, m, n, lda, ldb, ldb, false, false)) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, uplo_t::U, m, n, lda, ldb, ldb, false, false)) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, uplo_t::U, m, n, lda, ldb, ldb, false, false)) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, uplo_t::L, m, n, lda, ldb, ldb, false, false)) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, uplo_t::L, m, n, lda, ldb, ldb, false, false)) fatal_error();

		if(test_perms_in<T>(prop_t::GENERAL  , uplo_t::F, m, n, lda, ldb, ldb, true , false)) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, uplo_t::U, m, n, lda, ldb, ldb, true , false)) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, uplo_t::U, m, n, lda, ldb, ldb, true , false)) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, uplo_t::L, m, n, lda, ldb, ldb, true , false)) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, uplo_t::L, m, n, lda, ldb, ldb, true , false)) fatal_error();

		if(test_perms_in<T>(prop_t::GENERAL  , uplo_t::F, m, n, lda, ldb, ldb, false, true )) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, uplo_t::U, m, n, lda, ldb, ldb, false, true )) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, uplo_t::U, m, n, lda, ldb, ldb, false, true )) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, uplo_t::L, m, n, lda, ldb, ldb, false, true )) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, uplo_t::L, m, n, lda, ldb, ldb, false, true )) fatal_error();

		if(test_perms_in<T>(prop_t::GENERAL  , uplo_t::F, m, n, lda, ldb, ldb, true , true )) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, uplo_t::U, m, n, lda, ldb, ldb, true , true )) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, uplo_t::U, m, n, lda, ldb, ldb, true , true )) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, uplo_t::L, m, n, lda, ldb, ldb, true , true )) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, uplo_t::L, m, n, lda, ldb, ldb, true , true )) fatal_error();
	}

	{
		uint_t lda = m +  5;
		uint_t ldb = m + 15;
		if(test_perms_in<T>(prop_t::GENERAL  , uplo_t::F, m, n, lda, ldb, ldb, false, false)) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, uplo_t::U, m, n, lda, ldb, ldb, false, false)) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, uplo_t::U, m, n, lda, ldb, ldb, false, false)) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, uplo_t::L, m, n, lda, ldb, ldb, false, false)) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, uplo_t::L, m, n, lda, ldb, ldb, false, false)) fatal_error();

		if(test_perms_in<T>(prop_t::GENERAL  , uplo_t::F, m, n, lda, ldb, ldb, true , false)) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, uplo_t::U, m, n, lda, ldb, ldb, true , false)) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, uplo_t::U, m, n, lda, ldb, ldb, true , false)) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, uplo_t::L, m, n, lda, ldb, ldb, true , false)) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, uplo_t::L, m, n, lda, ldb, ldb, true , false)) fatal_error();

		if(test_perms_in<T>(prop_t::GENERAL  , uplo_t::F, m, n, lda, ldb, ldb, false, true )) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, uplo_t::U, m, n, lda, ldb, ldb, false, true )) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, uplo_t::U, m, n, lda, ldb, ldb, false, true )) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, uplo_t::L, m, n, lda, ldb, ldb, false, true )) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, uplo_t::L, m, n, lda, ldb, ldb, false, true )) fatal_error();

		if(test_perms_in<T>(prop_t::GENERAL  , uplo_t::F, m, n, lda, ldb, ldb, true , true )) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, uplo_t::U, m, n, lda, ldb, ldb, true , true )) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, uplo_t::U, m, n, lda, ldb, ldb, true , true )) fatal_error();
		if(test_perms_in<T>(prop_t::SYMMETRIC, uplo_t::L, m, n, lda, ldb, ldb, true , true )) fatal_error();
		if(test_perms_in<T>(prop_t::HERMITIAN, uplo_t::L, m, n, lda, ldb, ldb, true , true )) fatal_error();
	}

	test_success();
}
/*-------------------------------------------------*/
static int_t bulk_dns_dims(bool strict, uint_t m, uint_t n)
{
	staticm = m;
	staticn = n;

	int_t numtests = 0;
	int_t numfail = 0;

	numfail += test_fill<cla3p::int_t>(strict); numtests++;
	numfail += test_fill<cla3p::uint_t>(strict); numtests++;
	numfail += test_fill<cla3p::real_t>(strict); numtests++;
	numfail += test_fill<cla3p::real4_t>(strict); numtests++;
	numfail += test_fill<cla3p::complex_t>(strict); numtests++;
	numfail += test_fill<cla3p::complex8_t>(strict); numtests++;

	numfail += test_zero<cla3p::int_t>(strict); numtests++;
	numfail += test_zero<cla3p::uint_t>(strict); numtests++;
	numfail += test_zero<cla3p::real_t>(strict); numtests++;
	numfail += test_zero<cla3p::real4_t>(strict); numtests++;
	numfail += test_zero<cla3p::complex_t>(strict); numtests++;
	numfail += test_zero<cla3p::complex8_t>(strict); numtests++;

	numfail += test_rand<cla3p::int_t>(strict); numtests++;
	numfail += test_rand<cla3p::uint_t>(strict); numtests++;
	numfail += test_rand<cla3p::real_t>(strict); numtests++;
	numfail += test_rand<cla3p::real4_t>(strict); numtests++;
	numfail += test_rand<cla3p::complex_t>(strict); numtests++;
	numfail += test_rand<cla3p::complex8_t>(strict); numtests++;

	numfail += test_copy<cla3p::int_t>(strict); numtests++;
	numfail += test_copy<cla3p::uint_t>(strict); numtests++;
	numfail += test_copy<cla3p::real_t>(strict); numtests++;
	numfail += test_copy<cla3p::real4_t>(strict); numtests++;
	numfail += test_copy<cla3p::complex_t>(strict); numtests++;
	numfail += test_copy<cla3p::complex8_t>(strict); numtests++;

	numfail += test_real_imag<cla3p::complex_t,cla3p::real_t>(strict); numtests++;
	numfail += test_real_imag<cla3p::complex8_t,cla3p::real4_t>(strict); numtests++;

	numfail += test_scale<cla3p::int_t>(strict); numtests++;
	numfail += test_scale<cla3p::uint_t>(strict); numtests++;
	numfail += test_scale<cla3p::real_t>(strict); numtests++;
	numfail += test_scale<cla3p::real4_t>(strict); numtests++;
	numfail += test_scale<cla3p::complex_t>(strict); numtests++;
	numfail += test_scale<cla3p::complex8_t>(strict); numtests++;

	numfail += test_transpose<cla3p::int_t>(strict); numtests++;
	numfail += test_transpose<cla3p::uint_t>(strict); numtests++;
	numfail += test_transpose<cla3p::real_t>(strict); numtests++;
	numfail += test_transpose<cla3p::real4_t>(strict); numtests++;
	numfail += test_transpose<cla3p::complex_t>(strict); numtests++;
	numfail += test_transpose<cla3p::complex8_t>(strict); numtests++;

	numfail += test_conjugate_transpose<cla3p::complex_t>(strict); numtests++;
	numfail += test_conjugate_transpose<cla3p::complex8_t>(strict); numtests++;

	numfail += test_conjugate<cla3p::complex_t>(strict); numtests++;
	numfail += test_conjugate<cla3p::complex8_t>(strict); numtests++;

	numfail += test_sy2ge<cla3p::int_t>(strict); numtests++;
	numfail += test_sy2ge<cla3p::uint_t>(strict); numtests++;
	numfail += test_sy2ge<cla3p::real_t>(strict); numtests++;
	numfail += test_sy2ge<cla3p::real4_t>(strict); numtests++;
	numfail += test_sy2ge<cla3p::complex_t>(strict); numtests++;
	numfail += test_sy2ge<cla3p::complex8_t>(strict); numtests++;

	numfail += test_he2ge<cla3p::complex_t>(strict); numtests++;
	numfail += test_he2ge<cla3p::complex8_t>(strict); numtests++;

	numfail += test_nrmone<cla3p::real_t    ,cla3p::real_t >(strict); numtests++;
	numfail += test_nrmone<cla3p::real4_t   ,cla3p::real4_t>(strict); numtests++;
	numfail += test_nrmone<cla3p::complex_t ,cla3p::real_t >(strict); numtests++;
	numfail += test_nrmone<cla3p::complex8_t,cla3p::real4_t>(strict); numtests++;

	numfail += test_nrminf<cla3p::real_t    ,cla3p::real_t >(strict); numtests++;
	numfail += test_nrminf<cla3p::real4_t   ,cla3p::real4_t>(strict); numtests++;
	numfail += test_nrminf<cla3p::complex_t ,cla3p::real_t >(strict); numtests++;
	numfail += test_nrminf<cla3p::complex8_t,cla3p::real4_t>(strict); numtests++;

	numfail += test_nrmmax<cla3p::real_t    ,cla3p::real_t >(strict); numtests++;
	numfail += test_nrmmax<cla3p::real4_t   ,cla3p::real4_t>(strict); numtests++;
	numfail += test_nrmmax<cla3p::complex_t ,cla3p::real_t >(strict); numtests++;
	numfail += test_nrmmax<cla3p::complex8_t,cla3p::real4_t>(strict); numtests++;

	numfail += test_nrmfro<cla3p::real_t    ,cla3p::real_t >(strict); numtests++;
	numfail += test_nrmfro<cla3p::real4_t   ,cla3p::real4_t>(strict); numtests++;
	numfail += test_nrmfro<cla3p::complex_t ,cla3p::real_t >(strict); numtests++;
	numfail += test_nrmfro<cla3p::complex8_t,cla3p::real4_t>(strict); numtests++;

	numfail += test_perms<cla3p::int_t>(strict); numtests++;
	numfail += test_perms<cla3p::uint_t>(strict); numtests++;
	numfail += test_perms<cla3p::real_t>(strict); numtests++;
	numfail += test_perms<cla3p::real4_t>(strict); numtests++;
	numfail += test_perms<cla3p::complex_t>(strict); numtests++;
	numfail += test_perms<cla3p::complex8_t>(strict); numtests++;

	print_summary();
}
/*-------------------------------------------------*/
int_t bulk_dns(bool strict)
{
	uint_t m = 0;
	uint_t n = 0;

	m =    5; n =  8; if(bulk_dns_dims(strict, m, n)) fatal_error();
	m =    8; n =  5; if(bulk_dns_dims(strict, m, n)) fatal_error();
	m = 705; n = 699; if(bulk_dns_dims(strict, m, n)) fatal_error();
	m = 793; n = 612; if(bulk_dns_dims(strict, m, n)) fatal_error();

	m =   1; n =   8; if(bulk_dns_dims(strict, m, n)) fatal_error();
	m =   5; n =   1; if(bulk_dns_dims(strict, m, n)) fatal_error();
	m = 705; n =   1; if(bulk_dns_dims(strict, m, n)) fatal_error();
	m =   1; n = 612; if(bulk_dns_dims(strict, m, n)) fatal_error();

	test_success();
}
/*-------------------------------------------------*/
} // namespace tests
} // namespace cla3p
/*-------------------------------------------------*/
