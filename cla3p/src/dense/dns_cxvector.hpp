#ifndef CLA3P_DNS_CXVECTOR_HPP_
#define CLA3P_DNS_CXVECTOR_HPP_

#include "../dense/dns_xxvector.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief A dense complex vector class.
 */
template <typename T_Scalar, typename T_RScalar>
class CxVector : public XxVector<T_Scalar,T_RScalar,CxVector<T_Scalar,T_RScalar>> {

	public:
		CxVector();
		~CxVector();

		// no copy
		CxVector(const CxVector<T_Scalar,T_RScalar>&) = delete;
		CxVector<T_Scalar,T_RScalar>& operator=(const CxVector<T_Scalar,T_RScalar>&) = delete;

		// move
		CxVector(CxVector<T_Scalar,T_RScalar>&&) = default;
		CxVector<T_Scalar,T_RScalar>& operator=(CxVector<T_Scalar,T_RScalar>&&) = default;

};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_CXVECTOR_HPP_
