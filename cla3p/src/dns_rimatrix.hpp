#ifndef CLA3P_DNS_RIMATRIX_HPP_
#define CLA3P_DNS_RIMATRIX_HPP_

/** @file
 * The integer dense matrix definitions.
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
class RiMGuard;

/**
 * @class RiMatrix
 * @nosubgrouping 
 * @brief The integer dense matrix object.
 */
class RiMatrix : private UniversalMetaTypes, public GenericObject<int_t,int_t> {

	public:

		/**
		 * @copydoc cla3p::dns::RdMatrix::RdMatrix()
		 */
		RiMatrix();

		/**
		 * @copydoc cla3p::dns::RdMatrix::RdMatrix(uint_t nr, uint_t nc)
		 */
		RiMatrix(uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::RdMatrix(prop_t ptype, uint_t nr, uint_t nc, bool wipe)
		 */
		RiMatrix(prop_t ptype, uint_t nr, uint_t nc, bool wipe);

		/**
		 * @copydoc cla3p::dns::RdMatrix::~RdMatrix()
		 */
		~RiMatrix();

		// no copy
		RiMatrix(const RiMatrix&) = delete;
		RiMatrix& operator=(const RiMatrix&) = delete;

		/**
		 * @copydoc cla3p::dns::RdMatrix::RdMatrix(RdMatrix&& other)
		 */
		RiMatrix(RiMatrix&& other);

		/** 
		 * @name Operators
		 */

		/** @{ */

		/**
		 * @copydoc cla3p::dns::RdMatrix::operator=(RdMatrix&& other)
		 */
		RiMatrix& operator=(RiMatrix&& other);

		/**
		 * @copydoc cla3p::dns::RdMatrix::operator()()
		 */
		int_t& operator()(uint_t i, uint_t j);

		/**
		 * @copydoc cla3p::dns::RdMatrix::operator()()
		 */
		const int_t& operator()(uint_t i, uint_t j) const;

		/** @} */

		// 
		// non inherited args
		//

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

		// 
		// callcable from empty
		//

		/**
		 * @copydoc cla3p::dns::RdMatrix::scale()
		 */
		void scale(int_t coeff);

		/**
		 * @copydoc cla3p::dns::RdMatrix::copy()
		 */
		RiMatrix copy() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::move()
		 */
		RiMatrix move();

		/**
		 * @copydoc cla3p::dns::RdMatrix::clone()
		 */
		RiMatrix clone();

		/**
		 * @copydoc cla3p::dns::RdMatrix::clone() const
		 */
		RiMGuard clone() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::info()
		 */
		std::string info(const std::string& msg = "") const;

		// 
		// not callcable from empty
		//

		/**
		 * @copydoc cla3p::dns::RdMatrix::transpose()
		 */
		RiMatrix transpose() const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::permute(const PermMatrix& P, const PermMatrix& Q)
		 */
		RiMatrix permute(const PermMatrix& P, const PermMatrix& Q) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::permuteLeft()
		 */
		RiMatrix permuteLeft(const PermMatrix& P) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::permuteRight()
		 */
		RiMatrix permuteRight(const PermMatrix& Q) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::permuteMirror(const PermMatrix& P)
		 */
		RiMatrix permuteMirror(const PermMatrix& P) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::ipermute(const PermMatrix& P, const PermMatrix& Q)
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
		 * @copydoc cla3p::dns::RdMatrix::ipermute(const PermMatrix& P)
		 */
		void ipermuteMirror(const PermMatrix& P);

		/**
		 * @copydoc cla3p::dns::RdMatrix::block()
		 */
		RiMatrix block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj)
		 */
		RiMatrix rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);

		/**
		 * @copydoc cla3p::dns::RdMatrix::rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
		 */
		RiMGuard rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		/**
		 * @copydoc cla3p::dns::RdMatrix::setBlock()
		 */
		void setBlock(uint_t ibgn, uint_t jbgn, const RiMatrix& src);

		// 
		// static initializers
		//

		/**
		 * @copydoc cla3p::dns::RdMatrix::init(uint_t nr, uint_t nc)
		 */
		static RiMatrix init(uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::init(prop_t ptype, uint_t nr, uint_t nc)
		 */
		static RiMatrix init(prop_t ptype, uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::zero(uint_t nr, uint_t nc)
		 */
		static RiMatrix zero(uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::zero(prop_t ptype, uint_t nr, uint_t nc)
		 */
		static RiMatrix zero(prop_t ptype, uint_t nr, uint_t nc);

		/**
		 * @brief Creates a matrix with random values in (0,100).
		 * @copydetails cla3p::dns::RdMatrix::random(uint_t nr, uint_t nc)
		 */
		static RiMatrix random(uint_t nr, uint_t nc);

		/**
		 * @brief Creates a matrix with random values in (0,100).
		 * @copydetails cla3p::dns::RdMatrix::random(prop_t ptype, uint_t nr, uint_t nc)
		 */
		static RiMatrix random(prop_t ptype, uint_t nr, uint_t nc);

		/**
		 * @copydoc cla3p::dns::RdMatrix::wrap(uint_t nr, uint_t nc, real_t *vals, uint_t ldv)
		 */
		static RiMatrix wrap(uint_t nr, uint_t nc, int_t *vals, uint_t ldv);

		/**
		 * @copydoc cla3p::dns::RdMatrix::wrap(prop_t ptype, uint_t nr, uint_t nc, real_t *vals, uint_t ldv, bool bind)
		 */
		static RiMatrix wrap(prop_t ptype, uint_t nr, uint_t nc, int_t *vals, uint_t ldv, bool bind);

		/**
		 * @copydoc cla3p::dns::RdMatrix::wrap(uint_t nr, uint_t nc, const real_t *vals, uint_t ldv)
		 */
		static RiMGuard wrap(uint_t nr, uint_t nc, const int_t *vals, uint_t ldv);

		/**
		 * @copydoc cla3p::dns::RdMatrix::wrap(prop_t ptype, uint_t nr, uint_t nc, const real_t *vals, uint_t ldv)
		 */
		static RiMGuard wrap(prop_t ptype, uint_t nr, uint_t nc, const int_t *vals, uint_t ldv);
};

/*-------------------------------------------------*/

/**
 * @class RiMGuard
 * @brief The integer dense matrix guard.
 *
 * The matrix guard class is a matrix wrapper class. 
 * Useful for protecting immutable data from being exposed.
 */
class RiMGuard : private Guard<RiMatrix> {

	public:

		/**
		 * @copydoc cla3p::dns::RdMGuard::RdMGuard()
		 */
		RiMGuard();

		/**
		 * @copydoc cla3p::dns::RdMGuard::~RdMGuard()
		 */
		~RiMGuard();

		/**
		 * @copydoc cla3p::dns::RdMGuard::RdMGuard(const RdMGuard& other);
		 */
		RiMGuard(const RiMGuard& other);

		/**
		 * @copydoc cla3p::dns::RdMGuard::operator=(const RdMGuard& other);
		 */
		RiMGuard& operator=(const RiMGuard& other);

		/**
		 * @copydoc cla3p::dns::RdMGuard::mat()
		 */
		const RiMatrix& mat() const;

		friend class RiMatrix;
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @copydoc cla3p::dns::RdMGuard::operator<<()
 */
std::ostream& operator<<(std::ostream& os, const cla3p::dns::RiMatrix& mat);
/*-------------------------------------------------*/

#endif // CLA3P_DNS_RIMATRIX_HPP_
