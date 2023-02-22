#ifndef CLA3P_DNS_CDMATRIX_HPP_
#define CLA3P_DNS_CDMATRIX_HPP_

/** 
 * @file
 * The double precision complex dense matrix definitions.
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
class CdMGuard;

/**
 * @ingroup dense_matrix_group
 * @nosubgrouping 
 * @brief The double precision complex dense matrix object.
 */
class CdMatrix : private UniversalMetaTypes, public GenericObject<complex_t,real_t> {

	public:

		// no copy
		CdMatrix(const CdMatrix&) = delete;
		CdMatrix& operator=(const CdMatrix&) = delete;

		// -------------------------------------------------------------------------------

		/**
		 * @name Constructors
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdMatrix::RdMatrix()
		 */
		CdMatrix();

		/**
		 * @copydoc cla3p::dns::RdMatrix::RdMatrix(uint_t nr, uint_t nc)
		 */
		CdMatrix(uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::RdMatrix(prop_t ptype, uint_t nr, uint_t nc, bool wipe)
		 */
		CdMatrix(prop_t ptype, uint_t nr, uint_t nc, bool wipe);

		/**
		 * @copydoc cla3p::dns::RdMatrix::RdMatrix(RdMatrix&& other)
		 */
		CdMatrix(CdMatrix&& other);

		/**
		 * @copydoc cla3p::dns::RdMatrix::~RdMatrix()
		 */
		~CdMatrix();

		/** @} */

		// -------------------------------------------------------------------------------

		/** 
		 * @name Operators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdMatrix::operator=(RdMatrix&& other)
		 */
		CdMatrix& operator=(CdMatrix&& other);

		/**
		 * @copydoc cla3p::dns::RdMatrix::operator()()
		 */
		complex_t& operator()(uint_t i, uint_t j);

		/**
		 * @copydoc cla3p::dns::RdMatrix::operator()()
		 */
		const complex_t& operator()(uint_t i, uint_t j) const;

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
		CdMatrix copy() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::move()
		 */
		CdMatrix move();

		/**
		 * @copydoc cla3p::dns::RdMatrix::clone()
		 */
		CdMatrix clone();

		/**
		 * @copydoc cla3p::dns::RdMatrix::clone() const
		 */
		CdMGuard clone() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::scale()
		 */
		void scale(complex_t coeff);

		/**
		 * @copydoc cla3p::dns::RdMatrix::normOne()
		 */
		real_t normOne() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::normInf()
		 */
		real_t normInf() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::normMax()
		 */
		real_t normMax() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::normFro()
		 */
		real_t normFro() const;

		// 
		// not callcable from empty
		//

		/**
		 * @copydoc cla3p::dns::RdMatrix::transpose()
		 */
		CdMatrix transpose() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::permute()
		 */
		CdMatrix permute(const PermMatrix& P, const PermMatrix& Q) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::permuteLeft()
		 */
		CdMatrix permuteLeft(const PermMatrix& P) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::permuteRight()
		 */
		CdMatrix permuteRight(const PermMatrix& Q) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::permuteMirror()
		 */
		CdMatrix permuteMirror(const PermMatrix& P) const;

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
		CdMatrix block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj)
		 */
		CdMatrix rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

		/**
		 * @copydoc cla3p::dns::RdMatrix::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
		 */
		CdMGuard rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::setBlock()
		 */
		void setBlock(uint_t ibgn, uint_t jbgn, const CdMatrix& src);

		/** @} */

		// -------------------------------------------------------------------------------

		/**
		 * @name Creators/Generators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdMatrix::init(uint_t nr, uint_t nc)
		 */
		static CdMatrix init(uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::init(prop_t ptype, uint_t nr, uint_t nc)
		 */
		static CdMatrix init(prop_t ptype, uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::zero(uint_t nr, uint_t nc)
		 */
		static CdMatrix zero(uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::zero(prop_t ptype, uint_t nr, uint_t nc)
		 */
		static CdMatrix zero(prop_t ptype, uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::random(uint_t nr, uint_t nc)
		 */
		static CdMatrix random(uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::random(prop_t ptype, uint_t nr, uint_t nc)
		 */
		static CdMatrix random(prop_t ptype, uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::wrap(uint_t nr, uint_t nc, real_t *vals, uint_t ldv)
		 */
		static CdMatrix wrap(uint_t nr, uint_t nc, complex_t *vals, uint_t ldv);

		/**
		 * @copydoc cla3p::dns::RdMatrix::wrap(prop_t ptype, uint_t nr, uint_t nc, real_t *vals, uint_t ldv, bool bind)
		 */
		static CdMatrix wrap(prop_t ptype, uint_t nr, uint_t nc, complex_t *vals, uint_t ldv, bool bind);

		/**
		 * @copydoc cla3p::dns::RdMatrix::wrap(uint_t nr, uint_t nc, const real_t *vals, uint_t ldv)
		 */
		static CdMGuard wrap(uint_t nr, uint_t nc, const complex_t *vals, uint_t ldv);

		/**
		 * @copydoc cla3p::dns::RdMatrix::wrap(prop_t ptype, uint_t nr, uint_t nc, const real_t *vals, uint_t ldv)
		 */
		static CdMGuard wrap(prop_t ptype, uint_t nr, uint_t nc, const complex_t *vals, uint_t ldv);

		/** @} */
};

/*-------------------------------------------------*/

/**
 * @ingroup dense_guard_group
 * @brief The double precision complex dense matrix guard.
 *
 * The matrix guard class is a matrix wrapper class. 
 * Useful for protecting immutable data from being exposed.
 */
class CdMGuard : private Guard<CdMatrix> {

	public:

		/**
		 * @copydoc cla3p::dns::RdMGuard::RdMGuard()
		 */
		CdMGuard();

		/**
		 * @copydoc cla3p::dns::RdMGuard::~RdMGuard()
		 */
		~CdMGuard();

		/**
		 * @copydoc cla3p::dns::RdMGuard::RdMGuard(const RdMGuard& other);
		 */
		CdMGuard(const CdMGuard& other);

		/**
		 * @copydoc cla3p::dns::RdMGuard::operator=(const RdMGuard& other);
		 */
		CdMGuard& operator=(const CdMGuard& other);

		/**
		 * @copydoc cla3p::dns::RdMGuard::mat()
		 */
		const CdMatrix& mat() const;

		friend class CdMatrix;
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup stream_operator_group
 * @brief Writes to os the contents of mat
 */
std::ostream& operator<<(std::ostream& os, const cla3p::dns::CdMatrix& mat);
/*-------------------------------------------------*/

#endif // CLA3P_DNS_CDMATRIX_HPP_
