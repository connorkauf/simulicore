#ifndef CLA3P_DNS_CXMATRIX_HPP_
#define CLA3P_DNS_CXMATRIX_HPP_

#include "../dense/dns_xxmatrix.hpp"
#include "../types/basic_traits.hpp"

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

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template<typename T_Scalar>
class BasicTypeTraits<dns::CxMatrix<T_Scalar>> {
	public:
		static const std::string& type_name();
};
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_CXMATRIX_HPP_
