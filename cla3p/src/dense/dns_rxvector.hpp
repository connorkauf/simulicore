#ifndef CLA3P_DNS_RXVECTOR_HPP_
#define CLA3P_DNS_RXVECTOR_HPP_

#include "../dense/dns_xxvector.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief A dense real vector class.
 */
template <typename T_Scalar>
class RxVector : public XxVector<T_Scalar,T_Scalar,RxVector<T_Scalar>> {

	public:
		RxVector();
		~RxVector();

		// no copy
		RxVector(const RxVector<T_Scalar>&) = delete;
		RxVector<T_Scalar>& operator=(const RxVector<T_Scalar>&) = delete;

		// move
		RxVector(RxVector<T_Scalar>&&) = default;
		RxVector<T_Scalar>& operator=(RxVector<T_Scalar>&&) = default;

};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_RXVECTOR_HPP_
