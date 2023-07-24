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

	public:

		// no copy
		CxMatrix(const CxMatrix<T_Scalar,T_RScalar>&) = delete;
		CxMatrix<T_Scalar,T_RScalar>& operator=(const CxMatrix<T_Scalar,T_RScalar>&) = delete;

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
		CxMatrix(CxMatrix<T_Scalar,T_RScalar>&& other);

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
		CxMatrix<T_Scalar,T_RScalar>& operator=(CxMatrix<T_Scalar,T_RScalar>&&);

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

#endif // CLA3P_DNS_CXMATRIX_HPP_
