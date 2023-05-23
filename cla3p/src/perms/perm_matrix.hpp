#ifndef CLA3P_PERM_MATRIX_HPP_
#define CLA3P_PERM_MATRIX_HPP_

/** 
 * @file
 * The permutation matrix definitions.
 */

#include <string>

#include "../types.hpp"
#include "../generic/generic_dns.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @ingroup perm_matrices
 * @nosubgrouping
 * @brief The permutation matrix object.
 *
 * Permutation matrices are represented by an array of (unsigned) integers. @n
 * Their purpose is to rearrange indices using a predefined mapping. @n
 * So an n-sized PermMatrix is a 1D entity and its individual values lie in [0, n-1] (0-based indexing).
 */
class PermMatrix : private UniversalMetaTypes, public dns::GenericObject<uint_t,uint_t> {

	public:

		// no copy
		PermMatrix(const PermMatrix&) = delete;
		PermMatrix& operator=(const PermMatrix&) = delete;
		
		/** 
		 * @name Constructors
		 * @{
		 */

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty permutation matrix.
		 */
		PermMatrix();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs an n-sized permutation matrix with uninitialized values.
		 *
		 * @param[in] n The permutation matrix size.
		 */
		PermMatrix(uint_t n);

		/**
		 * @brief The move constructor.
		 *
		 * Constructs a permutation matrix with the contents of other, other is destroyed.
		 */
		PermMatrix(PermMatrix&& other);

		/**
		 * @brief Destroys the permutation matrix.
		 */
		~PermMatrix();

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
		PermMatrix& operator=(PermMatrix&& other);

		/**
		 * @brief Permutation matrix entry operator.
		 * @param[in] i The number of the requested index.
		 * @return A reference to the i-th element of the permutation.
		 */
		uint_t& operator()(uint_t i);

		/**
		 * @brief Permutation matrix entry operator.
		 * @param[in] i The number of the requested index.
		 * @return A reference to the i-th element of the permutation.
		 */
		const uint_t& operator()(uint_t i) const;

		/** @} */

		// -------------------------------------------------------------------------------

		/** 
		 * @name Arguments
		 * @{
		 */

		/**
		 * @brief The permutation size.
		 * @return The number of permutation size.
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
		 * @brief Prints permutation matrix information to a string.
		 * @param[in] msg Set a header identifier.
		 * @return A string containing the permutation matrix information
		 */
		std::string info(const std::string& msg = "") const;

		/**
		 * @brief Copies the permutation matrix.
		 * @return A deep copy of the permutation matrix.
		 */
		PermMatrix copy() const;

		/**
		 * @brief Moves the permutation matrix.
		 * @return A shallow copy of the permutation matrix, original matrix is destroyed.
		 */
		PermMatrix move();

		/**
		 * @brief The inverse permutation matrix.
		 * @return The inverse (transpose) of the permutation matrix.
		 */
		PermMatrix inverse() const;

		// 
		// not callcable from empty
		// ...
		//

		/** @} */

		// -------------------------------------------------------------------------------

		/** 
		 * @name Creators/Generators
		 * @{
		 */

		/**
		 * @brief Creates a permutation matrix.
		 *
		 * Creates an n-dimensional permutation matrix with uninitialized values.
		 *
		 * @param[in] n The permutation matrix size.
		 * @return The newly created permutation matrix.
		 */
		static PermMatrix init(uint_t n);

		/**
		 * @brief Creates an identity permutation matrix
		 *
		 * Creates an n-sized permutation matrix with P(i) = i.
		 *
		 * @param[in] n The permutation matrix size.
		 * @return The newly created permutation matrix.
		 */
		static PermMatrix identity(uint_t n);

		/**
		 * @brief Creates a random permutation matrix
		 *
		 * Creates an n-sized permutation matrix with randomly rearranged indexes.
		 *
		 * @param[in] n The permutation matrix size.
		 * @return The newly created permutation matrix.
		 */
		static PermMatrix random(uint_t n);

		/** @} */
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup stream_operators
 * @brief Writes to os the contents of mat
 */
std::ostream& operator<<(std::ostream& os, const cla3p::PermMatrix& mat);
/*-------------------------------------------------*/

#endif // CLA3P_PERM_MATRIX_HPP_
