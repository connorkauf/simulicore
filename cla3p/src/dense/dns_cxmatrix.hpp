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
template <typename T_Scalar>
class CxMatrix : public XxMatrix<T_Scalar,CxMatrix<T_Scalar>> {

	public:

		// no copy
		CxMatrix(const CxMatrix<T_Scalar>&) = delete;
		CxMatrix<T_Scalar>& operator=(const CxMatrix<T_Scalar>&) = delete;

		/**
		 * @name Constructors
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::XxMatrix::XxMatrix()
		 */
		explicit CxMatrix();

		/**
		 * @copydoc cla3p::dns::XxMatrix::XxMatrix(uint_t nr, uint_t nc, const Property& pr)
		 */
		explicit CxMatrix(uint_t nr, uint_t nc, const Property& pr = defaultProperty());

		/**
		 * @copydoc cla3p::dns::XxMatrix::XxMatrix(XxMatrix&& other)
		 */
		CxMatrix(CxMatrix<T_Scalar>&& other) = default;

		/**
		 * @copydoc cla3p::dns::XxMatrix::~XxMatrix()
		 */
		~CxMatrix();

		/** @} */

		/**
		 * @name Operators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::XxMatrix::operator=(XxMatrix&& other)
		 */
		CxMatrix<T_Scalar>& operator=(CxMatrix<T_Scalar>&& other) = default;

		/**
		 * @copydoc cla3p::dns::XxMatrix::operator=(T_Scalar val)
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
template <typename T_Scalar> class CxVector;
template <typename T_Scalar> class RxMatrix;
} // namespace dns

template<typename T_Scalar>
class BasicTypeTraits<dns::CxMatrix<T_Scalar>> {
  public:
    using element_type = T_Scalar;
    using equivalent_vector = dns::CxVector<T_Scalar>;
    using equivalent_matrix = dns::CxMatrix<T_Scalar>;
    using equivalent_real_vector = dns::RxVector<typename BasicTypeTraits<T_Scalar>::real_type>;
    using equivalent_real_matrix = dns::RxMatrix<typename BasicTypeTraits<T_Scalar>::real_type>;
};

} // namespace cla3p

#endif // CLA3P_DNS_CXMATRIX_HPP_
