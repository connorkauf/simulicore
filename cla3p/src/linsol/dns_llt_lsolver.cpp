// this file inc
#include "dns_llt_lsolver.hpp"

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
SpdCholesky<T>::SpdCholesky()
{
}
/*-------------------------------------------------*/
template <typename T>
SpdCholesky<T>::SpdCholesky(uint_t n)
	: DefaultLSolver<T>(n)
{
}
/*-------------------------------------------------*/
template <typename T>
SpdCholesky<T>::~SpdCholesky()
{
	DefaultLSolver<T>::clear();
}
/*-------------------------------------------------*/
template <typename T>
void SpdCholesky<T>::decompose(const T& mat)
{
	DefaultLSolver<T>::factor().clear();
	llt_decomp_input_check(mat);
	DefaultLSolver<T>::absorbInput(mat);
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T>
void SpdCholesky<T>::idecompose(T& mat)
{
	DefaultLSolver<T>::factor().clear();
	llt_decomp_input_check(mat);
	DefaultLSolver<T>::factor() = mat.move();
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T>
void SpdCholesky<T>::solve(T& rhs) const
{
	default_solve_input_check(rhs);

	if(DefaultLSolver<T>::factor().empty()) {
		throw InvalidOp("Decomposition stage is not performed");
	} // empty factor
	
	int_t info = lapack::potrs(
			DefaultLSolver<T>::factor().prop().cuplo(), 
			DefaultLSolver<T>::factor().ncols(), 
			rhs.ncols(), 
			DefaultLSolver<T>::factor().values(), 
			DefaultLSolver<T>::factor().ld(), rhs.values(), rhs.ld());
	
	lapack_info_check(info);
}
/*-------------------------------------------------*/
template <typename T>
void SpdCholesky<T>::fdecompose()
{
	DefaultLSolver<T>::info() = lapack::potrf(
			DefaultLSolver<T>::factor().prop().cuplo(), 
			DefaultLSolver<T>::factor().ncols(), 
			DefaultLSolver<T>::factor().values(), 
			DefaultLSolver<T>::factor().ld());

	lapack_info_check(DefaultLSolver<T>::info());
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class SpdCholesky<RdMatrix>;
template class SpdCholesky<RfMatrix>;
template class SpdCholesky<CdMatrix>;
template class SpdCholesky<CfMatrix>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

