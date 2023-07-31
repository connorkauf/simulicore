// this file inc
#include "dns_lu_lsolver.hpp"

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
LSolverLU<T_Matrix>::LSolverLU()
{
}
/*-------------------------------------------------*/
template <typename T_Matrix>
LSolverLU<T_Matrix>::LSolverLU(uint_t n)
{
	reserve(n);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
LSolverLU<T_Matrix>::~LSolverLU()
{
	this->clear();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverLU<T_Matrix>::reserve(uint_t n)
{
	this->reserveBuffer(n);
	this->reserveIpiv(n);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverLU<T_Matrix>::decompose(const T_Matrix& mat)
{
	this->factor().clear();
	lu_decomp_input_check(mat);
	this->absorbInput(mat);
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverLU<T_Matrix>::idecompose(T_Matrix& mat)
{
	this->factor().clear();
	lu_decomp_input_check(mat);
	this->factor() = mat.move();
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverLU<T_Matrix>::solve(T_Matrix& rhs) const
{
	if(this->factor().empty()) {
		throw InvalidOp("Decomposition stage is not performed");
	} // empty factor

	default_solve_input_check(this->factor().ncols(), rhs);

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

	} else {

		throw Exception("Unreachable");

	} // prop

	lapack_info_check(info);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverLU<T_Matrix>::fdecompose()
{
	this->factor().igeneral();

	if(this->factor().prop().isGeneral()) {

		this->ipiv1().resize(std::min(this->factor().nrows(), this->factor().ncols()));

		this->info() = lapack::getrf(
				this->factor().nrows(),
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
template class LSolverLU<RdMatrix>;
template class LSolverLU<RfMatrix>;
template class LSolverLU<CdMatrix>;
template class LSolverLU<CfMatrix>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

