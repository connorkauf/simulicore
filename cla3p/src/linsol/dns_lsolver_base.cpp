// this file inc
#include "dns_lsolver_base.hpp"

// system

// 3rd

// cla3p
#include "../dense.hpp"
#include "../proxies/lapack_proxy.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns { 
/*-------------------------------------------------*/
template <typename T_Matrix>
LSolverBase<T_Matrix>::LSolverBase()
{
	defaults();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
LSolverBase<T_Matrix>::~LSolverBase()
{
	clear();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverBase<T_Matrix>::defaults()
{
	info() = 0;
}
/*-------------------------------------------------*/
template <typename T_Matrix> int_t&              LSolverBase<T_Matrix>::info  (){ return m_info;   }
template <typename T_Matrix> T_Matrix&           LSolverBase<T_Matrix>::factor(){ return m_factor; }
template <typename T_Matrix> T_Matrix&           LSolverBase<T_Matrix>::buffer(){ return m_buffer; }
template <typename T_Matrix> std::vector<int_t>& LSolverBase<T_Matrix>::ipiv1 (){ return m_ipiv1;  }
template <typename T_Matrix> std::vector<int_t>& LSolverBase<T_Matrix>::jpiv1 (){ return m_jpiv1;  }
/*-------------------------------------------------*/
template <typename T_Matrix> const int_t&              LSolverBase<T_Matrix>::info  () const { return m_info;   }
template <typename T_Matrix> const T_Matrix&           LSolverBase<T_Matrix>::factor() const { return m_factor; }
template <typename T_Matrix> const T_Matrix&           LSolverBase<T_Matrix>::buffer() const { return m_buffer; }
template <typename T_Matrix> const std::vector<int_t>& LSolverBase<T_Matrix>::ipiv1 () const { return m_ipiv1;  }
template <typename T_Matrix> const std::vector<int_t>& LSolverBase<T_Matrix>::jpiv1 () const { return m_jpiv1;  }
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverBase<T_Matrix>::reserve(uint_t)
{
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverBase<T_Matrix>::clear()
{
	clearAll();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverBase<T_Matrix>::reserveBuffer(uint_t n)
{
	if(buffer().nrows() < n && buffer().ncols() < n) {
		buffer().clear();
		buffer() = T_Matrix::init(n, n);
	}
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverBase<T_Matrix>::reserveIpiv(uint_t n)
{
	ipiv1().reserve(n);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverBase<T_Matrix>::reserveJpiv(uint_t n)
{
	jpiv1().reserve(n);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverBase<T_Matrix>::absorbInput(const T_Matrix& mat)
{
	bool mat_fits_in_buffer = (buffer().nrows() >= mat.nrows() && buffer().ncols() >= mat.ncols());

	if(mat_fits_in_buffer) {

		// create a compatible factor using buffer & copy mat
		factor() = T_Matrix::wrap(mat.nrows(), mat.ncols(), buffer().values(), mat.nrows(), false, mat.prop());
		factor().setBlock(0, 0, mat);

	} else {

		factor() = mat.copy();

	} // use buffer or fresh copy
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverBase<T_Matrix>::clearAll()
{
	factor().clear();
	buffer().clear();
	ipiv1().clear();
	jpiv1().clear();

	defaults();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverBase<T_Matrix>::solve(T_Vector& rhs) const
{
	T_Matrix tmp = rhs.rmatrix();
	solve(tmp);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class LSolverBase<RdMatrix>;
template class LSolverBase<RfMatrix>;
template class LSolverBase<CdMatrix>;
template class LSolverBase<CfMatrix>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
