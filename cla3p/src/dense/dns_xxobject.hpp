#ifndef CLA3P_DNS_XXOBJECT_HPP_
#define CLA3P_DNS_XXOBJECT_HPP_

#include "../generic/array2d.hpp"
#include "../generic/guard.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief A dense object class.
 */
template <typename T_Scalar, typename T_RScalar, typename T_ReturnType>
class XxObject : public Array2D<T_Scalar> {

	public:
		explicit XxObject();
		explicit XxObject(uint_t nr, uint_t nc, uint_t nl, const Property& pr);
		~XxObject();

		// no copy
		XxObject(const XxObject<T_Scalar,T_RScalar,T_ReturnType>&) = delete;
		XxObject<T_Scalar,T_RScalar,T_ReturnType>& operator=(const XxObject<T_Scalar,T_RScalar,T_ReturnType>&) = delete;

		// move
		XxObject(XxObject<T_Scalar,T_RScalar,T_ReturnType>&& other) = default;
		XxObject<T_Scalar,T_RScalar,T_ReturnType>& operator=(XxObject<T_Scalar,T_RScalar,T_ReturnType>&& other) = default;

		/** 
		 * @name Public Member Functions
		 * @{
		 */

		/**
		 * @brief Copies an object.
		 * @return A deep copy of the object.
		 */
		T_ReturnType copy() const;

		/**
		 * @brief Shallow-copies an object.
		 * @return A shallow copy of the object, original object is unchanged.
		 */
		T_ReturnType rcopy();

		/**
		 * @brief Shallow-copies an object.
		 * @return A guard of the object.
		 */
		Guard<T_ReturnType> rcopy() const;

		/**
		 * @brief Moves an object.
		 * @return A shallow copy of the object, original object is destroyed.
		 */
		T_ReturnType move();

		/**
		 * @brief Scales the object by coeff.
		 * @param[in] val The scaling coefficient.
		 */
		void scale(T_Scalar val);

		/**
		 * @brief The 1-norm.
		 * @return The 1-norm of the object.
		 */
		T_RScalar normOne() const;

		/**
		 * @brief The infinite norm.
		 * @return The infinite norm of the object.
		 */
		T_RScalar normInf() const;

		/** @} */

	protected:
		void getBlockCopy(XxObject<T_Scalar,T_RScalar,T_ReturnType>&, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;
		void getBlockReference(XxObject<T_Scalar,T_RScalar,T_ReturnType>&, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);
		void setBlockCopy(const XxObject<T_Scalar,T_RScalar,T_ReturnType>&, uint_t ibgn, uint_t jbgn);

};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup stream_operators
 * @brief Writes to os the contents of obj.
 */
template <typename T_Scalar, typename T_RScalar, typename T_ReturnType>
std::ostream& operator<<(std::ostream& os, const cla3p::dns::XxObject<T_Scalar,T_RScalar,T_ReturnType>& obj)
{
  os << obj.toString();
  return os;
}

#endif // CLA3P_DNS_XXOBJECT_HPP_
