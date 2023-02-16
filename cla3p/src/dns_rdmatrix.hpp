#ifndef CLA3P_DNS_RDMATRIX_HPP_
#define CLA3P_DNS_RDMATRIX_HPP_

/** @file
 * The double precision real dense matrix definitions.
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
class RdMGuard;

/**
 * @class RdMatrix
 * @nosubgrouping 
 * @brief The double precision real dense matrix object.
 */
class RdMatrix : private UniversalMetaTypes, public GenericObject<real_t,real_t> {

	public:

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty matrix.
		 */
		RdMatrix();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs a general (nr x nc) matrix with uninitialized values.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 */
		RdMatrix(uint_t nr, uint_t nc);

		/**
		 * @brief The advanced constructor.
		 *
		 * Constructs a (nr x nc) matrix with advanced options.
		 *
		 * @param[in] ptype The matrix property.
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] wipe Set all matrix values to zero.
		 */
		RdMatrix(prop_t ptype, uint_t nr, uint_t nc, bool wipe);

		/**
		 * @brief Destroys the matrix.
		 */
		~RdMatrix();

		// no copy
		RdMatrix(const RdMatrix&) = delete;
		RdMatrix& operator=(const RdMatrix&) = delete;

		/**
		 * @brief The move constructor.
		 *
		 * Constructs a matrix with the contents of other, other is destroyed.
		 */
		RdMatrix(RdMatrix&& other);

		/** 
		 * @name Operators
		 */

		/** @{ */

		/**
		 * @brief The move assignment operator.
		 *
		 * Replaces the contents with those of other, other is destroyed.
		 */
		RdMatrix& operator=(RdMatrix&& other);

		/**
		 * @brief Matrix entry operator.
		 * @param[in] i The row number of the requested entry
		 * @param[in] j The column number of the requested entry
		 * @return A reference to the (i,j)-th element of the matrix.
		 */
		real_t& operator()(uint_t i, uint_t j);

		/**
		 * @brief Matrix entry operator.
		 * @param[in] i The row number of the requested entry
		 * @param[in] j The column number of the requested entry
		 * @return A reference to the (i,j)-th element of the matrix.
		 */
		const real_t& operator()(uint_t i, uint_t j) const;

		/** @} */

		// 
		// non inherited args
		//

		/**
		 * @brief The matrix rows.
		 * @return The number of matrix rows.
		 */
		uint_t nrows() const;

		/**
		 * @brief The matrix columns.
		 * @return The number of matrix columns.
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

		// 
		// callcable from empty
		//

		/**
		 * @brief Scales matrix by coeff.
		 * @param[in] coeff The scaling coefficient.
		 */
		void scale(real_t coeff);

		/**
		 * @brief Copies a matrix.
		 * @return A deep copy of the matrix.
		 */
		RdMatrix copy() const;

		/**
		 * @brief Moves a matrix.
		 * @return A shallow copy of the matrix, original matrix is destroyed.
		 */
		RdMatrix move();

		/**
		 * @brief Clones a matrix.
		 * @return A shallow copy of the matrix, original matrix is unchanged.
		 */
		RdMatrix clone();

		/**
		 * @brief Clones a matrix.
		 * @return A guard of the matrix.
		 */
		RdMGuard clone() const;

		/**
		 * @brief Prints matrix information.
		 * @param[in] msg Set a header identifier.
		 */
		std::string info(const std::string& msg = "") const;

		/**
		 * @brief Matrix 1-norm.
		 * @return The 1-norm of the matrix.
		 */
		real_t normOne() const;

		/**
		 * @brief Matrix infinite norm.
		 * @return The infinite norm of the matrix.
		 */
		real_t normInf() const;

		/**
		 * @brief Matrix max norm.
		 * @return The maximum norm of the matrix.
		 */
		real_t normMax() const;

		/**
		 * @brief Matrix Frobenius norm.
		 * @return The Frobenius norm of the matrix.
		 */
		real_t normFro() const;

		// 
		// not callcable from empty
		//

		/**
		 * @brief Transposes a general matrix.
		 * @return The transposed copy of the matrix.
		 */
		RdMatrix transpose() const;

		/**
		 * @brief Permutes a general matrix.
		 *
		 * Creates a permuted copy @f$ (PAQ) @f$ of the matrix @f$ A @f$.
		 *
		 * @param[in] P The left side permutation matrix.
		 * @param[in] Q The right side permutation matrix.
		 * @return The permuted copy of the matrix.
		 */
		RdMatrix permute(const PermMatrix& P, const PermMatrix& Q) const;

		/**
		 * @brief Permutes the rows of a general matrix.
		 *
		 * Creates a permuted copy @f$ (PA) @f$ of the matrix @f$ A @f$.
		 *
		 * @param[in] P The left side permutation matrix.
		 * @return The permuted copy of the matrix.
		 */
		RdMatrix permuteLeft(const PermMatrix& P) const;

		/**
		 * @brief Permutes the columns of a general matrix.
		 *
		 * Creates a permuted copy @f$ (AQ) @f$ of the matrix @f$ A @f$.
		 *
		 * @param[in] Q The right side permutation matrix.
		 * @return The permuted copy of the matrix.
		 */
		RdMatrix permuteRight(const PermMatrix& Q) const;

		/**
		 * @brief Permutes a symmetric matrix.
		 *
		 * Creates a permuted copy @f$ (PAP^T) @f$ of the matrix @f$ A @f$.
		 *
		 * @param[in] P The left and right side permutation matrix.
		 * @return The permuted copy of the matrix.
		 */
		RdMatrix permute(const PermMatrix& P) const;

		/**
		 * @brief Permutes a general matrix in-place.
		 *
		 * Replaces @f$ A @f$ with @f$ PAQ @f$.
		 *
		 * @param[in] P The left side permutation matrix.
		 * @param[in] Q The right side permutation matrix.
		 */
		void ipermute(const PermMatrix& P, const PermMatrix& Q);

		/**
		 * @brief Permutes the rows of a general matrix in-place.
		 *
		 * Replaces @f$ A @f$ with @f$ PA @f$.
		 *
		 * @param[in] P The left side permutation matrix.
		 */
		void ipermuteLeft(const PermMatrix& P);

		/**
		 * @brief Permutes the columns of a general matrix in-place.
		 *
		 * Replaces @f$ A @f$ with @f$ AQ @f$.
		 *
		 * @param[in] Q The right side permutation matrix.
		 */
		void ipermuteRight(const PermMatrix& Q);

		/**
		 * @brief Permutes a symmetric matrix in-place.
		 *
		 * Replaces @f$ A @f$ with @f$ PAP^T @f$.
		 *
		 * @param[in] P The left and right side permutation matrix.
		 */
		void ipermute(const PermMatrix& P);

		/**
		 * @brief Gets a submatrix copy.
		 *
		 * Gets a copy of a (ni x nj) block of the matrix, starting at (ibgn, jbgn)
		 *
		 * @param[in] ibgn The matrix row that the requested part begins.
		 * @param[in] jbgn The matrix column that the requested part begins.
		 * @param[in] ni The number of rows of the requested block.
		 * @param[in] nj The number of columns of the requested block.
		 * @return A copy of a portion of the matrix.
		 */
		RdMatrix block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

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
		RdMatrix rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

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
		RdMGuard rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @brief Sets a submatrix.
		 *
		 * Copies the contents of a block in the matrix, starting at (ibgn, jbgn)
		 *
		 * @param[in] ibgn The matrix row that src will be placed.
		 * @param[in] jbgn The matrix column that src will be placed.
		 * @param[in] src The block to be placed.
		 */
		void setBlock(uint_t ibgn, uint_t jbgn, const RdMatrix& src);

		// 
		// static initializers
		//

		/**
		 * @brief Creates a matrix.
		 *
		 * Creates a (nr x nc) general matrix with uninitialized values.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @return The newly created matrix.
		 */
		static RdMatrix init(uint_t nr, uint_t nc);

		/**
		 * @brief Creates a matrix.
		 *
		 * Creates a (nr x nc) matrix with uninitialized values.
		 *
		 * @param[in] ptype The matrix property.
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @return The newly created matrix.
		 */
		static RdMatrix init(prop_t ptype, uint_t nr, uint_t nc);

		/**
		 * @brief Creates a zero matrix.
		 *
		 * Creates a (nr x nc) general matrix with all values set to zero.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @return The newly created matrix.
		 */
		static RdMatrix zero(uint_t nr, uint_t nc);

		/**
		 * @brief Creates a zero matrix.
		 *
		 * Creates a (nr x nc) matrix with all values set to zero.
		 *
		 * @param[in] ptype The matrix property.
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @return The newly created matrix.
		 */
		static RdMatrix zero(prop_t ptype, uint_t nr, uint_t nc);

		/**
		 * @brief Creates a matrix with random values in (0,1).
		 *
		 * Creates a (nr x nc) general matrix with random values.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @return The newly created matrix.
		 */
		static RdMatrix random(uint_t nr, uint_t nc);

		/**
		 * @brief Creates a matrix with random values in (0,1).
		 *
		 * Creates a (nr x nc) matrix with random values.
		 *
		 * @param[in] ptype The matrix property.
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @return The newly created matrix.
		 */
		static RdMatrix random(prop_t ptype, uint_t nr, uint_t nc);

		/**
		 * @brief Creates a matrix from aux data.
		 *
		 * Creates a (nr x nc) general matrix from bulk data.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] vals The array containing the matrix values in column-major ordering.
		 * @param[in] ldv The leading dimension of the vals array.
		 * @return The newly created matrix.
		 */
		static RdMatrix wrap(uint_t nr, uint_t nc, real_t *vals, uint_t ldv);

		/**
		 * @brief Creates a matrix from aux data.
		 *
		 * Creates a (nr x nc) matrix from bulk data.
		 *
		 * @param[in] ptype The matrix property.
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] vals The array containing the matrix values in column-major ordering.
		 * @param[in] ldv The leading dimension of the vals array.
		 * @param[in] bind Binds the data to the matrix, the matrix will deallocate vals on destroy using i_free().
		 * @return The newly created matrix.
		 */
		static RdMatrix wrap(prop_t ptype, uint_t nr, uint_t nc, real_t *vals, uint_t ldv, bool bind);

		/**
		 * @brief Creates a general matrix guard from aux data.
		 *
		 * Creates a guarded (nr x nc) general matrix from bulk data.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] vals The array containing the matrix values in column-major ordering.
		 * @param[in] ldv The leading dimension of the vals array.
		 * @return The newly created guard.
		 */
		static RdMGuard wrap(uint_t nr, uint_t nc, const real_t *vals, uint_t ldv);

		/**
		 * @brief Creates a matrix guard from aux data.
		 *
		 * Creates a guarded (nr x nc) general matrix from bulk data.
		 *
		 * @param[in] ptype The matrix property.
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] vals The array containing the matrix values in column-major ordering.
		 * @param[in] ldv The leading dimension of the vals array.
		 * @return The newly created guard.
		 */
		static RdMGuard wrap(prop_t ptype, uint_t nr, uint_t nc, const real_t *vals, uint_t ldv);
};

/*-------------------------------------------------*/

/**
 * @class RdMGuard
 * @brief The double precision real dense matrix guard.
 *
 * The matrix guard class is a matrix wrapper class. 
 * Useful for protecting immutable data from being exposed.
 */
class RdMGuard : private Guard<RdMatrix> {

	public:

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty guard.
		 */
		RdMGuard();

		/**
		 * @brief Destroys the guard.
		 */
		~RdMGuard();

		/**
		 * @brief The copy constructor.
		 *
		 * Constructs a guard with a clone of the contents of other.
		 */
		RdMGuard(const RdMGuard& other);

		/**
		 * @brief The copy assignment operator.
		 *
		 * Replaces the contents of guard with a clone of the contents of other.
		 */
		RdMGuard& operator=(const RdMGuard& other);

		/**
		 * @brief The matrix being guarded.
		 * @return A constant reference to the matrix being guarded.
		 */
		const RdMatrix& mat() const;

		friend class RdMatrix;
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @brief Writes to os the contents of mat
 */
std::ostream& operator<<(std::ostream& os, const cla3p::dns::RdMatrix& mat);
/*-------------------------------------------------*/

#endif // CLA3P_DNS_RDMATRIX_HPP_
