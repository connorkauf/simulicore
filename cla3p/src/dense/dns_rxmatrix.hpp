#ifndef CLA3P_DNS_RXMATRIX_HPP_
#define CLA3P_DNS_RXMATRIX_HPP_

#include "../dense/dns_xxmatrix.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief A dense real vector class.
 */
template <typename T_Scalar>
class RxMatrix : public XxMatrix<T_Scalar,RxMatrix<T_Scalar>> {

	public:

		// no copy
		RxMatrix(const RxMatrix<T_Scalar>&) = delete;
		RxMatrix<T_Scalar>& operator=(const RxMatrix<T_Scalar>&) = delete;

		/**
		 * @name Constructors
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::XxMatrix::XxMatrix()
		 */
		explicit RxMatrix();

		/**
		 * @copydoc cla3p::dns::XxMatrix::XxMatrix(uint_t nr, uint_t nc, const Property& pr)
		 */
		explicit RxMatrix(uint_t nr, uint_t nc, const Property& pr = defaultProperty());

		/**
		 * @copydoc cla3p::dns::XxMatrix::XxMatrix(XxMatrix&& other)
		 */
		RxMatrix(RxMatrix<T_Scalar>&& other) = default;

		/**
		 * @copydoc cla3p::dns::XxMatrix::~XxMatrix()
		 */
		~RxMatrix();

		/** @} */

		/**
		 * @name Operators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::XxMatrix::operator=(XxMatrix&& other)
		 */
		RxMatrix<T_Scalar>& operator=(RxMatrix<T_Scalar>&& other) = default;

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
} // namespace dns

template<typename T_Scalar>
class BasicTypeTraits<dns::RxMatrix<T_Scalar>> {
  public:
    using element_type = T_Scalar;
    using equivalent_vector = dns::RxVector<T_Scalar>;
    using equivalent_matrix = dns::RxMatrix<T_Scalar>;
    using equivalent_real_vector = dns::RxVector<T_Scalar>;
    using equivalent_real_matrix = dns::RxMatrix<T_Scalar>;
};

} // namespace cla3p

#endif // CLA3P_DNS_RXMATRIX_HPP_
