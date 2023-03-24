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
template <typename T>
LSolverBase<T>::LSolverBase()
{
	defaults();
}
/*-------------------------------------------------*/
template <typename T>
LSolverBase<T>::~LSolverBase()
{
	clearAll();
}
/*-------------------------------------------------*/
template <typename T>
void LSolverBase<T>::defaults()
{
	info() = 0;
}
/*-------------------------------------------------*/
template <typename T> int_t&              LSolverBase<T>::info  (){ return m_info;   }
template <typename T> T&                  LSolverBase<T>::factor(){ return m_factor; }
template <typename T> T&                  LSolverBase<T>::buffer(){ return m_buffer; }
template <typename T> std::vector<int_t>& LSolverBase<T>::ipiv1 (){ return m_ipiv1;  }
template <typename T> std::vector<int_t>& LSolverBase<T>::jpiv1 (){ return m_jpiv1;  }
/*-------------------------------------------------*/
template <typename T> const int_t&              LSolverBase<T>::info  () const { return m_info;   }
template <typename T> const T&                  LSolverBase<T>::factor() const { return m_factor; }
template <typename T> const T&                  LSolverBase<T>::buffer() const { return m_buffer; }
template <typename T> const std::vector<int_t>& LSolverBase<T>::ipiv1 () const { return m_ipiv1;  }
template <typename T> const std::vector<int_t>& LSolverBase<T>::jpiv1 () const { return m_jpiv1;  }
/*-------------------------------------------------*/
template <typename T>
void LSolverBase<T>::reserveBuffer(uint_t n)
{
	if(buffer().nrows() < n && buffer().ncols() < n) {
		buffer().clear();
		buffer() = T::init(n, n);
	}
}
/*-------------------------------------------------*/
template <typename T>
void LSolverBase<T>::reserveIpiv(uint_t n)
{
	ipiv1().reserve(n);
}
/*-------------------------------------------------*/
template <typename T>
void LSolverBase<T>::reserveJpiv(uint_t n)
{
	jpiv1().reserve(n);
}
/*-------------------------------------------------*/
template <typename T>
void LSolverBase<T>::absorbInput(const T& mat)
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
void LSolverBase<T>::clearAll()
{
	factor().clear();
	buffer().clear();
	ipiv1().clear();
	jpiv1().clear();

	defaults();
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
