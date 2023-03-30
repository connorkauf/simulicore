// this file inc
#include "dns_complete_lu_lsolver.hpp"

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
LSolverCompleteLU<T>::LSolverCompleteLU()
{
}
/*-------------------------------------------------*/
template <typename T>
LSolverCompleteLU<T>::LSolverCompleteLU(uint_t n)
{
	reserve(n);
}
/*-------------------------------------------------*/
template <typename T>
LSolverCompleteLU<T>::~LSolverCompleteLU()
{
	this->clear();
}
/*-------------------------------------------------*/
template <typename T>
void LSolverCompleteLU<T>::reserve(uint_t n)
{
	this->reserveBuffer(n);
	this->reserveIpiv(n);
	this->reserveJpiv(n);
}
/*-------------------------------------------------*/
template <typename T>
void LSolverCompleteLU<T>::decompose(const T& mat)
{
	this->factor().clear();
	lu_decomp_input_check(mat);
	this->absorbInput(mat);
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T>
void LSolverCompleteLU<T>::idecompose(T& mat)
{
	this->factor().clear();
	lu_decomp_input_check(mat);
	this->factor() = mat.move();
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T>
void LSolverCompleteLU<T>::solve(T& rhs) const
{
	if(this->factor().empty()) {
		throw InvalidOp("Decomposition stage is not performed");
	} // empty factor

	default_solve_input_check(this->factor().ncols(), rhs);

	if(this->factor().prop().isGeneral()) {

		uint_t nrhs = rhs.ncols();
		T scale(nrhs, 1);

		for(uint_t k = 0; k < rhs.ncols(); k++) {

			auto scale_k = getRe(scale(k,0));
			T rhs_k = rhs.rblock(0, k, rhs.nrows(), 1); // TODO: replace with column functionality when implemented

			int_t info = lapack::gesc2(
					this->factor().ncols(),
					this->factor().values(),
					this->factor().ld(),
					rhs_k.values(),
					this->ipiv1().data(),
					this->jpiv1().data(),
					&scale_k);

			scale(k,0) = scale_k;

			// should I also scale here ???

			lapack_info_check(info);

		} // k

	} else {

		throw Exception("Unreachable");

	} // prop
}
/*-------------------------------------------------*/
template <typename T>
void LSolverCompleteLU<T>::fdecompose()
{
	this->factor().igeneral();

	if(this->factor().prop().isGeneral()) {

		this->ipiv1().resize(std::min(this->factor().nrows(), this->factor().ncols()));
		this->jpiv1().resize(std::min(this->factor().nrows(), this->factor().ncols()));

		this->info() = lapack::getc2(
				this->factor().ncols(),
				this->factor().values(),
				this->factor().ld(),
				this->ipiv1().data(),
				this->jpiv1().data());

	} else {

		throw Exception("Unreachable");

	} // prop

	lapack_info_check(this->info());
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class LSolverCompleteLU<RdMatrix>;
template class LSolverCompleteLU<RfMatrix>;
template class LSolverCompleteLU<CdMatrix>;
template class LSolverCompleteLU<CfMatrix>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

