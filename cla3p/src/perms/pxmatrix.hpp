#ifndef CLA3P_PXMATRIX_HPP_
#define CLA3P_PXMATRIX_HPP_

/** 
 * @file
 * The permutation matrix definitions.
 */

#include <string>
#include <ostream>

#include "../types.hpp"
#include "../generic/array2d.hpp"
#include "../generic/guard.hpp"

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
template <typename T_Scalar>
class PxMatrix : public Array2D<T_Scalar> {

	public:

		// no copy
		PxMatrix(const PxMatrix<T_Scalar>&) = delete;
		PxMatrix& operator=(const PxMatrix<T_Scalar>&) = delete;

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty permutation matrix.
		 */
		PxMatrix();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs an n-sized permutation matrix with uninitialized values.
		 *
		 * @param[in] n The permutation matrix size.
		 */
		PxMatrix(uint_t n);

		/**
		 * @brief The move constructor.
		 *
		 * Constructs a permutation matrix with the contents of other, other is destroyed.
		 */
		PxMatrix(PxMatrix<T_Scalar>&& other);

		/**
		 * @brief The move assignment operator.
		 *
		 * Replaces the contents with those of other, other is destroyed.
		 */
		PxMatrix<T_Scalar>& operator=(PxMatrix<T_Scalar>&& other);

		/**
		 * @brief Destroys the permutation matrix.
		 */
		~PxMatrix();

		/**
		 * @brief Permutation matrix entry operator.
		 * @param[in] i The number of the requested index.
		 * @return A reference to the i-th element of the permutation.
		 */
		T_Scalar& operator()(uint_t i);

		/**
		 * @brief Permutation matrix entry operator.
		 * @param[in] i The number of the requested index.
		 * @return A reference to the i-th element of the permutation.
		 */
		const T_Scalar& operator()(uint_t i) const;

		/**
		 * @brief The permutation size.
		 * @return The number of permutation size.
		 */
		uint_t size() const;

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
		PxMatrix<T_Scalar> copy() const;

		/**
		 * @brief Copies the permutation matrix.
		 * @return A shallow copy of the permutation matrix.
		 */
		PxMatrix<T_Scalar> rcopy();

		/**
		 * @brief Copies the permutation matrix.
		 * @return A shallow copy of the permutation matrix.
		 */
		Guard<PxMatrix<T_Scalar>> rcopy() const;

		/**
		 * @brief Moves the permutation matrix.
		 * @return A shallow copy of the permutation matrix, original matrix is destroyed.
		 */
		PxMatrix<T_Scalar> move();

		/**
		 * @brief The inverse permutation matrix.
		 * @return The inverse (transpose) of the permutation matrix.
		 */
		PxMatrix<T_Scalar> inverse() const;

		/**
		 * @brief Permutes a permutation matrix.
		 * @return The permutated permutation matrix (P * (*this)).
		 */
		PxMatrix<T_Scalar> permute(const PxMatrix<T_Scalar>& P) const;

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
		static PxMatrix init(uint_t n);

		/**
		 * @brief Creates an identity permutation matrix
		 *
		 * Creates an n-sized permutation matrix with P(i) = i.
		 *
		 * @param[in] n The permutation matrix size.
		 * @return The newly created permutation matrix.
		 */
		static PxMatrix identity(uint_t n);

		/**
		 * @brief Creates a random permutation matrix
		 *
		 * Creates an n-sized permutation matrix with randomly rearranged indexes.
		 *
		 * @param[in] n The permutation matrix size.
		 * @return The newly created permutation matrix.
		 */
		static PxMatrix random(uint_t n);

		/** @} */
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup stream_operators
 * @brief Writes to os the contents of mat
 */
template <typename T_Scalar>
std::ostream& operator<<(std::ostream& os, const cla3p::PxMatrix<T_Scalar>& mat)
{
  os << mat.toString();
  return os;
}

/*-------------------------------------------------*/

#endif // CLA3P_PXMATRIX_HPP_
