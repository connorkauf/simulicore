#ifndef CLA3P_DNS_XXVECTOR_HPP_
#define CLA3P_DNS_XXVECTOR_HPP_

#include "../dense/dns_xxobject.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief A dense object base class.
 */
template <typename T_Scalar, typename T_RScalar>
class XxVector : public XxObject<T_Scalar,T_RScalar> {

	public:
		XxVector();
		~XxVector();

		// no copy
		XxVector(const XxVector<T_Scalar,T_RScalar>&) = delete;
		XxVector<T_Scalar,T_RScalar>& operator=(const XxVector<T_Scalar,T_RScalar>&) = delete;

		// move
		XxVector(XxVector<T_Scalar,T_RScalar>&&) = default;
		XxVector<T_Scalar,T_RScalar>& operator=(XxVector<T_Scalar,T_RScalar>&&) = default;

		/**
		 * @brief Vector Euclidian norm.
		 * @return The Euclidian norm of the vector.
		 */
		T_RScalar normEuc() const;

};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_XXVECTOR_HPP_
