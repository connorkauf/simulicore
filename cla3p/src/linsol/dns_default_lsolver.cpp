// this file inc
#include "dns_default_lsolver.hpp"

// system

// 3rd

// cla3p
#include "../dense.hpp"
#include "../proxies/lapack_proxy.hpp"
#include "../support/error.hpp"
#include "../support/error_internal.hpp"

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
DefaultLSolver<T>::~DefaultLSolver()
{
	clear();
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::defaults()
{
	m_info = 0;
}
/*-------------------------------------------------*/
template <typename T>       int_t               DefaultLSolver<T>::info  () const { return m_info;   }
template <typename T>       T&                  DefaultLSolver<T>::factor()       { return m_factor; }
template <typename T> const T&                  DefaultLSolver<T>::factor() const { return m_factor; }
template <typename T>       std::vector<int_t>& DefaultLSolver<T>::ipiv  ()       { return m_ipiv;   }
template <typename T> const std::vector<int_t>& DefaultLSolver<T>::ipiv  () const { return m_ipiv;   }
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::clear()
{
	factor().clear();
	ipiv().clear();

	defaults();
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::check(int_t info) const
{
	if(info) {
		throw Exception(msg::lapack_error() + " info: " + std::to_string(info));
	} // ipiv
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::absorbInput(const T& mat)
{
	if(!factor().prop().isValid()) {
		factor() = mat.copy();
		return;
	} // factor not initialized

	if(factor().prop() == mat.prop() && factor().nrows() == mat.nrows() && factor().ncols() == mat.ncols()) {
		factor().setBlock(0, 0, mat);
	} else {
		factor() = mat.copy();
	} // overwrite/fresh copy
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::decompose(const T& mat)
{
	absorbInput(mat);
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::idecompose(T& mat)
{
	factor() = mat.move();
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::fdecompose()
{
	m_info = 0;

	if(factor().prop().isGeneral()) {

		ipiv().resize(std::min(factor().nrows(), factor().ncols()));
		m_info = lapack::getrf(factor().nrows(), factor().ncols(), factor().values(), factor().ld(), ipiv().data());

	} else if(factor().prop().isSymmetric()) {

		ipiv().resize(factor().ncols());
		m_info = lapack::sytrf(factor().prop().cuplo(), factor().ncols(), factor().values(), factor().ld(), ipiv().data());

	} else if(factor().prop().isHermitian()) {

		ipiv().resize(factor().ncols());
		m_info = lapack::hetrf(factor().prop().cuplo(), factor().ncols(), factor().values(), factor().ld(), ipiv().data());

	} else {

		if(factor().prop().isValid()) {
			throw InvalidOp(factor().prop().name() + " not supported for linear decomposition");
		} else {
			throw InvalidOp("Input matrix is empty");
		} // valid prop

	} // prop

	check(m_info);
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::solve(T& rhs) const
{
	int_t info = 0;

	if(factor().prop().isGeneral()) {

		info = lapack::getrs('N', factor().ncols(), rhs.ncols(), factor().values(), factor().ld(), ipiv().data(), rhs.values(), rhs.ld());

	} else if(factor().prop().isSymmetric()) {

		info = lapack::sytrs(factor().prop().cuplo(), factor().ncols(), rhs.ncols(), factor().values(), factor().ld(), ipiv().data(), rhs.values(), rhs.ld());

	} else if(factor().prop().isHermitian()) {

		info = lapack::hetrs(factor().prop().cuplo(), factor().ncols(), rhs.ncols(), factor().values(), factor().ld(), ipiv().data(), rhs.values(), rhs.ld());

	} else {

		if(factor().prop().isValid()) {
			throw InvalidOp(factor().prop().name() + " not supported for linear solution");
		} else {
			throw InvalidOp("Decomposition stage is not performed");
		} // valid prop

	} // prop

	check(info);
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
