#ifndef CLA3P_PERM_MATRIX_HPP_
#define CLA3P_PERM_MATRIX_HPP_

/** @file
 * The permutation matrix definitions.
 */

#include "types.hpp"
#include "generic/universal.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @class PermMatrix
 * @nosubgrouping
 * @brief The permutation matrix class (0-based).
 *
 * Permutation matrices are represented by an array of (unsigned) integers. @n
 * Their purpose is to rearrange indices using a predefined mapping. @n
 * So an n-sized PermMatrix is a 1D entity and its individual values lie in [0, n-1].
 */
class PermMatrix : private UniversalMetaTypes, private UniversalMetaData {

	public:
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
		 * @brief Destroys the permutation matrix.
		 */
		~PermMatrix();

		// no copy
		PermMatrix(const PermMatrix&) = delete;
		PermMatrix& operator=(const PermMatrix&) = delete;

		/**
		 * @brief The move constructor.
		 *
		 * Constructs a permutation matrix with the contents of other, other is destroyed.
		 */
		PermMatrix(PermMatrix&& other);

		/**
		 * @name Operators
		 */

		/** @{ */

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
		 * @brief Matrix entry operator.
		 * @param[in] i The number of the requested index.
		 * @return A reference to the i-th element of the permutation.
		 */
		const uint_t& operator()(uint_t i) const;

		/** @} */

		// 
		// non inherited args
		//

		/**
		 * @brief The permutation size.
		 * @return The number of permutation size.
		 */
		uint_t size() const;

		/**
		 * @brief The values array.
		 * @return The pointer to the numerical values of the permutation matrix.
		 */
		uint_t* values();

		/**
		 * @brief The values array.
		 * @return The pointer to the numerical values of the permutation matrix.
		 */
		const uint_t* values() const;

		// 
		// callcable from empty
		//

		/**
		 * @brief Clears the permutation matrix.
		 */
		void clear();

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
		 * @brief Prints permutation matrix information to a string.
		 * @param[in] msg Set a header identifier.
		 * @return A string containing the permutation matrix information
		 */
		std::string info(const std::string& msg = "") const;

		/**
		 * @brief Prints the contents of the permutation matrix.
		 */
		void print() const;

		/**
		 * @brief Prints the contents of the permutation matrix to a string.
		 * @return The string containing the formatted numerical values of the permutation matrix.
		 */
		std::string printToString() const;

		// 
		// not callcable from empty
		// ...
		//

		// 
		// static initializers (basic)
		//

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
		 * @brief Creates a random permutation matrix
		 *
		 * Creates an n-sized permutation matrix with randomly rearranged indexes.
		 *
		 * @param[in] n The permutation matrix size.
		 * @return The newly created permutation matrix.
		 */
		static PermMatrix random(uint_t n);

	private:
		uint_t *m_values;

		void setValues(uint_t *values);

		void defaults();
		void creator(uint_t size, uint_t *values, bool owner);
		void blankCreator(uint_t size);
		void randomCreator(uint_t size);
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @brief Writes to os the contents of mat
 */
std::ostream& operator<<(std::ostream& os, const cla3p::PermMatrix& mat);
/*-------------------------------------------------*/

#endif // CLA3P_PERM_MATRIX_HPP_
