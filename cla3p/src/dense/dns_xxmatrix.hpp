#ifndef CLA3P_DNS_XXMATRIX_HPP_
#define CLA3P_DNS_XXMATRIX_HPP_

#include <string>

#include "../generic/array2d.hpp"
#include "../generic/guard.hpp"
#include "../perms.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief A dense matrix class.
 */
template <typename T_Scalar, typename T_RScalar, typename T_ReturnType>
class XxMatrix : public Array2D<T_Scalar> {

	public:

		// no copy
		XxMatrix(const XxMatrix<T_Scalar,T_RScalar,T_ReturnType>&) = delete;
		XxMatrix<T_Scalar,T_RScalar,T_ReturnType>& operator=(const XxMatrix<T_Scalar,T_RScalar,T_ReturnType>&) = delete;

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
		XxMatrix(XxMatrix<T_Scalar,T_RScalar,T_ReturnType>&& other);

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
		XxMatrix<T_Scalar,T_RScalar,T_ReturnType>& operator=(XxMatrix<T_Scalar,T_RScalar,T_ReturnType>&& other);

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
		 * Sets all entries of the matrix to a single value.
		 *
		 * @param[in] val The value to be set.
		 */
		void operator=(T_Scalar val);

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
		 * @brief Clears the matrix.
		 *
		 * Deallocates owned data and resets all members.
		 */
		void clear();

		/**
		 * @brief Fills the matrix with a value.
		 *
		 * Sets all entries of the matrix to a single value.
		 *
		 * @param[in] val The value to be set.
		 */
		void fill(T_Scalar val);

		/**
		 * @brief Prints matrix information.
		 * @param[in] msg Set a header identifier.
		 */
		std::string info(const std::string& msg = "") const;

		/**
		 * @brief Prints the contents of the matrix.
		 * @param[in] nsd The number of significant digits (for real/complex types only, otherwise ignored).
		 */
		void print(uint_t nsd = 3) const;

		/**
		 * @brief Prints the contents of the matrix to a string.
		 * @param[in] nsd The number of significant digits (for real/complex types only, otherwise ignored).
		 * @return The string containing the formatted numerical values of the object.
		 */
		std::string toString(uint_t nsd = 3) const;

		/**
		 * @brief Copies a matrix.
		 * @return A deep copy of the matrix.
		 */
		T_ReturnType copy() const;

		/**
		 * @brief Clones a matrix.
		 * @return A shallow copy of the matrix, original matrix is unchanged.
		 */
		T_ReturnType rcopy();

		/**
		 * @brief Clones a matrix.
		 * @return A guard of the matrix.
		 */
		Guard<T_ReturnType> rcopy() const;

		/**
		 * @brief Moves a matrix.
		 * @return A shallow copy of the matrix, original matrix is destroyed.
		 */
		T_ReturnType move();

		/**
		 * @brief Scales the matrix by coeff.
		 * @param[in] val The scaling coefficient.
		 */
		void scale(T_Scalar val);

		/**
		 * @brief Matrix 1-norm.
		 * @return The 1-norm of the matrix.
		 */
		T_RScalar normOne() const;

		/**
		 * @brief Matrix infinite norm.
		 * @return The infinite norm of the matrix.
		 */
		T_RScalar normInf() const;

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

#if 0

		/**
		 * @brief Permutes the entries of a vector
		 *
		 * Creates a permuted copy @f$ (PX) @f$ of the vector @f$ X @f$.
		 *
		 * @param[in] P The left side permutation matrix.
		 * @return The permuted copy of the vector.
		 */
		T_ReturnType permute(const PiMatrix& P) const;

		/**
		 * @brief Permutes the entries of a vector in-place.
		 *
		 * Replaces @f$ X @f$ with @f$ PX @f$.
		 *
		 * @param[in] P The left side permutation matrix.
		 */
		void ipermute(const PiMatrix& P);

		/**
		 * @brief Gets a subvector copy.
		 *
		 * Gets a copy of a ni-sized block of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A copy of a portion of the vector.
		 */
		T_ReturnType block(uint_t ibgn, uint_t ni) const;

		/**
		 * @brief Gets a subvector reference.
		 *
		 * Gets a reference of a ni-sized block of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A reference to a portion of the vector.
		 */
		T_ReturnType rblock(uint_t ibgn, uint_t ni);

		/**
		 * @brief Gets a subvector reference.
		 *
		 * Gets a reference of a ni-sized block of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A guarded reference to a portion of the vector.
		 */
		Guard<T_ReturnType> rblock(uint_t ibgn, uint_t ni) const;

		/**
		 * @brief Sets a subvector.
		 *
		 * Copies the contents of src in the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector index that src will be placed.
		 * @param[in] src The vector to be placed.
		 */
		void setBlock(uint_t ibgn, const XxVector<T_Scalar,T_RScalar,T_ReturnType>& src);

#endif

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
		static T_ReturnType init(uint_t nr, uint_t nc, const Property& pr = defaultProperty());

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
		static T_ReturnType random(uint_t nr, uint_t nc, const Property& pr = defaultProperty());

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
		static T_ReturnType wrap(uint_t nr, uint_t nc, T_Scalar *vals, uint_t ldv, bool bind, const Property& pr = defaultProperty());

		/**
		 * @brief Creates a matrix guard from aux data.
		 *
		 * Creates a (nr x nc) matrix from bulk data.
		 *
		 * @param[in] nr The number of matrix rows.
		 * @param[in] nc The number of matrix columns.
		 * @param[in] vals The array containing the matrix values in column-major ordering.
		 * @param[in] ldv The leading dimension of the vals array.
		 * @param[in] bind Binds the data to the matrix, the matrix will deallocate vals on destroy using i_free().
		 * @param[in] pr The matrix property.
		 * @return The newly created guard.
		 */
		static Guard<T_ReturnType> wrap(uint_t nr, uint_t nc, const T_Scalar *vals, uint_t ldv, const Property& pr = defaultProperty());

		/** @} */
	
	private:
		Property m_prop;

		void defaults();

		void setProp(const Property&);

		void wrapper(const Property& pr, uint_t nr, uint_t nc, T_Scalar *vals, uint_t ldv, bool bind);
		void wrapperExtras(const Property& pr);

};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup dense_matrices
 * @brief Writes to os the contents of mat.
 */
template <typename T_Scalar, typename T_RScalar, typename T_ReturnType>
std::ostream& operator<<(std::ostream& os, const cla3p::dns::XxMatrix<T_Scalar,T_RScalar,T_ReturnType>& mat)
{
  os << mat.toString();
  return os;
}

#endif // CLA3P_DNS_XXMATRIX_HPP_
