#ifndef CLA3P_DNS_CXMATRIX_HPP_
#define CLA3P_DNS_CXMATRIX_HPP_

#include "../dense/dns_xxmatrix.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief A dense complex vector class.
 */
template <typename T_Scalar, typename T_RScalar>
class CxMatrix : public XxMatrix<T_Scalar,T_RScalar,CxMatrix<T_Scalar,T_RScalar>> {

#if 0

	public:

		// no copy
		CxVector(const CxVector<T_Scalar,T_RScalar>&) = delete;
		CxVector<T_Scalar,T_RScalar>& operator=(const CxVector<T_Scalar,T_RScalar>&) = delete;

		/**
		 * @name Constructors
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::XxVector::XxVector()
		 */
		explicit CxVector();

		/**
		 * @copydoc cla3p::dns::XxVector::XxVector(uint_t n)
		 */
		explicit CxVector(uint_t n);

		/**
		 * @copydoc cla3p::dns::XxVector::XxVector(XxVector&& other)
		 */
		CxVector(CxVector<T_Scalar,T_RScalar>&&) = default;

		/**
		 * @copydoc cla3p::dns::XxVector::~XxVector()
		 */
		~CxVector();

		/** @} */

		/**
		 * @name Operators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::XxVector::operator=(XxVector&& other)
		 */
		CxVector<T_Scalar,T_RScalar>& operator=(CxVector<T_Scalar,T_RScalar>&&) = default;

		/**
		 * @copydoc cla3p::dns::XxVector::operator=(T_Scalar val)
		 */
		void operator=(T_Scalar val);

		/** @} */

#endif // 0

};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_CXMATRIX_HPP_
