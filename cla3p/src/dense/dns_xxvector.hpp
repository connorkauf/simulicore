#ifndef CLA3P_DNS_XXVECTOR_HPP_
#define CLA3P_DNS_XXVECTOR_HPP_

#include <string>

#include "../types/basic_traits.hpp"
#include "../dense/dns_xxobject.hpp"
#include "../generic/guard.hpp"
#include "../perms.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief A dense vector class.
 */
template <typename T_Scalar, typename T_Vector>
class XxVector : public XxObject<T_Scalar,T_Vector> {

	using T_RScalar = typename BasicTypeTraits<T_Scalar>::real_type;
	using T_Matrix = typename BasicTypeTraits<T_Vector>::matrix_type;

	public:

		// no copy
		XxVector(const XxVector<T_Scalar,T_Vector>&) = delete;
		XxVector<T_Scalar,T_Vector>& operator=(const XxVector<T_Scalar,T_Vector>&) = delete;

		/** 
		 * @name Constructors
		 * @{
		 */

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty vector.
		 */
		explicit XxVector();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs a n-sized vector with uninitialized values.
		 *
		 * @param[in] n The vector size.
		 */
		explicit XxVector(uint_t n);

		/**
		 * @brief The move constructor.
		 *
		 * Constructs a vector with the contents of other, other is destroyed.
		 */
		XxVector(XxVector<T_Scalar,T_Vector>&& other) = default;

		/**
		 * @brief Destroys the vector.
		 */
		~XxVector();

		/** @} */

		/** 
		 * @name Operators
		 * @{
		 */

		/**
		 * @brief The move assignment operator.
		 *
		 * Replaces the contents with those of other, other is destroyed.
		 */
		XxVector<T_Scalar,T_Vector>& operator=(XxVector<T_Scalar,T_Vector>&& other) = default;

		/**
		 * @brief Vector entry operator.
		 * @param[in] i The number of the requested index.
		 * @return A reference to the i-th element of the vector.
		 */
		T_Scalar& operator()(uint_t i);

		/**
		 * @copydoc cla3p::dns::XxVector::operator()(uint_t i)
		 */
		const T_Scalar& operator()(uint_t i) const;

		/**
		 * @brief The value setter operator.
		 *
		 * Sets all entries of the vector to a single value.
		 *
		 * @param[in] val The value to be set.
		 */
		void operator=(T_Scalar val);

		/** @} */

		/** 
		 * @name Arguments
		 * @{
		 */

		/**
		 * @brief The vector size.
		 * @return The number of the vector entries.
		 */
		uint_t size() const;

		/** @} */

		/** 
		 * @name Public Member Functions
		 * @{
		 */

		/**
		 * @brief Prints vector information.
		 * @param[in] msg Set a header identifier.
		 */
		std::string info(const std::string& msg = "") const;

		/**
		 * @brief Vector Euclidian norm.
		 * @return The Euclidian norm of the vector.
		 */
		T_RScalar normEuc() const;

		/**
		 * @brief Permutes the entries of a vector
		 *
		 * Creates a permuted copy @f$ (PX) @f$ of the vector @f$ X @f$.
		 *
		 * @param[in] P The left side permutation matrix.
		 * @return The permuted copy of the vector.
		 */
		T_Vector permute(const PiMatrix& P) const;

		/**
		 * @brief Permutes the entries of a vector in-place.
		 *
		 * Replaces @f$ X @f$ with @f$ PX @f$.
		 *
		 * @param[in] P The left side permutation matrix.
		 */
		void ipermute(const PiMatrix& P);

		/**
		 * @brief Gets a subvector copy.
		 *
		 * Gets a copy of a ni-sized block of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A copy of a portion of the vector.
		 */
		T_Vector block(uint_t ibgn, uint_t ni) const;

		/**
		 * @brief Gets a subvector reference.
		 *
		 * Gets a reference of a ni-sized block of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A reference to a portion of the vector.
		 */
		T_Vector rblock(uint_t ibgn, uint_t ni);

		/**
		 * @brief Gets a subvector reference.
		 *
		 * Gets a reference of a ni-sized block of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A guarded reference to a portion of the vector.
		 */
		Guard<T_Vector> rblock(uint_t ibgn, uint_t ni) const;

		/**
		 * @brief Sets a subvector.
		 *
		 * Copies the contents of src in the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that src will be placed.
		 * @param[in] src The vector to be placed.
		 */
		void setBlock(uint_t ibgn, const T_Vector& src);

		/**
		 * @brief Converts a vector to a matrix.
		 * @return A copy of the vector as matrix.
		 */
		T_Matrix matrix() const;

		/**
		 * @brief Converts a vector to a matrix.
		 * @return A reference of the vector as matrix.
		 */
		T_Matrix rmatrix();

		/**
		 * @brief Converts a vector to a matrix.
		 * @return A reference of the vector as matrix guard.
		 */
		Guard<T_Matrix> rmatrix() const;

		/** @} */

		/** 
		 * @name Creators/Generators
		 * @{
		 */

		/**
		 * @brief Creates a vector.
		 *
		 * Creates a n-sized vector with uninitialized values.
		 *
		 * @param[in] n The vector size.
		 * @return The newly created vector.
		 */
		static T_Vector init(uint_t n);

		/**
		 * @brief Creates a vector with random values in (0,1).
		 *
		 * Creates a n-sized vector with random values.
		 *
		 * @param[in] n The vector size.
		 * @return The newly created vector.
		 */
		static T_Vector random(uint_t n);

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
		static T_Vector wrap(uint_t n, T_Scalar *vals, bool bind);

		/**
		 * @brief Creates a guard from aux data.
		 *
		 * Creates a n-sized guarded vector from bulk data.
		 *
		 * @param[in] n The vector size.
		 * @param[in] vals The array containing the vector values.
		 * @return The newly created guard.
		 */
		static Guard<T_Vector> wrap(uint_t n, const T_Scalar *vals);

		/** @} */

	public:
		void updateSelfWithScaledMatVec(T_Scalar alpha, const Operation& opA,
				const T_Matrix& otherA,
				const T_Vector& otherX);

};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_XXVECTOR_HPP_
