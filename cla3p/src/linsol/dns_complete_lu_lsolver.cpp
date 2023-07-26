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
template <typename T_Matrix>
LSolverCompleteLU<T_Matrix>::LSolverCompleteLU()
{
}
/*-------------------------------------------------*/
template <typename T_Matrix>
LSolverCompleteLU<T_Matrix>::LSolverCompleteLU(uint_t n)
{
	reserve(n);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
LSolverCompleteLU<T_Matrix>::~LSolverCompleteLU()
{
	this->clear();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverCompleteLU<T_Matrix>::reserve(uint_t n)
{
	this->reserveBuffer(n);
	this->reserveIpiv(n);
	this->reserveJpiv(n);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverCompleteLU<T_Matrix>::decompose(const T_Matrix& mat)
{
	this->factor().clear();
	lu_decomp_input_check(mat);
	this->absorbInput(mat);
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverCompleteLU<T_Matrix>::idecompose(T_Matrix& mat)
{
	this->factor().clear();
	lu_decomp_input_check(mat);
	this->factor() = mat.move();
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverCompleteLU<T_Matrix>::solve(T_Matrix& rhs) const
{
	if(this->factor().empty()) {
		throw InvalidOp("Decomposition stage is not performed");
	} // empty factor

	default_solve_input_check(this->factor().ncols(), rhs);

	if(this->factor().prop().isGeneral()) {

		uint_t nrhs = rhs.ncols();
		T_Matrix scale(nrhs, 1);

		for(uint_t k = 0; k < rhs.ncols(); k++) {

			auto scale_k = getRe(scale(k,0));
			T_Matrix rhs_k = rhs.rblock(0, k, rhs.nrows(), 1); // TODO: replace with column functionality when implemented

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
template <typename T_Matrix>
void LSolverCompleteLU<T_Matrix>::fdecompose()
{
	//this->factor().igeneral();

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

