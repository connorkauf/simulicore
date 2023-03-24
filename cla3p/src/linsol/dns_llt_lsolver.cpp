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
LSolverLLt<T>::LSolverLLt()
{
}
/*-------------------------------------------------*/
template <typename T>
LSolverLLt<T>::LSolverLLt(uint_t n)
{
	reserve(n);
}
/*-------------------------------------------------*/
template <typename T>
LSolverLLt<T>::~LSolverLLt()
{
	this->clear();
}
/*-------------------------------------------------*/
template <typename T>
void LSolverLLt<T>::reserve(uint_t n)
{
	this->reserveBuffer(n);
}
/*-------------------------------------------------*/
template <typename T>
void LSolverLLt<T>::decompose(const T& mat)
{
	this->factor().clear();
	llt_decomp_input_check(mat);
	this->absorbInput(mat);
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T>
void LSolverLLt<T>::idecompose(T& mat)
{
	this->factor().clear();
	llt_decomp_input_check(mat);
	this->factor() = mat.move();
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T>
void LSolverLLt<T>::solve(T& rhs) const
{
	default_solve_input_check(rhs);
	
	if(this->factor().empty()) {
		throw InvalidOp("Decomposition stage is not performed");
	} // empty factor
	
	int_t info = lapack::potrs(
			this->factor().prop().cuplo(), 
			this->factor().ncols(), 
			rhs.ncols(), 
			this->factor().values(), 
			this->factor().ld(), rhs.values(), rhs.ld());
	
	lapack_info_check(info);
}
/*-------------------------------------------------*/
template <typename T>
void LSolverLLt<T>::fdecompose()
{
	this->info() = lapack::potrf(
			this->factor().prop().cuplo(), 
			this->factor().ncols(), 
			this->factor().values(), 
			this->factor().ld());
	
	lapack_info_check(this->info());
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class LSolverLLt<RdMatrix>;
template class LSolverLLt<RfMatrix>;
template class LSolverLLt<CdMatrix>;
template class LSolverLLt<CfMatrix>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

