// this file inc
#include "dns_default_lsolver.hpp"

// system

// 3rd

// cla3p
#include "../dense.hpp"
#include "../proxies/lapack_proxy.hpp"
#include "../support/error.hpp"
#include "../checks/all_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns { 
/*-------------------------------------------------*/
template <typename T>
DefaultLSolver<T>::DefaultLSolver()
{
	defaults();
}
/*-------------------------------------------------*/
template <typename T>
DefaultLSolver<T>::DefaultLSolver(uint_t n)
{
	defaults();
	reserve(n);
}
/*-------------------------------------------------*/
template <typename T>
DefaultLSolver<T>::~DefaultLSolver()
{
	clearPrivately();
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::defaults()
{
	info() = 0;
}
/*-------------------------------------------------*/
template <typename T> int_t&              DefaultLSolver<T>::info  (){ return m_info;   }
template <typename T> T&                  DefaultLSolver<T>::factor(){ return m_factor; }
template <typename T> T&                  DefaultLSolver<T>::buffer(){ return m_buffer; }
template <typename T> std::vector<int_t>& DefaultLSolver<T>::ipiv1 (){ return m_ipiv1;  }
/*-------------------------------------------------*/
template <typename T> const int_t&              DefaultLSolver<T>::info  () const { return m_info;   }
template <typename T> const T&                  DefaultLSolver<T>::factor() const { return m_factor; }
template <typename T> const T&                  DefaultLSolver<T>::buffer() const { return m_buffer; }
template <typename T> const std::vector<int_t>& DefaultLSolver<T>::ipiv1 () const { return m_ipiv1;  }
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::clearPrivately()
{
	factor().clear();
	buffer().clear();
	ipiv1().clear();

	defaults();
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::absorbInput(const T& mat)
{
	bool mat_fits_in_buffer = (buffer().nrows() >= mat.nrows() && buffer().ncols() >= mat.ncols());

	if(mat_fits_in_buffer) {

		// create a compatible factor using buffer & copy mat
		factor() = T::wrap(mat.prop(), mat.nrows(), mat.ncols(), buffer().values(), mat.nrows(), false);
		factor().setBlock(0, 0, mat);

	} else {

		factor() = mat.copy();

	} // use buffer or fresh copy
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::fdecompose()
{
	if(factor().prop().isGeneral()) {

		ipiv1().resize(std::min(factor().nrows(), factor().ncols()));
		info() = lapack::getrf(factor().nrows(), factor().ncols(), factor().values(), factor().ld(), ipiv1().data());

	} else if(factor().prop().isSymmetric()) {

		ipiv1().resize(factor().ncols());
		info() = lapack::sytrf(factor().prop().cuplo(), factor().ncols(), factor().values(), factor().ld(), ipiv1().data());

	} else if(factor().prop().isHermitian()) {

		ipiv1().resize(factor().ncols());
		info() = lapack::hetrf(factor().prop().cuplo(), factor().ncols(), factor().values(), factor().ld(), ipiv1().data());

	} else {

		throw Exception("Unreachable");

	} // prop

	lapack_info_check(info());
}
/*-------------------------------------------------*/
/*----------------   VIRTUALS   -------------------*/
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::reserve(uint_t n)
{
	if(buffer().nrows() < n && buffer().ncols() < n) {
		buffer().clear();
		buffer() = T::init(n, n);
	}
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::clear()
{
	clearPrivately();
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::decompose(const T& mat)
{
	factor().clear();
	default_decomp_input_check(mat);
	absorbInput(mat);
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::idecompose(T& mat)
{
	factor().clear();
	default_decomp_input_check(mat);
	factor() = mat.move();
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::solve(T& rhs) const
{
	default_solve_input_check(rhs);

	if(factor().empty()) {
		throw InvalidOp("Decomposition stage is not performed");
	} // empty factor

	int_t info = 0;

	if(factor().prop().isGeneral()) {

		info = lapack::getrs('N', factor().ncols(), rhs.ncols(), factor().values(), factor().ld(), ipiv1().data(), rhs.values(), rhs.ld());

	} else if(factor().prop().isSymmetric()) {

		info = lapack::sytrs(factor().prop().cuplo(), factor().ncols(), rhs.ncols(), factor().values(), factor().ld(), ipiv1().data(), rhs.values(), rhs.ld());

	} else if(factor().prop().isHermitian()) {

		info = lapack::hetrs(factor().prop().cuplo(), factor().ncols(), rhs.ncols(), factor().values(), factor().ld(), ipiv1().data(), rhs.values(), rhs.ld());

	} else {

		throw Exception("Unreachable");

	} // prop

	lapack_info_check(info);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class DefaultLSolver<RdMatrix>;
template class DefaultLSolver<RfMatrix>;
template class DefaultLSolver<CdMatrix>;
template class DefaultLSolver<CfMatrix>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
