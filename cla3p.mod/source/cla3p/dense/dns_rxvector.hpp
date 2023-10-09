#ifndef CLA3P_DNS_RXVECTOR_HPP_
#define CLA3P_DNS_RXVECTOR_HPP_

#include "cla3p/types/basic_traits.hpp"
#include "cla3p/dense/dns_xxvector.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

template <typename T_Scalar> class RxMatrix;

/**
 * @nosubgrouping 
 * @brief A dense real vector class.
 */
template <typename T_Scalar>
class RxVector : public XxVector<T_Scalar,RxVector<T_Scalar>> {

	public:

		// no copy
		RxVector(const RxVector<T_Scalar>&) = delete;
		RxVector<T_Scalar>& operator=(const RxVector<T_Scalar>&) = delete;

		/**
		 * @name Constructors
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::XxVector::XxVector()
		 */
		explicit RxVector();

		/**
		 * @copydoc cla3p::dns::XxVector::XxVector(uint_t n)
		 */
		explicit RxVector(uint_t n);

		/**
		 * @copydoc cla3p::dns::XxVector::XxVector(XxVector&& other)
		 */
		RxVector(RxVector<T_Scalar>&& other) = default;

		/**
		 * @copydoc cla3p::dns::XxVector::~XxVector()
		 */
		~RxVector();

		/** @} */

		/**
		 * @name Operators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::XxVector::operator=(XxVector&& other)
		 */
		RxVector<T_Scalar>& operator=(RxVector<T_Scalar>&& other) = default;

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

/*-------------------------------------------------*/
namespace cla3p { 
template<typename T_Scalar>
class BasicTypeTraits<dns::RxVector<T_Scalar>> {
	public:
		static std::string type_name();
		using real_type = dns::RxVector<T_Scalar>;
		using matrix_type = dns::RxMatrix<T_Scalar>;
};
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_RXVECTOR_HPP_