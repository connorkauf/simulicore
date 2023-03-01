#ifndef CLA3P_DNS_CFMATRIX_HPP_
#define CLA3P_DNS_CFMATRIX_HPP_

/** 
 * @file
 * The single precision complex dense matrix definitions.
 */

#include <string>

#include "../types.hpp"
#include "../generic/generic_dns.hpp"
#include "../generic/guard.hpp"
#include "../dense/dns_rfmatrix.hpp"

/*-------------------------------------------------*/
namespace cla3p {
class PermMatrix;
namespace dns {
/*-------------------------------------------------*/
class CfMGuard;

/**
 * @ingroup dense_matrix_group
 * @nosubgrouping 
 * @brief The single precision complex dense matrix object.
 */
class CfMatrix : private UniversalMetaTypes, public GenericObject<complex8_t,real4_t> {

	public:

		// no copy
		CfMatrix(const CfMatrix&) = delete;
		CfMatrix& operator=(const CfMatrix&) = delete;

		// -------------------------------------------------------------------------------

		/**
		 * @name Constructors
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdMatrix::RdMatrix()
		 */
		CfMatrix();

		/**
		 * @copydoc cla3p::dns::RdMatrix::RdMatrix(uint_t nr, uint_t nc)
		 */
		CfMatrix(uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::RdMatrix(const Property& pr, uint_t nr, uint_t nc, bool wipe)
		 */
		CfMatrix(const Property& pr, uint_t nr, uint_t nc, bool wipe);

		/**
		 * @copydoc cla3p::dns::RdMatrix::RdMatrix(RdMatrix&& other)
		 */
		CfMatrix(CfMatrix&& other);

		/**
		 * @copydoc cla3p::dns::RdMatrix::~RdMatrix()
		 */
		~CfMatrix();

		/** @} */

		// -------------------------------------------------------------------------------

		/** 
		 * @name Operators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdMatrix::operator=(RdMatrix&& other)
		 */
		CfMatrix& operator=(CfMatrix&& other);

		/**
		 * @copydoc cla3p::dns::RdMatrix::operator()()
		 */
		complex8_t& operator()(uint_t i, uint_t j);

		/**
		 * @copydoc cla3p::dns::RdMatrix::operator()()
		 */
		const complex8_t& operator()(uint_t i, uint_t j) const;

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
		CfMatrix copy() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::move()
		 */
		CfMatrix move();

		/**
		 * @copydoc cla3p::dns::RdMatrix::clone()
		 */
		CfMatrix clone();

		/**
		 * @copydoc cla3p::dns::RdMatrix::clone() const
		 */
		CfMGuard clone() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::scale()
		 */
		void scale(complex8_t coeff);

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
		CfMatrix transpose() const;

		/**
		 * @copydoc cla3p::dns::CdMatrix::ctranspose()
		 */
		CfMatrix ctranspose() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::permute()
		 */
		CfMatrix permute(const PermMatrix& P, const PermMatrix& Q) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::permuteLeft()
		 */
		CfMatrix permuteLeft(const PermMatrix& P) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::permuteRight()
		 */
		CfMatrix permuteRight(const PermMatrix& Q) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::permuteMirror()
		 */
		CfMatrix permuteMirror(const PermMatrix& P) const;

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
		CfMatrix block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj)
		 */
		CfMatrix rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

		/**
		 * @copydoc cla3p::dns::RdMatrix::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
		 */
		CfMGuard rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::setBlock()
		 */
		void setBlock(uint_t ibgn, uint_t jbgn, const CfMatrix& src);

		/**
		 * @copydoc cla3p::dns::CdMatrix::realPart()
		 */
		RfMatrix realPart() const;

		/**
		 * @copydoc cla3p::dns::CdMatrix::imagPart()
		 */
		RfMatrix imagPart() const;

		/**
		 * @copydoc cla3p::dns::CdMatrix::setRealPart()
		 */
		void setRealPart(const RfMatrix& src);

		/**
		 * @copydoc cla3p::dns::CdMatrix::setImagPart()
		 */
		void setImagPart(const RfMatrix& src);

		/**
		 * @copydoc cla3p::dns::CdMatrix::realBlock()
		 */
		RfMatrix realBlock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @copydoc cla3p::dns::CdMatrix::imagBlock()
		 */
		RfMatrix imagBlock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @copydoc cla3p::dns::CdMatrix::setRealBlock()
		 */
		void setRealBlock(uint_t ibgn, uint_t jbgn, const RfMatrix& src);

		/**
		 * @copydoc cla3p::dns::CdMatrix::setImagBlock()
		 */
		void setImagBlock(uint_t ibgn, uint_t jbgn, const RfMatrix& src);

		/** @} */

		// -------------------------------------------------------------------------------

		/**
		 * @name Creators/Generators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdMatrix::init(uint_t nr, uint_t nc)
		 */
		static CfMatrix init(uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::init(const Property& pr, uint_t nr, uint_t nc)
		 */
		static CfMatrix init(const Property& pr, uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::zero(uint_t nr, uint_t nc)
		 */
		static CfMatrix zero(uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::zero(const Property& pr, uint_t nr, uint_t nc)
		 */
		static CfMatrix zero(const Property& pr, uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::random(uint_t nr, uint_t nc)
		 */
		static CfMatrix random(uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::random(const Property& pr, uint_t nr, uint_t nc)
		 */
		static CfMatrix random(const Property& pr, uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::wrap(uint_t nr, uint_t nc, real_t *vals, uint_t ldv)
		 */
		static CfMatrix wrap(uint_t nr, uint_t nc, complex8_t *vals, uint_t ldv);

		/**
		 * @copydoc cla3p::dns::RdMatrix::wrap(const Property& pr, uint_t nr, uint_t nc, real_t *vals, uint_t ldv, bool bind)
		 */
		static CfMatrix wrap(const Property& pr, uint_t nr, uint_t nc, complex8_t *vals, uint_t ldv, bool bind);

		/**
		 * @copydoc cla3p::dns::RdMatrix::wrap(uint_t nr, uint_t nc, const real_t *vals, uint_t ldv)
		 */
		static CfMGuard wrap(uint_t nr, uint_t nc, const complex8_t *vals, uint_t ldv);

		/**
		 * @copydoc cla3p::dns::RdMatrix::wrap(const Property& pr, uint_t nr, uint_t nc, const real_t *vals, uint_t ldv)
		 */
		static CfMGuard wrap(const Property& pr, uint_t nr, uint_t nc, const complex8_t *vals, uint_t ldv);

		/** @} */
};

/*-------------------------------------------------*/

/**
 * @ingroup dense_guard_group
 * @brief The single precision complex dense matrix guard.
 *
 * The matrix guard class is a matrix wrapper class. 
 * Useful for protecting immutable data from being exposed.
 */
class CfMGuard : private Guard<CfMatrix> {

	public:

		/**
		 * @copydoc cla3p::dns::RdMGuard::RdMGuard()
		 */
		CfMGuard();

		/**
		 * @copydoc cla3p::dns::RdMGuard::~RdMGuard()
		 */
		~CfMGuard();

		/**
		 * @copydoc cla3p::dns::RdMGuard::RdMGuard(const RdMGuard& other);
		 */
		CfMGuard(const CfMGuard& other);

		/**
		 * @copydoc cla3p::dns::RdMGuard::operator=(const RdMGuard& other);
		 */
		CfMGuard& operator=(const CfMGuard& other);

		/**
		 * @copydoc cla3p::dns::RdMGuard::mat()
		 */
		const CfMatrix& mat() const;

		friend class CfMatrix;
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup stream_operator_group
 * @brief Writes to os the contents of mat
 */
std::ostream& operator<<(std::ostream& os, const cla3p::dns::CfMatrix& mat);
/*-------------------------------------------------*/

#endif // CLA3P_DNS_CFMATRIX_HPP_
