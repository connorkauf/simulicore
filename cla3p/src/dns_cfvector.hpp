#ifndef CLA3P_DNS_CFVECTOR_HPP_
#define CLA3P_DNS_CFVECTOR_HPP_

/** 
 * @file
 * The single precision complex dense vector definitions.
 */

#include <string>

#include "types.hpp"
#include "generic/generic_dns.hpp"
#include "generic/guard.hpp"

/*-------------------------------------------------*/
namespace cla3p {
class PermMatrix;
namespace dns {
/*-------------------------------------------------*/
class CfVGuard;

/**
 * @ingroup dense_vector_group
 * @nosubgrouping 
 * @brief The single precision complex dense vector object.
 */
class CfVector : private UniversalMetaTypes, public GenericObject<complex8_t,real4_t> {

	public:

		// no copy
		CfVector(const CfVector&) = delete;
		CfVector& operator=(const CfVector&) = delete;

		// -------------------------------------------------------------------------------

		/** 
		 * @name Constructors
		 * @{
		 */

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty vector.
		 */
		CfVector();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs a n-sized vector with uninitialized values.
		 *
		 * @param[in] n The vector size.
		 */
		CfVector(uint_t n);

		/**
		 * @brief The move constructor.
		 *
		 * Constructs a vector with the contents of other, other is destroyed.
		 */
		CfVector(CfVector&& other);

		/**
		 *
		 * @brief Destroys the vector.
		 */
		~CfVector();

		/** @} */

		// -------------------------------------------------------------------------------

		/** 
		 * @name Operators
		 * @{
		 */

		/**
		 * @brief The move assignment operator.
		 *
		 * Replaces the contents with those of other, other is destroyed.
		 */
		CfVector& operator=(CfVector&& other);

		/**
		 * @brief Vector entry operator.
		 * @param[in] i The index number of the requested entry
		 * @return A reference to the i-th element of the vector.
		 */
		complex8_t& operator()(uint_t i);

		/**
		 * @brief Vector entry operator.
		 * @param[in] i The index number of the requested entry
		 * @return A reference to the i-th element of the vector.
		 */
		const complex8_t& operator()(uint_t i) const;

		/** @} */

		// -------------------------------------------------------------------------------

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

		// -------------------------------------------------------------------------------

		/** 
		 * @name Operations
		 * @{
		 */

		// 
		// callcable from empty
		//

		/**
		 * @brief Prints vector information.
		 * @param[in] msg Set a header identifier.
		 */
		std::string info(const std::string& msg = "") const;

		/**
		 * @brief Copies a vector.
		 * @return A deep copy of the vector.
		 */
		CfVector copy() const;

		/**
		 * @brief Moves a vector.
		 * @return A shallow copy of the vector, original vector is destroyed.
		 */
		CfVector move();

		/**
		 * @brief Clones a vector.
		 * @return A shallow copy of the vector, original vector is unchanged.
		 */
		CfVector clone();

		/**
		 * @brief Clones a vector.
		 * @return A guard of the vector.
		 */
		CfVGuard clone() const;

		/**
		 * @brief Scales vector by coeff.
		 * @param[in] coeff The scaling coefficient.
		 */
		void scale(complex8_t coeff);

		/**
		 * @brief Vector 1-norm.
		 * @return The 1-norm of the vector.
		 */
		real4_t normOne() const;

		/**
		 * @brief Vector infinite norm.
		 * @return The infinite norm of the vector.
		 */
		real4_t normInf() const;

		/**
		 * @brief Vector Euclidian norm.
		 * @return The Euclidian norm of the vector.
		 */
		real4_t normEuc() const;

		// 
		// not callcable from empty
		//

		/**
		 * @brief Permutes the entries of a vector
		 *
		 * Creates a permuted copy @f$ (PX) @f$ of the vector @f$ X @f$.
		 *
		 * @param[in] P The left side permutation matrix.
		 * @return The permuted copy of the vector.
		 */
		CfVector permuteLeft(const PermMatrix& P) const;

		/**
		 * @brief Permutes the entries of a vector in-place.
		 *
		 * Replaces @f$ X @f$ with @f$ PX @f$.
		 *
		 * @param[in] P The left side permutation matrix.
		 */
		void ipermuteLeft(const PermMatrix& P);

		/**
		 * @brief Gets a subvector copy.
		 *
		 * Gets a copy of a ni-sized block of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A copy of a portion of the vector.
		 */
		CfVector block(uint_t ibgn, uint_t ni) const;

		/**
		 * @brief Gets a subvector reference.
		 *
		 * Gets a reference of a ni-sized block of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A reference to a portion of the vector.
		 */
		CfVector rblock(uint_t ibgn, uint_t ni);

		/**
		 * @brief Gets a subvector reference.
		 *
		 * Gets a reference of a ni-sized block of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A guarded reference to a portion of the vector.
		 */
		CfVGuard rblock(uint_t ibgn, uint_t ni) const;

		/**
		 * @brief Sets a subvector.
		 *
		 * Copies the contents of a block in the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that src will be placed.
		 * @param[in] src The block to be placed.
		 */
		void setBlock(uint_t ibgn, const CfVector& src);

		/** @} */

		// -------------------------------------------------------------------------------

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
		static CfVector init(uint_t n);

		/**
		 * @brief Creates a zero vector.
		 *
		 * Creates a n-sized vector with all values set to zero.
		 *
		 * @param[in] n The vector size.
		 * @return The newly created vector.
		 */
		static CfVector zero(uint_t n);

		/**
		 * @brief Creates a vector with random values in (0,1).
		 *
		 * Creates a n-sized vector with random values.
		 *
		 * @param[in] n The vector size.
		 * @return The newly created vector.
		 */
		static CfVector random(uint_t n);

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
		static CfVector wrap(uint_t n, complex8_t *vals, bool bind);

		/**
		 * @brief Creates a guard from aux data.
		 *
		 * Creates a n-sized guarded vector from bulk data.
		 *
		 * @param[in] n The vector size.
		 * @param[in] vals The array containing the vector values.
		 * @return The newly created guard.
		 */
		static CfVGuard wrap(uint_t n, const complex8_t *vals);

		/** @} */
};

/*-------------------------------------------------*/

/**
 * @ingroup dense_guard_group
 * @brief The single precision complex dense vector guard.
 *
 * The vector guard class is a vector wrapper class. 
 * Useful for protecting immutable data from being exposed.
 */
class CfVGuard : private Guard<CfVector> {

	public:

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty guard.
		 */
		CfVGuard();

		/**
		 * @brief Destroys the guard.
		 */
		~CfVGuard();

		/**
		 * @brief The copy constructor.
		 *
		 * Constructs a guard with a clone of the contents of other.
		 */
		CfVGuard(const CfVGuard& other);

		/**
		 * @brief The copy assignment operator.
		 *
		 * Replaces the contents of guard with a clone of the contents of other.
		 */
		CfVGuard& operator=(const CfVGuard& other);

		/**
		 * @brief The vector being guarded.
		 * @return A constant reference to the vector being guarded.
		 */
		const CfVector& vec() const;

		friend class CfVector;
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup stream_operator_group
 * @brief Writes to os the contents of vec
 */
std::ostream& operator<<(std::ostream& os, const cla3p::dns::CfVector& vec);
/*-------------------------------------------------*/

#endif // CLA3P_DNS_CFVECTOR_HPP_
