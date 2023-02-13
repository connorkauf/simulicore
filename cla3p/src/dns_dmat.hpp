#ifndef CLA3P_DNS_DMAT_HPP_
#define CLA3P_DNS_DMAT_HPP_

#include <string>

#include "types.hpp"
#include "generic/generic_dns.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace prm { class pMat; }
namespace dns {
/*-------------------------------------------------*/
class dMGuard;

/**
 * @brief The double precision real dense matrix object
 */
class dMat : private UniversalMetaTypes, public GenericObject<real_t,real_t> {

	public:
		/**
		 * @brief The default constructor
		 */
		dMat();

		/**
		 * @brief The dimensional constructor
		 * @param[in] nrows The number of matrix rows
		 * @param[in] ncols The number of matrix columns
		 */
		dMat(uint_t nrows, uint_t ncols);

		/**
		 * @brief The advanced constructor
		 * @param[in] ptype The matrix property
		 * @param[in] nrows The number of matrix rows
		 * @param[in] ncols The number of matrix columns
		 * @param[in] ld The leading dimension of the matrix
		 * @param[in] wipe Set all matrix values to zero
		 */
		dMat(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld, bool wipe);

		~dMat();

		// no copy
		dMat(const dMat&) = delete;
		dMat& operator=(const dMat&) = delete;

		// move
		dMat(dMat&&);
		dMat& operator=(dMat&&);

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
		dMat copy() const;

		/**
		 * @brief Moves a matrix
		 * @return A shallow copy of the matrix, original matrix is destroyed
		 */
		dMat move();

		/**
		 * @brief Clones a matrix
		 * @return A shallow copy of the matrix
		 */
		dMat clone();

		/**
		 * @brief Clones a matrix
		 * @return A guard of the matrix
		 */
		dMGuard clone() const;

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
		 * @return The transpose of the matrix
		 */
		dMat transpose() const;

		/**
		 * @brief Permutes a matrix
		 * @param[in] P The left side permutation matrix
		 * @param[in] Q The right side permutation matrix
		 * @return The permuted copy of the matrix
		 */
		dMat permute(const prm::pMat& P, const prm::pMat& Q) const;

		/**
		 * @brief Permutes the rows a matrix
		 * @param[in] P The left side permutation matrix
		 * @return The permuted copy of the matrix
		 */
		dMat permuteLeft(const prm::pMat& P) const;

		/**
		 * @brief Permutes the columns a matrix
		 * @param[in] Q The right side permutation matrix
		 * @return The permuted copy of the matrix
		 */
		dMat permuteRight(const prm::pMat& Q) const;

		/**
		 * @brief Permutes a symmetric matrix
		 * @param[in] P The left and right side permutation matrix
		 * @return The permuted copy of the matrix
		 */
		dMat permute(const prm::pMat& P) const;

		/**
		 * @brief Permutes a matrix in-place
		 * @param[in] P The left side permutation matrix
		 * @param[in] Q The right side permutation matrix
		 */
		void ipermute(const prm::pMat& P, const prm::pMat& Q);

		/**
		 * @brief Permutes the rows a matrix in-place
		 * @param[in] P The left side permutation matrix
		 */
		void ipermuteLeft(const prm::pMat& P);

		/**
		 * @brief Permutes the columns a matrix in-place
		 * @param[in] Q The right side permutation matrix
		 */
		void ipermuteRight(const prm::pMat& Q);

		/**
		 * @brief Permutes a symmetric matrix in-place
		 * @param[in] P The left and right side permutation matrix
		 */
		void ipermute(const prm::pMat& P);

		/**
		 * @brief Gets a submatrix copy
		 * @param[in] ibgn The matrix row that the requested part begins
		 * @param[in] jbgn The matrix column that the requested part begins
		 * @param[in] ni The number of rows of the requested block
		 * @param[in] nj The number of columns of the requested block
		 * @return A copy of a portion of the matrix
		 */
		dMat block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @brief Gets a submatrix reference
		 * @param[in] ibgn The matrix row that the requested part begins
		 * @param[in] jbgn The matrix column that the requested part begins
		 * @param[in] ni The number of rows of the requested block
		 * @param[in] nj The number of columns of the requested block
		 * @return A reference of a portion of the matrix
		 */
		dMat rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

		/**
		 * @brief Gets a submatrix reference
		 * @param[in] ibgn The matrix row that the requested part begins
		 * @param[in] jbgn The matrix column that the requested part begins
		 * @param[in] ni The number of rows of the requested block
		 * @param[in] nj The number of columns of the requested block
		 * @return A reference of a portion of the matrix
		 */
		dMGuard rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @brief Sets a submatrix
		 * @param[in] ibgn The matrix row that src will be placed
		 * @param[in] jbgn The matrix column that src will be placed
		 * @param[in] src The matrix to be placed
		 */
		void setBlock(uint_t ibgn, uint_t jbgn, const dMat& src);

		// 
		// static initializers (basic)
		//

		/**
		 * @brief Creates a matrix
		 * @param[in] nrows The number of matrix rows
		 * @param[in] ncols The number of matrix columns
		 * @return A matrix with uninitialized values
		 */
		static dMat init(uint_t nrows, uint_t ncols);

		/**
		 * @brief Creates a zero matrix
		 * @param[in] nrows The number of matrix rows
		 * @param[in] ncols The number of matrix columns
		 * @return A matrix with zero values
		 */
		static dMat zero(uint_t nrows, uint_t ncols);

		/**
		 * @brief Creates a random matrix
		 * @param[in] nrows The number of matrix rows
		 * @param[in] ncols The number of matrix columns
		 * @return A matrix with random values in (0,1)
		 */
		static dMat random(uint_t nrows, uint_t ncols);

		/**
		 * @brief Creates a matrix from aux data
		 * @param[in] nrows The number of matrix rows
		 * @param[in] ncols The number of matrix columns
		 * @param[in] values The array containing the matrix values in column-major ordering
		 * @return A matrix with values from aux bulk data
		 */
		static dMat wrap(uint_t nrows, uint_t ncols, real_t *values);

		/**
		 * @brief Creates a matrix guard from aux data
		 * @param[in] nrows The number of matrix rows
		 * @param[in] ncols The number of matrix columns
		 * @param[in] values The array containing the matrix values in column-major ordering
		 * @return A matrix guard with values from aux bulk data
		 */
		static dMGuard wrap(uint_t nrows, uint_t ncols, const real_t *values);

		// 
		// static initializers (advanced)
		//

		/**
		 * @brief Creates a matrix
		 * @param[in] ptype The matrix property
		 * @param[in] nrows The number of matrix rows
		 * @param[in] ncols The number of matrix columns
		 * @param[in] ld The leading dimension of the matrix
		 * @return A matrix with uninitialized values
		 */
		static dMat init(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld);

		/**
		 * @brief Creates a zero matrix
		 * @param[in] ptype The matrix property
		 * @param[in] nrows The number of matrix rows
		 * @param[in] ncols The number of matrix columns
		 * @param[in] ld The leading dimension of the matrix
		 * @return A matrix with zero values
		 */
		static dMat zero(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld);

		/**
		 * @brief Creates a random matrix
		 * @param[in] ptype The matrix property
		 * @param[in] nrows The number of matrix rows
		 * @param[in] ncols The number of matrix columns
		 * @param[in] ld The leading dimension of the matrix
		 * @return A matrix with random values in (0,1)
		 */
		static dMat random(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld);

		/**
		 * @brief Creates a matrix from aux data
		 * @param[in] ptype The matrix property
		 * @param[in] nrows The number of matrix rows
		 * @param[in] ncols The number of matrix columns
		 * @param[in] values The array containing the matrix values in column-major ordering
		 * @param[in] ld The leading dimension of the matrix
		 * @param[in] bind Binds the data to the matrix, the matrix will deallocate the data on destroy
		 * @return A matrix with values from aux bulk data
		 */
		static dMat wrap(prop_t ptype, uint_t nrows, uint_t ncols, real_t *values, uint_t ld, bool bind);

		/**
		 * @brief Creates a matrix guard from aux data
		 * @param[in] ptype The matrix property
		 * @param[in] nrows The number of matrix rows
		 * @param[in] ncols The number of matrix columns
		 * @param[in] values The array containing the matrix values in column-major ordering
		 * @param[in] ld The leading dimension of the matrix
		 * @return A matrix with values from aux bulk data
		 */
		static dMGuard wrap(prop_t ptype, uint_t nrows, uint_t ncols, const real_t *values, uint_t ld);
};

/*-------------------------------------------------*/

/**
 * @brief The double precision real dense matrix guard
 */
class dMGuard : private GenericGuard<dMat> {

	public:
		dMGuard();
		~dMGuard();
		dMGuard(const dMGuard&);
		dMGuard& operator=(const dMGuard&);

		/**
		 * @brief The matrix being guarded
		 * @return The matrix being guarded
		 */
		const dMat& mat() const;

		friend class dMat;
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
std::ostream& operator<<(std::ostream&, const cla3p::dns::dMat&);
/*-------------------------------------------------*/

#endif // CLA3P_DNS_DMAT_HPP_
