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
	clear_privately();
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::defaults()
{
	reset_info();
	reset_decomp_flg();
}
/*-------------------------------------------------*/
template <typename T>       int_t               DefaultLSolver<T>::info  () const { return m_info;   }
template <typename T>       T&                  DefaultLSolver<T>::factor()       { return m_factor; }
template <typename T> const T&                  DefaultLSolver<T>::factor() const { return m_factor; }
template <typename T>       std::vector<int_t>& DefaultLSolver<T>::ipiv1 ()       { return m_ipiv1;  }
template <typename T> const std::vector<int_t>& DefaultLSolver<T>::ipiv1 () const { return m_ipiv1;  }
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::clear_privately()
{
	factor().clear();
	ipiv1().clear();

	defaults();
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::reset_info()
{
	m_info = 0;
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::reset_decomp_flg()
{
	m_decomp_success = false;
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::update_decomp_flg()
{
	if(!info()) {
		m_decomp_success = true;
	} // info successful
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::check_decomp_info() const
{
	if(info()) {
		throw Exception(msg::lapack_error() + " info: " + std::to_string(info()));
	} // info
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::check_decomp_input(const T& mat) const
{
	bool supported_prop = (mat.prop().isGeneral() || mat.prop().isSymmetric() || mat.prop().isHermitian());

	if(mat.empty()) {
		throw InvalidOp("Input matrix is empty");
	} else if(!supported_prop) {
		throw InvalidOp(mat.prop().name() + " not supported for linear decomposition");
	} // valid prop
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::check_solve_input(const T& rhs) const
{
	if(!factor().prop().isValid()) {
		throw InvalidOp("Decomposition stage is not performed");
	} // valid prop

	bool supported_prop = rhs.prop().isGeneral();

	if(rhs.empty()) {
		throw InvalidOp("Input rhs matrix is empty");
	} else if(!supported_prop) {
		throw InvalidOp(rhs.prop().name() + " not supported for rhs in linear solution stage");
	} // valid prop
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::absorbInput(const T& mat)
{
	bool mat_fits_in_factor = (
			factor().prop()  == mat.prop()  && 
			factor().nrows() == mat.nrows() && 
			factor().ncols() == mat.ncols() );

	if(mat_fits_in_factor) {
		factor().setBlock(0, 0, mat);
	} else {
		factor() = mat.copy();
	} // overwrite/fresh copy
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::fdecompose()
{
	if(factor().prop().isGeneral()) {

		ipiv1().resize(std::min(factor().nrows(), factor().ncols()));
		m_info = lapack::getrf(factor().nrows(), factor().ncols(), factor().values(), factor().ld(), ipiv1().data());
		update_decomp_flg();

	} else if(factor().prop().isSymmetric()) {

		ipiv1().resize(factor().ncols());
		m_info = lapack::sytrf(factor().prop().cuplo(), factor().ncols(), factor().values(), factor().ld(), ipiv1().data());
		update_decomp_flg();

	} else if(factor().prop().isHermitian()) {

		ipiv1().resize(factor().ncols());
		m_info = lapack::hetrf(factor().prop().cuplo(), factor().ncols(), factor().values(), factor().ld(), ipiv1().data());
		update_decomp_flg();

	} else {

		throw Exception("Unreachable");

	} // prop

	check_decomp_info();
}
/*-------------------------------------------------*/
/*----------------   VIRTUALS   -------------------*/
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::clear()
{
	clear_privately();
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::decompose(const T& mat)
{
	reset_info();
	reset_decomp_flg();
	check_decomp_input(mat);
	absorbInput(mat);
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::idecompose(T& mat)
{
	reset_info();
	reset_decomp_flg();
	check_decomp_input(mat);
	factor() = mat.move();
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T>
void DefaultLSolver<T>::solve(T& rhs) const
{
	check_solve_input(rhs);

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

	if(info) {
		throw Exception("info: " + std::to_string(info));
	}
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
