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
template <typename T_Scalar>
class CxVector : public XxVector<T_Scalar,CxVector<T_Scalar>> {

	using T_RScalar = typename BasicTypeTraits<T_Scalar>::real_type;

	public:

		// no copy
		CxVector(const CxVector<T_Scalar>&) = delete;
		CxVector<T_Scalar>& operator=(const CxVector<T_Scalar>&) = delete;

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
		CxVector(CxVector<T_Scalar>&& other) = default;

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
		CxVector<T_Scalar>& operator=(CxVector<T_Scalar>&& other) = default;

		/**
		 * @copydoc cla3p::dns::XxVector::operator=(T_Scalar val)
		 */
		void operator=(T_Scalar val);

		/** @} */

};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

namespace cla3p { 

namespace dns {
template <typename T_Scalar> class RxVector;
template <typename T_Scalar> class RxMatrix;
template <typename T_Scalar> class CxMatrix;
} // namespace dns

template<typename T_Scalar>
class BasicTypeTraits<dns::CxVector<T_Scalar>> {
  public:
    using element_type = T_Scalar;
    using equivalent_vector = dns::CxVector<T_Scalar>;
    using equivalent_matrix = dns::CxMatrix<T_Scalar>;
    using equivalent_real_vector = dns::RxVector<typename BasicTypeTraits<T_Scalar>::real_type>;
    using equivalent_real_matrix = dns::RxMatrix<typename BasicTypeTraits<T_Scalar>::real_type>;
};

} // namespace cla3p

#endif // CLA3P_DNS_CXVECTOR_HPP_
