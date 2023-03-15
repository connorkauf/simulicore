#ifndef CLA3P_DNS_RFVECTOR_HPP_
#define CLA3P_DNS_RFVECTOR_HPP_

/** 
 * @file
 * The single precision real dense vector definitions.
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
class RfVGuard;

/**
 * @ingroup dense_vector_group
 * @nosubgrouping 
 * @brief The single precision real dense vector object.
 */
class RfVector : private UniversalMetaTypes, public GenericObject<real4_t,real4_t> {

	public:

		// no copy
		RfVector(const RfVector&) = delete;
		RfVector& operator=(const RfVector&) = delete;

		// -------------------------------------------------------------------------------

		/** 
		 * @name Constructors
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdVector::RdVector()
		 */
		RfVector();

		/**
		 * @copydoc cla3p::dns::RdVector::RdVector(uint_t n)
		 */
		RfVector(uint_t n);

		/**
		 * @copydoc cla3p::dns::RdVector::RdVector(RdVector&& other)
		 */
		RfVector(RfVector&& other);

		/**
		 * @copydoc cla3p::dns::RdVector::~RdVector()
		 */
		~RfVector();

		/** @} */

		// -------------------------------------------------------------------------------

		/** 
		 * @name Operators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdVector::operator=(RdVector&& other)
		 */
		RfVector& operator=(RfVector&& other);

		/**
		 * @copydoc cla3p::dns::RdVector::operator()()
		 */
		real4_t& operator()(uint_t i);

		/**
		 * @copydoc cla3p::dns::RdVector::operator()()
		 */
		const real4_t& operator()(uint_t i) const;

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
		RfVector copy() const;

		/**
		 * @copydoc cla3p::dns::RdVector::move()
		 */
		RfVector move();

		/**
		 * @copydoc cla3p::dns::RdVector::clone()
		 */
		RfVector clone();

		/**
		 * @copydoc cla3p::dns::RdVector::clone() const
		 */
		RfVGuard clone() const;

		/**
		 * @copydoc cla3p::dns::RdVector::scale()
		 */
		void scale(real4_t coeff);

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
		 * @copydoc cla3p::dns::RdVector::permute()
		 */
		RfVector permute(const PermMatrix& P) const;

		/**
		 * @copydoc cla3p::dns::RdVector::ipermute()
		 */
		void ipermute(const PermMatrix& P);

		/**
		 * @copydoc cla3p::dns::RdVector::block()
		 */
		RfVector block(uint_t ibgn, uint_t ni) const;

		/**
		 * @copydoc cla3p::dns::RdVector::rblock(uint_t ibgn, uint_t ni)
		 */
		RfVector rblock(uint_t ibgn, uint_t ni);

		/**
		 * @copydoc cla3p::dns::RdVector::rblock(uint_t ibgn, uint_t ni) const
		 */
		RfVGuard rblock(uint_t ibgn, uint_t ni) const;

		/**
		 * @copydoc cla3p::dns::RdVector::setBlock()
		 */
		void setBlock(uint_t ibgn, const RfVector& src);

		/** @} */

		// -------------------------------------------------------------------------------

		/** 
		 * @name Creators/Generators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdVector::init()
		 */
		static RfVector init(uint_t n);

		/**
		 * @copydoc cla3p::dns::RdVector::zero()
		 */
		static RfVector zero(uint_t n);

		/**
		 * @copydoc cla3p::dns::RdVector::random()
		 */
		static RfVector random(uint_t n);

		/**
		 * @copydoc cla3p::dns::RdVector::wrap(uint_t n, real_t *vals, bool bind)
		 */
		static RfVector wrap(uint_t n, real4_t *vals, bool bind);

		/**
		 * @copydoc cla3p::dns::RdVector::wrap(uint_t n, const real_t *vals)
		 */
		static RfVGuard wrap(uint_t n, const real4_t *vals);

		/** @} */
};

/*-------------------------------------------------*/

/**
 * @ingroup dense_guard_group
 * @brief The single precision real dense vector guard.
 *
 * The vector guard class is a vector wrapper class. 
 * Useful for protecting immutable data from being exposed.
 */
class RfVGuard : private Guard<RfVector> {

	public:

		/**
		 * @copydoc cla3p::dns::RdVGuard::RdVGuard()
		 */
		RfVGuard();

		/**
		 * @copydoc cla3p::dns::RdVGuard::~RdVGuard()
		 */
		~RfVGuard();

		/**
		 * @copydoc cla3p::dns::RdVGuard::RdVGuard(const RdVGuard& other)
		 */
		RfVGuard(const RfVGuard& other);

		/**
		 * @copydoc cla3p::dns::RdVGuard::operator=(const RdVGuard& other);
		 */
		RfVGuard& operator=(const RfVGuard& other);

		/**
		 * @copydoc cla3p::dns::RdVGuard::vec()
		 */
		const RfVector& vec() const;

		friend class RfVector;
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup stream_operator_group
 * @brief Writes to os the contents of vec
 */
std::ostream& operator<<(std::ostream& os, const cla3p::dns::RfVector& vec);
/*-------------------------------------------------*/

#endif // CLA3P_DNS_RFVECTOR_HPP_
