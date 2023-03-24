// this file inc
#include "dns_auto_lsolver.hpp"

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
LSolverAuto<T>::LSolverAuto()
{
}
/*-------------------------------------------------*/
template <typename T>
LSolverAuto<T>::LSolverAuto(uint_t n)
{
	reserve(n);
}
/*-------------------------------------------------*/
template <typename T>
LSolverAuto<T>::~LSolverAuto()
{
	this->clear();
}
/*-------------------------------------------------*/
template <typename T>
void LSolverAuto<T>::reserve(uint_t n)
{
	this->reserveBuffer(n);
	this->reserveIpiv(n);
}
/*-------------------------------------------------*/
template <typename T>
void LSolverAuto<T>::decompose(const T& mat)
{
	this->factor().clear();
	default_decomp_input_check(mat);
	this->absorbInput(mat);
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T>
void LSolverAuto<T>::idecompose(T& mat)
{
	this->factor().clear();
	default_decomp_input_check(mat);
	this->factor() = mat.move();
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T>
void LSolverAuto<T>::solve(T& rhs) const
{
	default_solve_input_check(rhs);

	if(this->factor().empty()) {
		throw InvalidOp("Decomposition stage is not performed");
	} // empty factor

	int_t info = 0;

	if(this->factor().prop().isGeneral()) {

		info = lapack::getrs('N', 
				this->factor().ncols(), 
				rhs.ncols(), 
				this->factor().values(), 
				this->factor().ld(), 
				this->ipiv1().data(), 
				rhs.values(), 
				rhs.ld());

	} else if(this->factor().prop().isSymmetric()) {

		info = lapack::sytrs(
				this->factor().prop().cuplo(), 
				this->factor().ncols(), 
				rhs.ncols(), 
				this->factor().values(), 
				this->factor().ld(), 
				this->ipiv1().data(), 
				rhs.values(), 
				rhs.ld());

	} else if(this->factor().prop().isHermitian()) {

		info = lapack::hetrs(
				this->factor().prop().cuplo(), 
				this->factor().ncols(), 
				rhs.ncols(), 
				this->factor().values(), 
				this->factor().ld(), 
				this->ipiv1().data(), 
				rhs.values(), 
				rhs.ld());

	} else {

		throw Exception("Unreachable");

	} // prop

	lapack_info_check(info);
}
/*-------------------------------------------------*/
template <typename T>
void LSolverAuto<T>::fdecompose()
{
	if(this->factor().prop().isGeneral()) {

		this->ipiv1().resize(std::min(this->factor().nrows(), this->factor().ncols()));

		this->info() = lapack::getrf(
				this->factor().nrows(), 
				this->factor().ncols(), 
				this->factor().values(), 
				this->factor().ld(), 
				this->ipiv1().data());

	} else if(this->factor().prop().isSymmetric()) {

		this->ipiv1().resize(this->factor().ncols());

		this->info() = lapack::sytrf(
				this->factor().prop().cuplo(), 
				this->factor().ncols(), 
				this->factor().values(), 
				this->factor().ld(), 
				this->ipiv1().data());

	} else if(this->factor().prop().isHermitian()) {

		this->ipiv1().resize(this->factor().ncols());

		this->info() = lapack::hetrf(
				this->factor().prop().cuplo(), 
				this->factor().ncols(), 
				this->factor().values(), 
				this->factor().ld(), 
				this->ipiv1().data());

	} else {

		throw Exception("Unreachable");

	} // prop

	lapack_info_check(this->info());
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class LSolverAuto<RdMatrix>;
template class LSolverAuto<RfMatrix>;
template class LSolverAuto<CdMatrix>;
template class LSolverAuto<CfMatrix>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
