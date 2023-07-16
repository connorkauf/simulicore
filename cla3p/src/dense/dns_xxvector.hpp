#ifndef CLA3P_DNS_XXVECTOR_HPP_
#define CLA3P_DNS_XXVECTOR_HPP_

#include "../dense/dns_xxobject.hpp"
#include "../generic/guard.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief A dense vector class.
 */
template <typename T_Scalar, typename T_RScalar, typename T_ReturnType>
class XxVector : public XxObject<T_Scalar,T_RScalar,T_ReturnType> {

	public:
		XxVector();
		~XxVector();

		// no copy
		XxVector(const XxVector<T_Scalar,T_RScalar,T_ReturnType>&) = delete;
		XxVector<T_Scalar,T_RScalar,T_ReturnType>& operator=(const XxVector<T_Scalar,T_RScalar,T_ReturnType>&) = delete;

		// move
		XxVector(XxVector<T_Scalar,T_RScalar,T_ReturnType>&&) = default;
		XxVector<T_Scalar,T_RScalar,T_ReturnType>& operator=(XxVector<T_Scalar,T_RScalar,T_ReturnType>&&) = default;

		/**
		 * @brief Copies a vector.
		 * @return A deep copy of the vector.
		 */
		T_ReturnType copy() const;

		/**
		 * @brief Clones a vector.
		 * @return A shallow copy of the vector, original vector is unchanged.
		 */
		T_ReturnType rcopy();

		/**
		 * @brief Clones a vector.
		 * @return A guard of the vector.
		 */
		Guard<T_ReturnType> rcopy() const;

		/**
		 * @brief Moves a vector.
		 * @return A shallow copy of the vector, original vector is destroyed.
		 */
		T_ReturnType move();

		/**
		 * @brief Vector Euclidian norm.
		 * @return The Euclidian norm of the vector.
		 */
		T_RScalar normEuc() const;

		/**
		 * @brief Gets a subvector copy.
		 *
		 * Gets a copy of a ni-sized block of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A copy of a portion of the vector.
		 */
		T_ReturnType block(uint_t ibgn, uint_t ni) const;

		/**
		 * @brief Gets a subvector reference.
		 *
		 * Gets a reference of a ni-sized block of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A reference to a portion of the vector.
		 */
		T_ReturnType rblock(uint_t ibgn, uint_t ni);

		/**
		 * @brief Gets a subvector reference.
		 *
		 * Gets a reference of a ni-sized block of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A guarded reference to a portion of the vector.
		 */
		Guard<T_ReturnType> rblock(uint_t ibgn, uint_t ni) const;

		/**
		 * @brief Creates a vector from aux data.
		 *
		 * Creates a n-sized vector from bulk data.
		 *
		 * @param[in] n The vector size.
		 * @param[in] vals The array containing the vector values.
		 * @param[in] bind Binds the data to the vector, the vector will deallocate vals on destroy using i_free().
		 * @return The newly created vector.
		 */
		static T_ReturnType wrap(uint_t n, T_Scalar *vals, bool bind);

		/**
		 * @brief Creates a guard from aux data.
		 *
		 * Creates a n-sized guarded vector from bulk data.
		 *
		 * @param[in] n The vector size.
		 * @param[in] vals The array containing the vector values.
		 * @return The newly created guard.
		 */
		static Guard<T_ReturnType> wrap(uint_t n, const T_Scalar *vals);

};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup dense_vectors
 * @brief Writes to os the contents of vec.
 */
template <typename T_Scalar, typename T_RScalar, typename T_ReturnType>
std::ostream& operator<<(std::ostream& os, const cla3p::dns::XxVector<T_Scalar,T_RScalar,T_ReturnType>& vec)
{
  os << vec.toString();
  return os;
}

#endif // CLA3P_DNS_XXVECTOR_HPP_
