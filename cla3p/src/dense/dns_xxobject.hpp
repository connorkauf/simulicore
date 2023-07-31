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
template <typename T_Scalar, typename T_Object>
class XxObject : public Array2D<T_Scalar> {
	
	using T_RScalar = typename BasicTypeTraits<T_Scalar>::real_type;

	public:
		explicit XxObject();
		explicit XxObject(uint_t nr, uint_t nc, uint_t nl, const Property& pr);
		~XxObject();

		// no copy
		XxObject(const XxObject<T_Scalar,T_Object>&) = delete;
		XxObject<T_Scalar,T_Object>& operator=(const XxObject<T_Scalar,T_Object>&) = delete;

		// move
		XxObject(XxObject<T_Scalar,T_Object>&& other) = default;
		XxObject<T_Scalar,T_Object>& operator=(XxObject<T_Scalar,T_Object>&& other) = default;

		/** 
		 * @name Operators
		 * @{
		 */

		/**
		 * @brief Add operator.
		 *
		 * Adds two compatible objects.
		 *
		 * @return The result of the operation *this + other.
		 */
		T_Object operator+(const XxObject<T_Scalar,T_Object>& other);

		/**
		 * @brief Subtract operator.
		 *
		 * Subtracts two compatible objects.
		 *
		 * @return The result of the operation *this - other.
		 */
		T_Object operator-(const XxObject<T_Scalar,T_Object>& other);

		/**
		 * @brief Update operator.
		 *
		 * Adds other to *this.
		 */
		XxObject<T_Scalar,T_Object>& operator+=(const XxObject<T_Scalar,T_Object>& other);

		/**
		 * @brief Update operator.
		 *  
		 * Subtracts other from *this.
		 */
		XxObject<T_Scalar,T_Object>& operator-=(const XxObject<T_Scalar,T_Object>& other);

		/**
		 * @brief Update operator.
		 * @param[in] val The scaling coefficient.
		 *  
		 * Scales *this by val.
		 */
		XxObject<T_Scalar,T_Object>& operator*=(T_Scalar val);

		/**
		 * @brief Update operator.
		 * @param[in] val The scaling coefficient.
		 *  
		 * Scales *this by 1/val.
		 */
		XxObject<T_Scalar,T_Object>& operator/=(T_Scalar val);

		/** @} */

		/** 
		 * @name Public Member Functions
		 * @{
		 */

		/**
		 * @brief Copies an object.
		 * @return A deep copy of the object.
		 */
		T_Object copy() const;

		/**
		 * @brief Shallow-copies an object.
		 * @return A shallow copy of the object, original object is unchanged.
		 */
		T_Object rcopy();

		/**
		 * @brief Shallow-copies an object.
		 * @return A guard of the object.
		 */
		Guard<T_Object> rcopy() const;

		/**
		 * @brief Moves an object.
		 * @return A shallow copy of the object, original object is destroyed.
		 */
		T_Object move();

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
		T_Object getBlockCopy(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;
		T_Object getBlockReference(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);
		Guard<T_Object> getBlockReference(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;
		void setBlockCopy(const XxObject<T_Scalar,T_Object>&, uint_t ibgn, uint_t jbgn);

	public:
		void updateSelfWithScaledOther(T_Scalar alpha, const XxObject<T_Scalar,T_Object>& other);
		void createFromScaledSum(
				T_Scalar alpha, const XxObject<T_Scalar,T_Object>& otherA, 
				T_Scalar beta, const XxObject<T_Scalar,T_Object>& otherB);

};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup stream_operators
 * @brief Writes to os the contents of obj.
 */
template <typename T_Scalar, typename T_Object>
std::ostream& operator<<(std::ostream& os, const cla3p::dns::XxObject<T_Scalar,T_Object>& obj)
{
  os << obj.toString();
  return os;
}

#endif // CLA3P_DNS_XXOBJECT_HPP_
