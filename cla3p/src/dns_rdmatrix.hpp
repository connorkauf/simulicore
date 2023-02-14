#ifndef CLA3P_DNS_RDMATRIX_HPP_
#define CLA3P_DNS_RDMATRIX_HPP_

/** @file
 * The double precision real dense matrix definitions
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
 * @brief The double precision real dense matrix object
 */
class RdMatrix : private UniversalMetaTypes, public GenericObject<real_t,real_t> {

	public:
		/**
		 * @brief The default constructor
		 *
		 * Constructs an empty matrix
		 */
		RdMatrix();

		/**
		 * @brief The dimensional constructor
		 *
		 * Constructs a general (nr x nc) RdMatrix with uninitialized values
		 *
		 * @param[in] nr The number of matrix rows
		 * @param[in] nc The number of matrix columns
		 */
		RdMatrix(uint_t nr, uint_t nc);

		/**
		 * @brief The advanced constructor
		 *
		 * Constructs a (nr x nc) RdMatrix with advanced options
		 *
		 * @param[in] ptype The matrix property
		 * @param[in] nr The number of matrix rows
		 * @param[in] nc The number of matrix columns
		 * @param[in] ldim The leading dimension of the matrix
		 * @param[in] wipe Set all matrix values to zero
		 */
		RdMatrix(prop_t ptype, uint_t nr, uint_t nc, uint_t ldim, bool wipe);

		/**
		 * @brief Destroys the matrix
		 */
		~RdMatrix();

		// no copy
		RdMatrix(const RdMatrix&) = delete;
		RdMatrix& operator=(const RdMatrix&) = delete;

		/**
		 * @brief Move constructor
		 *
		 * Constructs a matrix with the contents of other, other is destroyed
		 */
		RdMatrix(RdMatrix&& other);

		/**
		 * @brief Move assignment operator
		 *
		 * Replaces the contents with those of other, other is destroyed
		 */
		RdMatrix& operator=(RdMatrix&& other);

		// 
		// non inherited args
		//

		/**
		 * @brief The matrix rows
		 * @return The number of matrix rows
		 */
		uint_t nrows() const;

		/**
		 * @brief The matrix columns
		 * @return The number of matrix columns
		 */
		uint_t ncols() const;

		/**
		 * @brief The matrix leading dimension
		 * @return The leading dimension of the matrix (ld() >= nrows())
		 */
		uint_t ld() const;

		/**
		 * @brief The matrix property
		 * @return The property that characterizes the matrix
		 */
		const Property& prop() const;

		// 
		// callcable from empty
		//

		/**
		 * @brief Copies a matrix
		 * @return A deep copy of the matrix
		 */
		RdMatrix copy() const;

		/**
		 * @brief Moves a matrix
		 * @return A shallow copy of the matrix, original matrix is destroyed
		 */
		RdMatrix move();

		/**
		 * @brief Clones a matrix
		 * @return A shallow copy of the matrix, original matrix is unchanged
		 */
		RdMatrix clone();

		/**
		 * @brief Clones a matrix
		 * @return A guard of the matrix
		 */
		RdMGuard clone() const;

		/**
		 * @brief Prints matrix information
		 * @param[in] msg Set a header identifier
		 */
		void info(const std::string& msg = "") const;

		/**
		 * @brief Matrix 1-norm
		 * @return Matrix 1-norm
		 */
		real_t normOne() const;

		/**
		 * @brief Matrix infinite norm
		 * @return Matrix infinite norm
		 */
		real_t normInf() const;

		/**
		 * @brief Matrix max norm
		 * @return Matrix max norm
		 */
		real_t normMax() const;

		/**
		 * @brief Matrix Frobenius norm
		 * @return Matrix Frobenius norm
		 */
		real_t normFro() const;

		real_t& operator()(uint_t i, uint_t j);
		const real_t& operator()(uint_t i, uint_t j) const;

		// 
		// not callcable from empty
		//

		/**
		 * @brief Transposes a matrix
		 * @return The transposed copy of the matrix
		 */
		RdMatrix transpose() const;

		/**
		 * @brief Permutes a matrix
		 * @param[in] P The left side permutation matrix
		 * @param[in] Q The right side permutation matrix
		 * @return The permuted copy of the matrix
		 */
		RdMatrix permute(const PermMatrix& P, const PermMatrix& Q) const;

		/**
		 * @brief Permutes the rows a matrix
		 * @param[in] P The left side permutation matrix
		 * @return The permuted copy of the matrix
		 */
		RdMatrix permuteLeft(const PermMatrix& P) const;

		/**
		 * @brief Permutes the columns a matrix
		 * @param[in] Q The right side permutation matrix
		 * @return The permuted copy of the matrix
		 */
		RdMatrix permuteRight(const PermMatrix& Q) const;

		/**
		 * @brief Permutes a symmetric matrix
		 * @param[in] P The left and right side permutation matrix
		 * @return The permuted copy of the matrix
		 */
		RdMatrix permute(const PermMatrix& P) const;

		/**
		 * @brief Permutes a matrix in-place
		 * @param[in] P The left side permutation matrix
		 * @param[in] Q The right side permutation matrix
		 */
		void ipermute(const PermMatrix& P, const PermMatrix& Q);

		/**
		 * @brief Permutes the rows a matrix in-place
		 * @param[in] P The left side permutation matrix
		 */
		void ipermuteLeft(const PermMatrix& P);

		/**
		 * @brief Permutes the columns a matrix in-place
		 * @param[in] Q The right side permutation matrix
		 */
		void ipermuteRight(const PermMatrix& Q);

		/**
		 * @brief Permutes a symmetric matrix in-place
		 * @param[in] P The left and right side permutation matrix
		 */
		void ipermute(const PermMatrix& P);

		/**
		 * @brief Gets a submatrix copy
		 * @param[in] ibgn The matrix row that the requested part begins
		 * @param[in] jbgn The matrix column that the requested part begins
		 * @param[in] ni The number of rows of the requested block
		 * @param[in] nj The number of columns of the requested block
		 * @return A copy of a portion of the matrix
		 */
		RdMatrix block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @brief Gets a submatrix reference
		 * @param[in] ibgn The matrix row that the requested part begins
		 * @param[in] jbgn The matrix column that the requested part begins
		 * @param[in] ni The number of rows of the requested block
		 * @param[in] nj The number of columns of the requested block
		 * @return A reference to a portion of the matrix
		 */
		RdMatrix rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

		/**
		 * @brief Gets a submatrix reference
		 * @param[in] ibgn The matrix row that the requested part begins
		 * @param[in] jbgn The matrix column that the requested part begins
		 * @param[in] ni The number of rows of the requested block
		 * @param[in] nj The number of columns of the requested block
		 * @return A reference to a portion of the matrix
		 */
		RdMGuard rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @brief Sets a submatrix
		 * @param[in] ibgn The matrix row that src will be placed
		 * @param[in] jbgn The matrix column that src will be placed
		 * @param[in] src The matrix to be placed
		 */
		void setBlock(uint_t ibgn, uint_t jbgn, const RdMatrix& src);

		// 
		// static initializers (basic)
		//

		/**
		 * @brief Creates a matrix
		 * @param[in] nr The number of matrix rows
		 * @param[in] nc The number of matrix columns
		 * @return A matrix with uninitialized values
		 */
		static RdMatrix init(uint_t nr, uint_t nc);

		/**
		 * @brief Creates a zero matrix
		 * @param[in] nr The number of matrix rows
		 * @param[in] nc The number of matrix columns
		 * @return A matrix with zero values
		 */
		static RdMatrix zero(uint_t nr, uint_t nc);

		/**
		 * @brief Creates a random matrix
		 * @param[in] nr The number of matrix rows
		 * @param[in] nc The number of matrix columns
		 * @return A matrix with random values in (0,1)
		 */
		static RdMatrix random(uint_t nr, uint_t nc);

		/**
		 * @brief Creates a matrix from aux data
		 * @param[in] nr The number of matrix rows
		 * @param[in] nc The number of matrix columns
		 * @param[in] vals The array containing the matrix values in column-major ordering
		 * @return A matrix with values from aux bulk data
		 */
		static RdMatrix wrap(uint_t nr, uint_t nc, real_t *vals);

		/**
		 * @brief Creates a matrix guard from aux data
		 * @param[in] nr The number of matrix rows
		 * @param[in] nc The number of matrix columns
		 * @param[in] vals The array containing the matrix values in column-major ordering
		 * @return A matrix guard with values from aux bulk data
		 */
		static RdMGuard wrap(uint_t nr, uint_t nc, const real_t *vals);

		// 
		// static initializers (advanced)
		//

		/**
		 * @brief Creates a matrix
		 * @param[in] ptype The matrix property
		 * @param[in] nr The number of matrix rows
		 * @param[in] nc The number of matrix columns
		 * @param[in] ldim The leading dimension of the matrix
		 * @return A matrix with uninitialized values
		 */
		static RdMatrix init(prop_t ptype, uint_t nr, uint_t nc, uint_t ldim);

		/**
		 * @brief Creates a zero matrix
		 * @param[in] ptype The matrix property
		 * @param[in] nr The number of matrix rows
		 * @param[in] nc The number of matrix columns
		 * @param[in] ldim The leading dimension of the matrix
		 * @return A matrix with zero values
		 */
		static RdMatrix zero(prop_t ptype, uint_t nr, uint_t nc, uint_t ldim);

		/**
		 * @brief Creates a random matrix
		 * @param[in] ptype The matrix property
		 * @param[in] nr The number of matrix rows
		 * @param[in] nc The number of matrix columns
		 * @param[in] ldim The leading dimension of the matrix
		 * @return A matrix with random values in (0,1)
		 */
		static RdMatrix random(prop_t ptype, uint_t nr, uint_t nc, uint_t ldim);

		/**
		 * @brief Creates a matrix from aux data
		 * @param[in] ptype The matrix property
		 * @param[in] nr The number of matrix rows
		 * @param[in] nc The number of matrix columns
		 * @param[in] vals The array containing the matrix values in column-major ordering
		 * @param[in] ldv The leading dimension of the matrix
		 * @param[in] bind Binds the data to the matrix, the matrix will deallocate the data on destroy
		 * @return A matrix with values from aux bulk data
		 */
		static RdMatrix wrap(prop_t ptype, uint_t nr, uint_t nc, real_t *vals, uint_t ldv, bool bind);

		/**
		 * @brief Creates a matrix guard from aux data
		 * @param[in] ptype The matrix property
		 * @param[in] nr The number of matrix rows
		 * @param[in] nc The number of matrix columns
		 * @param[in] vals The array containing the matrix values in column-major ordering
		 * @param[in] ldv The leading dimension of the matrix
		 * @return A matrix with values from aux bulk data
		 */
		static RdMGuard wrap(prop_t ptype, uint_t nr, uint_t nc, const real_t *vals, uint_t ldv);
};

/*-------------------------------------------------*/

/**
 * @class RdMGuard
 * @brief The double precision real dense matrix guard
 *
 * The matrix guard class is a matrix wrapper class. 
 * Useful for protecting immutable data from being exposed.
 */
class RdMGuard : private Guard<RdMatrix> {

	public:
		/**
		 * @brief The default constructor
		 *
		 * Constructs an empty guard
		 */
		RdMGuard();

		/**
		 * @brief Destroys the guard
		 */
		~RdMGuard();

		/**
		 * @brief The guard copy constructor
		 *
		 * Constructs a guard with s clonr of the contents of other
		 */
		RdMGuard(const RdMGuard& other);

		/**
		 * @brief The guard copy assignment operator
		 *
		 * Replaces the contents of guard with a clone of the contents of other
		 */
		RdMGuard& operator=(const RdMGuard& other);

		/**
		 * @brief The matrix being guarded
		 * @return The matrix being guarded
		 */
		const RdMatrix& mat() const;

		friend class RdMatrix;
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @brief Writes to os the type of mat
 */
std::ostream& operator<<(std::ostream& os, const cla3p::dns::RdMatrix& mat);

/**
 * @brief Writes to os the type of grd
 */
std::ostream& operator<<(std::ostream& os, const cla3p::dns::RdMGuard& grd);
/*-------------------------------------------------*/

#endif // CLA3P_DNS_RDMATRIX_HPP_
