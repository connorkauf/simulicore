#ifndef CLA3P_DNS_CXVECTOR_HPP_
#define CLA3P_DNS_CXVECTOR_HPP_

#include "../types/basic_traits.hpp"
#include "../dense/dns_xxvector.hpp"
#include "../dense/dns_rxvector.hpp"

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
	using T_RVector = RxVector<T_RScalar>;

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

		/** 
		 * @name Public Member Functions
		 * @{
		 */

		/**
		 * @brief Gets a copy of the real part of the vector.
		 *
		 * @return A copy of the real part of the vector.
		 */
		T_RVector real() const;

		/**
		 * @brief Gets a copy of the imaginary part of the vector.
		 *
		 * @return A copy of the imaginary part of the vector.
		 */
		T_RVector imag() const;

		/** @} */

};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
template <typename T_Scalar> class CxMatrix;
} // namespace dns
template<typename T_Scalar>
class BasicTypeTraits<dns::CxVector<T_Scalar>> {
	public:
		static const std::string& type_name();
		using matrix_type = dns::CxMatrix<T_Scalar>;
};
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_CXVECTOR_HPP_
