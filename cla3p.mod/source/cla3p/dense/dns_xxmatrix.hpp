#ifndef CLA3P_DNS_XXMATRIX_HPP_
#define CLA3P_DNS_XXMATRIX_HPP_

#include <string>

#include "cla3p/types/basic_traits.hpp"
#include "cla3p/dense/dns_xxobject.hpp"
#include "cla3p/generic/guard.hpp"

/*-------------------------------------------------*/

namespace cla3p { template <typename T_Int> class PxMatrix; }

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief A dense matrix class.
 */
template <typename T_Scalar, typename T_Matrix>
class XxMatrix : public XxObject<T_Scalar,T_Matrix> {

	private:
		using T_RScalar = typename BasicTypeTraits<T_Scalar>::real_type;
		using T_Vector = typename BasicTypeTraits<T_Matrix>::vector_type;

	public:

		// no copy
		XxMatrix(const XxMatrix<T_Scalar,T_Matrix>&) = delete;
		XxMatrix<T_Scalar,T_Matrix>& operator=(const XxMatrix<T_Scalar,T_Matrix>&) = delete;

		/** 
		 * @name Constructors
		 * @{
		 */

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty matrix.
		 */
		explicit XxMatrix();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs a general (nr x nc) matrix with uninitialized values.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] pr The matrix property.
		 */
		explicit XxMatrix(uint_t nr, uint_t nc, const Property& pr = defaultProperty());

		/**
		 * @brief The move constructor.
		 *
		 * Constructs a matrix with the contents of other, other is destroyed.
		 */
		XxMatrix(XxMatrix<T_Scalar,T_Matrix>&& other) = default;

		/**
		 * @brief Destroys the matrix.
		 */
		~XxMatrix();

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
		XxMatrix<T_Scalar,T_Matrix>& operator=(XxMatrix<T_Scalar,T_Matrix>&& other) = default;

		/**
		 * @brief Matrix entry operator.
		 * @param[in] i The row number of the requested entry.
		 * @param[in] j The column number of the requested entry.
		 * @return A reference to the (i,j)-th element of the matrix.
		 */
		T_Scalar& operator()(uint_t i, uint_t j);

		/**
		 * @copydoc cla3p::dns::XxMatrix::operator()(uint_t i, uint_t j)
		 */
		const T_Scalar& operator()(uint_t i, uint_t j) const;

		/**
		 * @brief The value setter operator.
		 *
		 * Sets all entries of the matrix to a single value.@n
		 * Imaginary part of diagonal is set to zero for Hermitian cases.@n
		 * Diagonal is set to zero for Skew cases.
		 *
		 * @param[in] val The value to be set.
		 */
		void operator=(T_Scalar val);

		/**
		 * @brief The matrix-matrix multiplication operator.
		 *
		 * Multiplies *this with other.
		 *
		 * @param[in] other The left hand side multiplier.
		 * @return The result of the operation (*this * other).
		 */
		T_Matrix operator*(const XxMatrix<T_Scalar,T_Matrix>& other) const;

		/**
		 * @brief Solves the linear system other * x = *this.
		 *
		 * @param[in] other The lhs matrix.
		 * @return The result of the operation (other^{-1} * (*this)).
		 */
		T_Matrix operator/(const XxMatrix<T_Scalar,T_Matrix>& other) const;

		/**
		 * @brief Overwrites *this with the solution other^{-1} * (*this).
		 *
		 * @param[in] other The lhs matrix.
		 * @return The result of the operation (other^{-1} * (*this)).
		 */
		XxMatrix<T_Scalar,T_Matrix>& operator/=(const XxMatrix<T_Scalar,T_Matrix>& other);

		/** @} */

		/** 
		 * @name Arguments
		 * @{
		 */

		/**
		 * @brief The matrix rows.
		 * @return The number of the matrix rows.
		 */
		uint_t nrows() const;

		/**
		 * @brief The matrix columns.
		 * @return The number of the matrix columns.
		 */
		uint_t ncols() const;

		/**
		 * @brief The matrix leading dimension.
		 * @return The leading dimension of the matrix (column-major: ld() @f$ \geq @f$ nrows()).
		 */
		uint_t ld() const;

		/**
		 * @brief The matrix property.
		 * @return The property that characterizes the matrix.
		 */
		const Property& prop() const;

		/** @} */

		/** 
		 * @name Public Member Functions
		 * @{
		 */

		/**
		 * @brief Prints matrix information.
		 * @param[in] msg Set a header identifier.
		 */
		std::string info(const std::string& msg = "") const;

		/**
		 * @brief Matrix infinite norm.
		 * @return The infinite norm of the matrix.
		 */
		T_RScalar normMax() const;

		/**
		 * @brief Matrix Frobenius norm.
		 * @return The Frobenius norm of the matrix.
		 */
		T_RScalar normFro() const;

		/**
		 * @brief Transposes a general matrix.
		 * @return The transposed copy of the matrix.
		 */
		T_Matrix transpose() const;

		/**
		 * @brief Converts a matrix to general.
		 * @return A copy of the matrix with general property.
		 */
		T_Matrix general() const;

		/**
		 * @brief Converts a matrix to general in-place.
		 */
		void igeneral();

		/**
		 * @brief Permutes a general matrix.
		 *
		 * Creates a permuted copy @f$ (PAQ) @f$ of the matrix @f$ A @f$.
		 *
		 * @param[in] P The left side permutation matrix.
		 * @param[in] Q The right side permutation matrix.
		 * @return The permuted copy of the matrix.
		 */
		T_Matrix permuteLeftRight(const PxMatrix<int_t>& P, const PxMatrix<int_t>& Q) const;

		/**
		 * @brief Permutes the rows of a general matrix.
		 *
		 * Creates a permuted copy @f$ (PA) @f$ of the matrix @f$ A @f$.
		 *
		 * @param[in] P The left side permutation matrix.
		 * @return The permuted copy of the matrix.
		 */
		T_Matrix permuteLeft(const PxMatrix<int_t>& P) const;

		/**
		 * @brief Permutes the columns of a general matrix.
		 *
		 * Creates a permuted copy @f$ (AQ) @f$ of the matrix @f$ A @f$.
		 *
		 * @param[in] Q The right side permutation matrix.
		 * @return The permuted copy of the matrix.
		 */
		T_Matrix permuteRight(const PxMatrix<int_t>& Q) const;

		/**
		 * @brief Permutes a matrix symmetrically.
		 *
		 * Creates a permuted copy @f$ (PAP^T) @f$ of the matrix @f$ A @f$.
		 *
		 * @param[in] P The left and right side permutation matrix.
		 * @return The permuted copy of the matrix.
		 */
		T_Matrix permuteMirror(const PxMatrix<int_t>& P) const;

		/**
		 * @brief Permutes a general matrix in-place.
		 *
		 * Replaces @f$ A @f$ with @f$ PAQ @f$.
		 *
		 * @param[in] P The left side permutation matrix.
		 * @param[in] Q The right side permutation matrix.
		 */
		void ipermuteLeftRight(const PxMatrix<int_t>& P, const PxMatrix<int_t>& Q);

		/**
		 * @brief Permutes the rows of a general matrix in-place.
		 *
		 * Replaces @f$ A @f$ with @f$ PA @f$.
		 *
		 * @param[in] P The left side permutation matrix.
		 */
		void ipermuteLeft(const PxMatrix<int_t>& P);

		/**
		 * @brief Permutes the columns of a general matrix in-place.
		 *
		 * Replaces @f$ A @f$ with @f$ AQ @f$.
		 *
		 * @param[in] Q The right side permutation matrix.
		 */
		void ipermuteRight(const PxMatrix<int_t>& Q);

		/**
		 * @brief Permutes a matrix symmetrically in-place.
		 *
		 * Replaces @f$ A @f$ with @f$ PAP^T @f$.
		 *
		 * @param[in] P The left and right side permutation matrix.
		 */
		void ipermuteMirror(const PxMatrix<int_t>& P);

		/**
		 * @brief Gets a submatrix copy.
		 *
		 * Gets a copy of a (ni x nj) block of the matrix, starting at (ibgn, jbgn).
		 *
		 * @param[in] ibgn The matrix row that the requested part begins.
		 * @param[in] jbgn The matrix column that the requested part begins.
		 * @param[in] ni The number of rows of the requested block.
		 * @param[in] nj The number of columns of the requested block.
		 * @return A copy of a portion of the matrix.
		 */
		T_Matrix block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @brief Gets a submatrix reference.
		 *
		 * Gets a reference of a (ni x nj) block of the matrix, starting at (ibgn, jbgn)
		 *
		 * @param[in] ibgn The matrix row that the requested part begins.
		 * @param[in] jbgn The matrix column that the requested part begins.
		 * @param[in] ni The number of rows of the requested block.
		 * @param[in] nj The number of columns of the requested block.
		 * @return A reference to a portion of the matrix.
		 */
		T_Matrix rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

		/**
		 * @brief Gets a submatrix reference.
		 *
		 * Gets a reference of a (ni x nj) block of the matrix, starting at (ibgn, jbgn)
		 *
		 * @param[in] ibgn The matrix row that the requested part begins.
		 * @param[in] jbgn The matrix column that the requested part begins.
		 * @param[in] ni The number of rows of the requested block.
		 * @param[in] nj The number of columns of the requested block.
		 * @return A guarded reference to a portion of the matrix.
		 */
		Guard<T_Matrix> rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @brief Sets a submatrix.
		 *
		 * Copies the contents of a block in the matrix, starting at (ibgn, jbgn)
		 *
		 * @param[in] ibgn The matrix row that src will be placed.
		 * @param[in] jbgn The matrix column that src will be placed.
		 * @param[in] src The block to be placed.
		 */
		void setBlock(uint_t ibgn, uint_t jbgn, const XxMatrix<T_Scalar,T_Matrix>& src);

		/**
		 * @brief Gets a matrix column copy.
		 *
		 * Gets a copy of the j-th column of the matrix.
		 *
		 * @param[in] j The matrix column requested.
		 * @return A copy of the column of the matrix.
		 */
		T_Vector column(uint_t j) const;

		/**
		 * @brief Gets a matrix column reference.
		 *
		 * Gets a reference of the j-th column of the matrix.
		 *
		 * @param[in] j The matrix column requested.
		 * @return A reference of the column of the matrix.
		 */
		T_Vector rcolumn(uint_t j);

		/**
		 * @brief Gets a matrix column reference.
		 *
		 * Gets a reference of the j-th column of the matrix.
		 *
		 * @param[in] j The matrix column requested.
		 * @return A guarded reference of the column of the matrix.
		 */
		Guard<T_Vector> rcolumn(uint_t j) const;

		/** @} */

		/** 
		 * @name Creators/Generators
		 * @{
		 */

		/**
		 * @brief Creates a matrix.
		 *
		 * Creates a (nr x nc) matrix with uninitialized values.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] pr The matrix property.
		 * @return The newly created matrix.
		 */
		static T_Matrix init(uint_t nr, uint_t nc, const Property& pr = defaultProperty());

		/**
		 * @brief Creates a matrix with random values in (0,1).
		 *
		 * Creates a (nr x nc) matrix with random values.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] pr The matrix property.
		 * @return The newly created matrix.
		 */
		static T_Matrix random(uint_t nr, uint_t nc, const Property& pr = defaultProperty());

		/**
		 * @brief Creates a matrix from aux data.
		 *
		 * Creates a (nr x nc) matrix from bulk data.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] vals The array containing the matrix values in column-major ordering.
		 * @param[in] ldv The leading dimension of the vals array.
		 * @param[in] bind Binds the data to the matrix, the matrix will deallocate vals on destroy using i_free().
		 * @param[in] pr The matrix property.
		 * @return The newly created matrix.
		 */
		static T_Matrix wrap(uint_t nr, uint_t nc, T_Scalar *vals, uint_t ldv, bool bind, const Property& pr = defaultProperty());

		/**
		 * @brief Creates a matrix guard from aux data.
		 *
		 * Creates a (nr x nc) matrix from bulk data.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] vals The array containing the matrix values in column-major ordering.
		 * @param[in] ldv The leading dimension of the vals array.
		 * @param[in] pr The matrix property.
		 * @return The newly created guard.
		 */
		static Guard<T_Matrix> wrap(uint_t nr, uint_t nc, const T_Scalar *vals, uint_t ldv, const Property& pr = defaultProperty());

		/** @} */

	public:
		void updateSelfWithScaledMatMat(T_Scalar alpha,
				const Operation& opA, const XxMatrix<T_Scalar,T_Matrix>& otherA,
				const Operation& opB, const XxMatrix<T_Scalar,T_Matrix>& otherB);

};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_XXMATRIX_HPP_