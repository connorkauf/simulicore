#ifndef CLA3P_DNS_RFMATRIX_HPP_
#define CLA3P_DNS_RFMATRIX_HPP_

/** 
 * @file
 * The single precision real dense matrix definitions.
 */

#include <string>

#include "../types.hpp"
#include "../generic/generic_dns.hpp"
#include "../generic/guard.hpp"

/*-------------------------------------------------*/
namespace cla3p {
class PermMatrix;
namespace dns {
/*-------------------------------------------------*/
class RfMGuard;

/**
 * @ingroup dense_matrix_group
 * @nosubgrouping 
 * @brief The single precision real dense matrix object.
 */
class RfMatrix : private UniversalMetaTypes, public GenericObject<real4_t,real4_t> {

	public:

		// no copy
		RfMatrix(const RfMatrix&) = delete;
		RfMatrix& operator=(const RfMatrix&) = delete;

		// -------------------------------------------------------------------------------

		/**
		 * @name Constructors
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdMatrix::RdMatrix()
		 */
		RfMatrix();

		/**
		 * @copydoc cla3p::dns::RdMatrix::RdMatrix(uint_t nr, uint_t nc)
		 */
		RfMatrix(uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::RdMatrix(const Property& pr, uint_t nr, uint_t nc, bool wipe)
		 */
		RfMatrix(const Property& pr, uint_t nr, uint_t nc, bool wipe);

		/**
		 * @copydoc cla3p::dns::RdMatrix::RdMatrix(RdMatrix&& other)
		 */
		RfMatrix(RfMatrix&& other);

		/**
		 * @copydoc cla3p::dns::RdMatrix::~RdMatrix()
		 */
		~RfMatrix();

		/** @} */

		// -------------------------------------------------------------------------------

		/** 
		 * @name Operators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdMatrix::operator=(RdMatrix&& other)
		 */
		RfMatrix& operator=(RfMatrix&& other);

		/**
		 * @copydoc cla3p::dns::RdMatrix::operator()()
		 */
		real4_t& operator()(uint_t i, uint_t j);

		/**
		 * @copydoc cla3p::dns::RdMatrix::operator()()
		 */
		const real4_t& operator()(uint_t i, uint_t j) const;

		/** @} */

		// -------------------------------------------------------------------------------

		/**
		 * @name Arguments
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdMatrix::nrows()
		 */
		uint_t nrows() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::ncols()
		 */
		uint_t ncols() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::ld()
		 */
		uint_t ld() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::prop()
		 */
		const Property& prop() const;

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
		 * @copydoc cla3p::dns::RdMatrix::info()
		 */
		std::string info(const std::string& msg = "") const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::copy()
		 */
		RfMatrix copy() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::move()
		 */
		RfMatrix move();

		/**
		 * @copydoc cla3p::dns::RdMatrix::clone()
		 */
		RfMatrix clone();

		/**
		 * @copydoc cla3p::dns::RdMatrix::clone() const
		 */
		RfMGuard clone() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::scale()
		 */
		void scale(real4_t coeff);

		/**
		 * @copydoc cla3p::dns::RdMatrix::normOne()
		 */
		real4_t normOne() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::normInf()
		 */
		real4_t normInf() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::normMax()
		 */
		real4_t normMax() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::normFro()
		 */
		real4_t normFro() const;

		// 
		// not callcable from empty
		//

		/**
		 * @copydoc cla3p::dns::RdMatrix::transpose()
		 */
		RfMatrix transpose() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::permute()
		 */
		RfMatrix permute(const PermMatrix& P, const PermMatrix& Q) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::permuteLeft()
		 */
		RfMatrix permuteLeft(const PermMatrix& P) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::permuteRight()
		 */
		RfMatrix permuteRight(const PermMatrix& Q) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::permuteMirror()
		 */
		RfMatrix permuteMirror(const PermMatrix& P) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::ipermute()
		 */
		void ipermute(const PermMatrix& P, const PermMatrix& Q);

		/**
		 * @copydoc cla3p::dns::RdMatrix::ipermuteLeft()
		 */
		void ipermuteLeft(const PermMatrix& P);

		/**
		 * @copydoc cla3p::dns::RdMatrix::ipermuteRight()
		 */
		void ipermuteRight(const PermMatrix& Q);

		/**
		 * @copydoc cla3p::dns::RdMatrix::ipermuteMirror()
		 */
		void ipermuteMirror(const PermMatrix& P);

		/**
		 * @copydoc cla3p::dns::RdMatrix::block()
		 */
		RfMatrix block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj)
		 */
		RfMatrix rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

		/**
		 * @copydoc cla3p::dns::RdMatrix::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
		 */
		RfMGuard rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::setBlock()
		 */
		void setBlock(uint_t ibgn, uint_t jbgn, const RfMatrix& src);

		/** @} */

		// -------------------------------------------------------------------------------

		/**
		 * @name Creators/Generators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdMatrix::init(uint_t nr, uint_t nc)
		 */
		static RfMatrix init(uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::init(const Property& pr, uint_t nr, uint_t nc)
		 */
		static RfMatrix init(const Property& pr, uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::zero(uint_t nr, uint_t nc)
		 */
		static RfMatrix zero(uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::zero(const Property& pr, uint_t nr, uint_t nc)
		 */
		static RfMatrix zero(const Property& pr, uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::random(uint_t nr, uint_t nc)
		 */
		static RfMatrix random(uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::random(const Property& pr, uint_t nr, uint_t nc)
		 */
		static RfMatrix random(const Property& pr, uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::wrap(uint_t nr, uint_t nc, real_t *vals, uint_t ldv)
		 */
		static RfMatrix wrap(uint_t nr, uint_t nc, real4_t *vals, uint_t ldv);

		/**
		 * @copydoc cla3p::dns::RdMatrix::wrap(const Property& pr, uint_t nr, uint_t nc, real_t *vals, uint_t ldv, bool bind)
		 */
		static RfMatrix wrap(const Property& pr, uint_t nr, uint_t nc, real4_t *vals, uint_t ldv, bool bind);

		/**
		 * @copydoc cla3p::dns::RdMatrix::wrap(uint_t nr, uint_t nc, const real_t *vals, uint_t ldv)
		 */
		static RfMGuard wrap(uint_t nr, uint_t nc, const real4_t *vals, uint_t ldv);

		/**
		 * @copydoc cla3p::dns::RdMatrix::wrap(const Property& pr, uint_t nr, uint_t nc, const real_t *vals, uint_t ldv)
		 */
		static RfMGuard wrap(const Property& pr, uint_t nr, uint_t nc, const real4_t *vals, uint_t ldv);

		/** @} */
};

/*-------------------------------------------------*/

/**
 * @ingroup dense_guard_group
 * @brief The single precision real dense matrix guard.
 *
 * The matrix guard class is a matrix wrapper class. 
 * Useful for protecting immutable data from being exposed.
 */
class RfMGuard : private Guard<RfMatrix> {

	public:

		/**
		 * @copydoc cla3p::dns::RdMGuard::RdMGuard()
		 */
		RfMGuard();

		/**
		 * @copydoc cla3p::dns::RdMGuard::~RdMGuard()
		 */
		~RfMGuard();

		/**
		 * @copydoc cla3p::dns::RdMGuard::RdMGuard(const RdMGuard& other);
		 */
		RfMGuard(const RfMGuard& other);

		/**
		 * @copydoc cla3p::dns::RdMGuard::operator=(const RdMGuard& other);
		 */
		RfMGuard& operator=(const RfMGuard& other);

		/**
		 * @copydoc cla3p::dns::RdMGuard::mat()
		 */
		const RfMatrix& mat() const;

		friend class RfMatrix;
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup stream_operator_group
 * @brief Writes to os the contents of mat
 */
std::ostream& operator<<(std::ostream& os, const cla3p::dns::RfMatrix& mat);
/*-------------------------------------------------*/

#endif // CLA3P_DNS_RFMATRIX_HPP_
