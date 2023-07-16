#ifndef CLA3P_DNS_XXOBJECT_HPP_
#define CLA3P_DNS_XXOBJECT_HPP_

#include "../generic/array2d.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief A dense object base class.
 */
template <typename T_Scalar, typename T_RScalar, typename T_ReturnType>
class XxObject : public Array2D<T_Scalar> {

	public:
		XxObject();
		~XxObject();

		// no copy
		XxObject(const XxObject<T_Scalar,T_RScalar,T_ReturnType>&) = delete;
		XxObject<T_Scalar,T_RScalar,T_ReturnType>& operator=(const XxObject<T_Scalar,T_RScalar,T_ReturnType>&) = delete;

		// move
		XxObject(XxObject<T_Scalar,T_RScalar,T_ReturnType>&&) = default;
		XxObject<T_Scalar,T_RScalar,T_ReturnType>& operator=(XxObject<T_Scalar,T_RScalar,T_ReturnType>&&) = default;

		/**
		 * @brief Scales matrix by coeff.
		 * @param[in] val The scaling coefficient.
		 */
		virtual void scale(T_Scalar val);

		/**
		 * @brief Matrix 1-norm.
		 * @return The 1-norm of the matrix.
		 */
		virtual T_RScalar normOne() const;

		/**
		 * @brief Matrix infinite norm.
		 * @return The infinite norm of the matrix.
		 */
		virtual T_RScalar normInf() const;

		/**
		 * @brief Matrix max norm.
		 * @return The maximum norm of the matrix.
		 */
		virtual T_RScalar normMax() const;

		/**
		 * @brief Matrix Frobenius norm.
		 * @return The Frobenius norm of the matrix.
		 */
		virtual T_RScalar normFro() const;

};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_XXOBJECT_HPP_
