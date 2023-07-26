#ifndef CLA3P_DNS_RIVECTOR_HPP_
#define CLA3P_DNS_RIVECTOR_HPP_

/** 
 * @file
 * The integer dense vector definitions.
 */

#include <string>

#include "../types.hpp"
#include "../generic/generic_dns.hpp"
#include "../generic/guard.hpp"
#include "../dense/dns_rimatrix.hpp"

/*-------------------------------------------------*/
namespace cla3p {
class PermMatrix;
namespace dns {
/*-------------------------------------------------*/
class RiVGuard;

/**
 * @ingroup dense_vectors
 * @nosubgrouping 
 * @brief The integer dense vector object.
 */
class RiVector : private UniversalMetaTypes, public GenericObject<int_t,int_t> {

	public:

		// no copy
		RiVector(const RiVector&) = delete;
		RiVector& operator=(const RiVector&) = delete;

		// -------------------------------------------------------------------------------

		/** 
		 * @name Constructors
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdVector::RdVector()
		 */
		RiVector();

		/**
		 * @copydoc cla3p::dns::RdVector::RdVector(uint_t n)
		 */
		RiVector(uint_t n);

		/**
		 * @copydoc cla3p::dns::RdVector::RdVector(RdVector&& other)
		 */
		RiVector(RiVector&& other);

		/**
		 * @copydoc cla3p::dns::RdVector::~RdVector()
		 */
		~RiVector();

		/** @} */

		// -------------------------------------------------------------------------------

		/** 
		 * @name Operators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdVector::operator=(RdVector&& other)
		 */
		RiVector& operator=(RiVector&& other);

		/**
		 * @copydoc cla3p::dns::RdVector::operator()()
		 */
		int_t& operator()(uint_t i);

		/**
		 * @copydoc cla3p::dns::RdVector::operator()()
		 */
		const int_t& operator()(uint_t i) const;

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
		RiVector copy() const;

		/**
		 * @copydoc cla3p::dns::RdVector::move()
		 */
		RiVector move();

		/**
		 * @copydoc cla3p::dns::RdVector::rcopy()
		 */
		RiVector rcopy();

		/**
		 * @copydoc cla3p::dns::RdVector::rcopy() const
		 */
		RiVGuard rcopy() const;

		/**
		 * @copydoc cla3p::dns::RdVector::matrix()
		 */
		RiMatrix matrix() const;

		/**
		 * @copydoc cla3p::dns::RdVector::rmatrix()
		 */
		RiMatrix rmatrix();

		/**
		 * @copydoc cla3p::dns::RdVector::rmatrix() const
		 */
		RiMGuard rmatrix() const;

		/**
		 * @copydoc cla3p::dns::RdVector::scale()
		 */
		void scale(int_t coeff);

		// 
		// not callcable from empty
		//

		/**
		 * @copydoc cla3p::dns::RdVector::permute()
		 */
		RiVector permute(const PermMatrix& P) const;

		/**
		 * @copydoc cla3p::dns::RdVector::ipermute()
		 */
		void ipermute(const PermMatrix& P);

		/**
		 * @copydoc cla3p::dns::RdVector::block()
		 */
		RiVector block(uint_t ibgn, uint_t ni) const;

		/**
		 * @copydoc cla3p::dns::RdVector::rblock(uint_t ibgn, uint_t ni)
		 */
		RiVector rblock(uint_t ibgn, uint_t ni);

		/**
		 * @copydoc cla3p::dns::RdVector::rblock(uint_t ibgn, uint_t ni) const
		 */
		RiVGuard rblock(uint_t ibgn, uint_t ni) const;

		/**
		 * @copydoc cla3p::dns::RdVector::setBlock()
		 */
		void setBlock(uint_t ibgn, const RiVector& src);

		/** @} */

		// -------------------------------------------------------------------------------

		/** 
		 * @name Creators/Generators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdVector::init()
		 */
		static RiVector init(uint_t n);

		/**
		 * @copydoc cla3p::dns::RdVector::zero()
		 */
		static RiVector zero(uint_t n);

		/**
		 * @copydoc cla3p::dns::RdVector::random()
		 */
		static RiVector random(uint_t n);

		/**
		 * @copydoc cla3p::dns::RdVector::wrap(uint_t n, real_t *vals, bool bind)
		 */
		static RiVector wrap(uint_t n, int_t *vals, bool bind);

		/**
		 * @copydoc cla3p::dns::RdVector::wrap(uint_t n, const real_t *vals)
		 */
		static RiVGuard wrap(uint_t n, const int_t *vals);

		/** @} */
};

/*-------------------------------------------------*/

/**
 * @ingroup dense_guards
 * @brief The integer dense vector guard.
 *
 * The vector guard class is a vector wrapper class. 
 * Useful for protecting immutable data from being exposed.
 */
class RiVGuard : private Guard<RiVector> {

	public:

		/**
		 * @copydoc cla3p::dns::RdVGuard::RdVGuard()
		 */
		RiVGuard();

		/**
		 * @copydoc cla3p::dns::RdVGuard::~RdVGuard()
		 */
		~RiVGuard();

		/**
		 * @copydoc cla3p::dns::RdVGuard::RdVGuard(const RdVGuard& other)
		 */
		RiVGuard(const RiVGuard& other);

		/**
		 * @copydoc cla3p::dns::RdVGuard::operator=(const RdVGuard& other);
		 */
		RiVGuard& operator=(const RiVGuard& other);

		/**
		 * @copydoc cla3p::dns::RdVGuard::vec()
		 */
		const RiVector& vec() const;

		friend class RiVector;
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup stream_operators
 * @brief Writes to os the contents of vec
 */
std::ostream& operator<<(std::ostream& os, const cla3p::dns::RiVector& vec);
/*-------------------------------------------------*/

#endif // CLA3P_DNS_RIVECTOR_HPP_
