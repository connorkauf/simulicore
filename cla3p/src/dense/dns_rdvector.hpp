#ifndef CLA3P_DNS_RDVECTOR_HPP_
#define CLA3P_DNS_RDVECTOR_HPP_

/** 
 * @file
 * The double precision real dense vector definitions.
 */

#include <string>

#include "../types.hpp"
#include "../generic/generic_dns.hpp"
#include "../generic/guard.hpp"
#include "../dense/dns_rdmatrix.hpp"

/*-------------------------------------------------*/
namespace cla3p {
class PermMatrix;
namespace dns {
/*-------------------------------------------------*/
class RdVGuard;

/**
 * @ingroup dense_vectors
 * @nosubgrouping 
 * @brief The double precision real dense vector object.
 */
class RdVector : private UniversalMetaTypes, public GenericObject<real_t,real_t> {

	public:

		// no copy
		RdVector(const RdVector&) = delete;
		RdVector& operator=(const RdVector&) = delete;

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
		RdVector();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs a n-sized vector with uninitialized values.
		 *
		 * @param[in] n The vector size.
		 */
		RdVector(uint_t n);

		/**
		 * @brief The move constructor.
		 *
		 * Constructs a vector with the contents of other, other is destroyed.
		 */
		RdVector(RdVector&& other);

		/**
		 *
		 * @brief Destroys the vector.
		 */
		~RdVector();

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
		RdVector& operator=(RdVector&& other);

		/**
		 * @brief Vector entry operator.
		 * @param[in] i The index number of the requested entry
		 * @return A reference to the i-th element of the vector.
		 */
		real_t& operator()(uint_t i);

		/**
		 * @brief Vector entry operator.
		 * @param[in] i The index number of the requested entry
		 * @return A reference to the i-th element of the vector.
		 */
		const real_t& operator()(uint_t i) const;

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
		RdVector copy() const;

		/**
		 * @brief Moves a vector.
		 * @return A shallow copy of the vector, original vector is destroyed.
		 */
		RdVector move();

		/**
		 * @brief Clones a vector.
		 * @return A shallow copy of the vector, original vector is unchanged.
		 */
		RdVector clone();

		/**
		 * @brief Clones a vector.
		 * @return A guard of the vector.
		 */
		RdVGuard clone() const;

		/**
		 * @brief Converts a vector to a matrix.
		 * @return A copy of the vector as matrix.
		 */
		RdMatrix matrix() const;

		/**
		 * @brief Converts a vector to a matrix.
		 * @return A reference of the vector as matrix.
		 */
		RdMatrix rmatrix();

		/**
		 * @brief Converts a vector to a matrix.
		 * @return A reference of the vector as matrix guard.
		 */
		RdMGuard rmatrix() const;

		/**
		 * @brief Scales vector by coeff.
		 * @param[in] coeff The scaling coefficient.
		 */
		void scale(real_t coeff);

		/**
		 * @brief Vector 1-norm.
		 * @return The 1-norm of the vector.
		 */
		real_t normOne() const;

		/**
		 * @brief Vector infinite norm.
		 * @return The infinite norm of the vector.
		 */
		real_t normInf() const;

		/**
		 * @brief Vector Euclidian norm.
		 * @return The Euclidian norm of the vector.
		 */
		real_t normEuc() const;

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
		RdVector permute(const PermMatrix& P) const;

		/**
		 * @brief Permutes the entries of a vector in-place.
		 *
		 * Replaces @f$ X @f$ with @f$ PX @f$.
		 *
		 * @param[in] P The left side permutation matrix.
		 */
		void ipermute(const PermMatrix& P);

		/**
		 * @brief Gets a subvector copy.
		 *
		 * Gets a copy of a ni-sized block of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A copy of a portion of the vector.
		 */
		RdVector block(uint_t ibgn, uint_t ni) const;

		/**
		 * @brief Gets a subvector reference.
		 *
		 * Gets a reference of a ni-sized block of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A reference to a portion of the vector.
		 */
		RdVector rblock(uint_t ibgn, uint_t ni);

		/**
		 * @brief Gets a subvector reference.
		 *
		 * Gets a reference of a ni-sized block of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A guarded reference to a portion of the vector.
		 */
		RdVGuard rblock(uint_t ibgn, uint_t ni) const;

		/**
		 * @brief Sets a subvector.
		 *
		 * Copies the contents of a block in the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that src will be placed.
		 * @param[in] src The block to be placed.
		 */
		void setBlock(uint_t ibgn, const RdVector& src);

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
		static RdVector init(uint_t n);

		/**
		 * @brief Creates a zero vector.
		 *
		 * Creates a n-sized vector with all values set to zero.
		 *
		 * @param[in] n The vector size.
		 * @return The newly created vector.
		 */
		static RdVector zero(uint_t n);

		/**
		 * @brief Creates a vector with random values in (0,1).
		 *
		 * Creates a n-sized vector with random values.
		 *
		 * @param[in] n The vector size.
		 * @return The newly created vector.
		 */
		static RdVector random(uint_t n);

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
		static RdVector wrap(uint_t n, real_t *vals, bool bind);

		/**
		 * @brief Creates a guard from aux data.
		 *
		 * Creates a n-sized guarded vector from bulk data.
		 *
		 * @param[in] n The vector size.
		 * @param[in] vals The array containing the vector values.
		 * @return The newly created guard.
		 */
		static RdVGuard wrap(uint_t n, const real_t *vals);

		/** @} */
};

/*-------------------------------------------------*/

/**
 * @ingroup dense_guards
 * @brief The double precision real dense vector guard.
 *
 * The vector guard class is a vector wrapper class. 
 * Useful for protecting immutable data from being exposed.
 */
class RdVGuard : private Guard<RdVector> {

	public:

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty guard.
		 */
		RdVGuard();

		/**
		 * @brief Destroys the guard.
		 */
		~RdVGuard();

		/**
		 * @brief The copy constructor.
		 *
		 * Constructs a guard with a clone of the contents of other.
		 */
		RdVGuard(const RdVGuard& other);

		/**
		 * @brief The copy assignment operator.
		 *
		 * Replaces the contents of guard with a clone of the contents of other.
		 */
		RdVGuard& operator=(const RdVGuard& other);

		/**
		 * @brief The vector being guarded.
		 * @return A constant reference to the vector being guarded.
		 */
		const RdVector& vec() const;

		friend class RdVector;
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup stream_operators
 * @brief Writes to os the contents of vec
 */
std::ostream& operator<<(std::ostream& os, const cla3p::dns::RdVector& vec);
/*-------------------------------------------------*/

#endif // CLA3P_DNS_RDVECTOR_HPP_
