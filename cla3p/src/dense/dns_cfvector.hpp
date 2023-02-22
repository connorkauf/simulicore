#ifndef CLA3P_DNS_CFVECTOR_HPP_
#define CLA3P_DNS_CFVECTOR_HPP_

/** 
 * @file
 * The single precision complex dense vector definitions.
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
class CfVGuard;

/**
 * @ingroup dense_vector_group
 * @nosubgrouping 
 * @brief The single precision complex dense vector object.
 */
class CfVector : private UniversalMetaTypes, public GenericObject<complex8_t,real4_t> {

	public:

		// no copy
		CfVector(const CfVector&) = delete;
		CfVector& operator=(const CfVector&) = delete;

		// -------------------------------------------------------------------------------

		/** 
		 * @name Constructors
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdVector::RdVector()
		 */
		CfVector();

		/**
		 * @copydoc cla3p::dns::RdVector::RdVector(uint_t n)
		 */
		CfVector(uint_t n);

		/**
		 * @copydoc cla3p::dns::RdVector::RdVector(RdVector&& other)
		 */
		CfVector(CfVector&& other);

		/**
		 * @copydoc cla3p::dns::RdVector::~RdVector()
		 */
		~CfVector();

		/** @} */

		// -------------------------------------------------------------------------------

		/** 
		 * @name Operators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdVector::operator=(RdVector&& other)
		 */
		CfVector& operator=(CfVector&& other);

		/**
		 * @copydoc cla3p::dns::RdVector::operator()()
		 */
		complex8_t& operator()(uint_t i);

		/**
		 * @copydoc cla3p::dns::RdVector::operator()()
		 */
		const complex8_t& operator()(uint_t i) const;

		/** @} */

		// -------------------------------------------------------------------------------

		/** 
		 * @name Arguments
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdVector::size()
		 */
		uint_t size() const;

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
		 * @copydoc cla3p::dns::RdVector::info()
		 */
		std::string info(const std::string& msg = "") const;

		/**
		 * @copydoc cla3p::dns::RdVector::copy()
		 */
		CfVector copy() const;

		/**
		 * @copydoc cla3p::dns::RdVector::move()
		 */
		CfVector move();

		/**
		 * @copydoc cla3p::dns::RdVector::clone()
		 */
		CfVector clone();

		/**
		 * @copydoc cla3p::dns::RdVector::clone() const
		 */
		CfVGuard clone() const;

		/**
		 * @copydoc cla3p::dns::RdVector::scale()
		 */
		void scale(complex8_t coeff);

		/**
		 * @copydoc cla3p::dns::RdVector::normOne()
		 */
		real4_t normOne() const;

		/**
		 * @copydoc cla3p::dns::RdVector::normInf()
		 */
		real4_t normInf() const;

		/**
		 * @copydoc cla3p::dns::RdVector::normEuc()
		 */
		real4_t normEuc() const;

		// 
		// not callcable from empty
		//

		/**
		 * @copydoc cla3p::dns::RdVector::permuteLeft()
		 */
		CfVector permuteLeft(const PermMatrix& P) const;

		/**
		 * @copydoc cla3p::dns::RdVector::ipermuteLeft()
		 */
		void ipermuteLeft(const PermMatrix& P);

		/**
		 * @copydoc cla3p::dns::RdVector::block()
		 */
		CfVector block(uint_t ibgn, uint_t ni) const;

		/**
		 * @copydoc cla3p::dns::RdVector::rblock(uint_t ibgn, uint_t ni)
		 */
		CfVector rblock(uint_t ibgn, uint_t ni);

		/**
		 * @copydoc cla3p::dns::RdVector::rblock(uint_t ibgn, uint_t ni) const
		 */
		CfVGuard rblock(uint_t ibgn, uint_t ni) const;

		/**
		 * @copydoc cla3p::dns::RdVector::setBlock()
		 */
		void setBlock(uint_t ibgn, const CfVector& src);

		/** @} */

		// -------------------------------------------------------------------------------

		/** 
		 * @name Creators/Generators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdVector::init()
		 */
		static CfVector init(uint_t n);

		/**
		 * @copydoc cla3p::dns::RdVector::zero()
		 */
		static CfVector zero(uint_t n);

		/**
		 * @copydoc cla3p::dns::RdVector::random()
		 */
		static CfVector random(uint_t n);

		/**
		 * @copydoc cla3p::dns::RdVector::wrap(uint_t n, real_t *vals, bool bind)
		 */
		static CfVector wrap(uint_t n, complex8_t *vals, bool bind);

		/**
		 * @copydoc cla3p::dns::RdVector::wrap(uint_t n, const real_t *vals)
		 */
		static CfVGuard wrap(uint_t n, const complex8_t *vals);

		/** @} */
};

/*-------------------------------------------------*/

/**
 * @ingroup dense_guard_group
 * @brief The single precision complex dense vector guard.
 *
 * The vector guard class is a vector wrapper class. 
 * Useful for protecting immutable data from being exposed.
 */
class CfVGuard : private Guard<CfVector> {

	public:

		/**
		 * @copydoc cla3p::dns::RdVGuard::RdVGuard()
		 */
		CfVGuard();

		/**
		 * @copydoc cla3p::dns::RdVGuard::~RdVGuard()
		 */
		~CfVGuard();

		/**
		 * @copydoc cla3p::dns::RdVGuard::RdVGuard(const RdVGuard& other)
		 */
		CfVGuard(const CfVGuard& other);

		/**
		 * @copydoc cla3p::dns::RdVGuard::operator=(const RdVGuard& other);
		 */
		CfVGuard& operator=(const CfVGuard& other);

		/**
		 * @copydoc cla3p::dns::RdVGuard::vec()
		 */
		const CfVector& vec() const;

		friend class CfVector;
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup stream_operator_group
 * @brief Writes to os the contents of vec
 */
std::ostream& operator<<(std::ostream& os, const cla3p::dns::CfVector& vec);
/*-------------------------------------------------*/

#endif // CLA3P_DNS_CFVECTOR_HPP_
