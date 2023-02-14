#ifndef CLA3P_PERM_MATRIX_HPP_
#define CLA3P_PERM_MATRIX_HPP_

/** @file
 * The permutation matrix definitions
 */

#include "types.hpp"
#include "generic/universal.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @class PermMatrix
 * @brief The permutation matrix object
 */
class PermMatrix : private UniversalMetaTypes, private UniversalMetaData {

	public:
		/**
		 * @brief The default constructor
		 *
		 * Constructs an empty matrix
		 */
		PermMatrix();

		/**
		 * @brief The dimensional constructor
		 *
		 * Constructs a general (n x n) PermMatrix with uninitialized values
		 *
		 * @param[in] n The number of matrix rows and columns
		 */
		PermMatrix(uint_t n);

		/**
		 * @brief Destroys the matrix
		 */
		~PermMatrix();

		// no copy
		PermMatrix(const PermMatrix&) = delete;
		PermMatrix& operator=(const PermMatrix&) = delete;

		/**
		 * @brief Move constructor
		 *
		 * Constructs a matrix with the contents of other, other is destroyed
		 */
		PermMatrix(PermMatrix&& other);

		/**
		 * @brief Move assignment operator
		 *
		 * Replaces the contents with those of other, other is destroyed
		 */
		PermMatrix& operator=(PermMatrix&& other);

		// 
		// non inherited args
		//

		/**
		 * @brief The matrix rows/columns
		 * @return The number of matrix rows/columns
		 */
		uint_t size() const;

		/**
		 * @brief The values array
		 * @return The pointer to the numerical values of the object
		 */
		uint_t* values();

		/**
		 * @brief The values array
		 * @return The pointer to the numerical values of the object
		 */
		const uint_t* values() const;

		// 
		// callcable from empty
		//

		/**
		 * @brief Clears the object
		 */
		void clear();

		/**
		 * @brief Copies a matrix
		 * @return A deep copy of the matrix
		 */
		PermMatrix copy() const;

		/**
		 * @brief Moves a matrix
		 * @return A shallow copy of the matrix, original matrix is destroyed
		 */
		PermMatrix move();

		/**
		 * @brief Prints matrix information
		 * @param[in] msg Set a header identifier
		 */
		void info(const std::string& msg = "") const;

		/**
		 * @brief Prints the contents of the object
		 */
		void print() const;

		uint_t& operator()(uint_t i);
		const uint_t& operator()(uint_t i) const;

		// 
		// not callcable from empty
		// ...
		//

		// 
		// static initializers (basic)
		//

		/**
		 * @brief Creates a matrix
		 * @param[in] n The number of matrix rows/columns
		 * @return A matrix with uninitialized values
		 */
		static PermMatrix init(uint_t n);

		/**
		 * @brief Creates a random permutation matrix
		 * @param[in] n The number of matrix rows/columns
		 * @return A matrix with randomly rearranged rows/columns
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

#endif // CLA3P_PERM_MATRIX_HPP_
