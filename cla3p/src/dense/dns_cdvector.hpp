#ifndef CLA3P_DNS_CDVECTOR_HPP_
#define CLA3P_DNS_CDVECTOR_HPP_

/** 
 * @file
 * The double precision complex dense vector definitions.
 */

#include <string>

#include "../types.hpp"
#include "../generic/generic_dns.hpp"
#include "../generic/guard.hpp"
#include "../dense/dns_rdvector.hpp"
#include "../dense/dns_cdmatrix.hpp"

/*-------------------------------------------------*/
namespace cla3p {
class PermMatrix;
namespace dns {
/*-------------------------------------------------*/
class CdVGuard;

/**
 * @ingroup dense_vectors
 * @nosubgrouping 
 * @brief The double precision complex dense vector object.
 */
class CdVector : private UniversalMetaTypes, public GenericObject<complex_t,real_t> {

	public:

		// no copy
		CdVector(const CdVector&) = delete;
		CdVector& operator=(const CdVector&) = delete;

		// -------------------------------------------------------------------------------

		/** 
		 * @name Constructors
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdVector::RdVector()
		 */
		CdVector();

		/**
		 * @copydoc cla3p::dns::RdVector::RdVector(uint_t n)
		 */
		CdVector(uint_t n);

		/**
		 * @copydoc cla3p::dns::RdVector::RdVector(RdVector&& other)
		 */
		CdVector(CdVector&& other);

		/**
		 * @copydoc cla3p::dns::RdVector::~RdVector()
		 */
		~CdVector();

		/** @} */

		// -------------------------------------------------------------------------------

		/** 
		 * @name Operators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdVector::operator=(RdVector&& other)
		 */
		CdVector& operator=(CdVector&& other);

		/**
		 * @copydoc cla3p::dns::RdVector::operator()()
		 */
		complex_t& operator()(uint_t i);

		/**
		 * @copydoc cla3p::dns::RdVector::operator()()
		 */
		const complex_t& operator()(uint_t i) const;

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
		CdVector copy() const;

		/**
		 * @copydoc cla3p::dns::RdVector::move()
		 */
		CdVector move();

		/**
		 * @copydoc cla3p::dns::RdVector::clone()
		 */
		CdVector clone();

		/**
		 * @copydoc cla3p::dns::RdVector::clone() const
		 */
		CdVGuard clone() const;

		/**
		 * @copydoc cla3p::dns::RdVector::matrix()
		 */
		CdMatrix matrix() const;

		/**
		 * @copydoc cla3p::dns::RdVector::rmatrix()
		 */
		CdMatrix rmatrix();

		/**
		 * @copydoc cla3p::dns::RdVector::rmatrix() const
		 */
		CdMGuard rmatrix() const;

		/**
		 * @copydoc cla3p::dns::RdVector::scale()
		 */
		void scale(complex_t coeff);

		/**
		 * @copydoc cla3p::dns::RdVector::normOne()
		 */
		real_t normOne() const;

		/**
		 * @copydoc cla3p::dns::RdVector::normInf()
		 */
		real_t normInf() const;

		/**
		 * @copydoc cla3p::dns::RdVector::normEuc()
		 */
		real_t normEuc() const;

		// 
		// not callcable from empty
		//

		/**
		 * @copydoc cla3p::dns::RdVector::permute()
		 */
		CdVector permute(const PermMatrix& P) const;

		/**
		 * @copydoc cla3p::dns::RdVector::ipermute()
		 */
		void ipermute(const PermMatrix& P);

		/**
		 * @copydoc cla3p::dns::RdVector::block()
		 */
		CdVector block(uint_t ibgn, uint_t ni) const;

		/**
		 * @copydoc cla3p::dns::RdVector::rblock(uint_t ibgn, uint_t ni)
		 */
		CdVector rblock(uint_t ibgn, uint_t ni);

		/**
		 * @copydoc cla3p::dns::RdVector::rblock(uint_t ibgn, uint_t ni) const
		 */
		CdVGuard rblock(uint_t ibgn, uint_t ni) const;

		/**
		 * @copydoc cla3p::dns::RdVector::setBlock()
		 */
		void setBlock(uint_t ibgn, const CdVector& src);

		/**
		 * @brief Gets a copy of the real part of vector.
		 */
		RdVector realPart() const;

		/**
		 * @brief Gets a copy of the imaginary part of vector.
		 */
		RdVector imagPart() const;

		/**
		 * @brief Sets a vector real part.
		 */
		void setRealPart(const RdVector& src);

		/**
		 * @brief Sets a vector imaginary part.
		 */
		void setImagPart(const RdVector& src);

		/**
		 * @brief Gets a copy of the real part of a portion of vector.
		 *
		 * Gets a copy of the real part of a ni-sized block of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector row that the requested part begins.
		 * @param[in] ni The number of rows of the requested block.
		 * @return A copy of the real part of a portion of the vector.
		 */
		RdVector realBlock(uint_t ibgn, uint_t ni) const;

		/**
		 * @brief Gets a copy of the imaginary part of a portion of vector.
		 *
		 * Gets a copy of the imaginary part of a ni-sized block of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector row that the requested part begins.
		 * @param[in] ni The number of rows of the requested block.
		 * @return A copy of the imaginary part of a portion of the vector.
		 */
		RdVector imagBlock(uint_t ibgn, uint_t ni) const;

		/**
		 * @brief Sets real part of a subvector.
		 *
		 * Copies the contents of a block in the real part of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector row that src will be placed.
		 * @param[in] src The block to be placed.
		 */
		void setRealBlock(uint_t ibgn, const RdVector& src);

		/**
		 * @brief Sets imaginary part of a subvector.
		 *
		 * Copies the contents of a block in the imaginary part of the vector, starting at ibgn.
		 *
		 * @param[in] ibgn The vector row that src will be placed.
		 * @param[in] src The block to be placed.
		 */
		void setImagBlock(uint_t ibgn, const RdVector& src);

		/** @} */

		// -------------------------------------------------------------------------------

		/** 
		 * @name Creators/Generators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::RdVector::init()
		 */
		static CdVector init(uint_t n);

		/**
		 * @copydoc cla3p::dns::RdVector::zero()
		 */
		static CdVector zero(uint_t n);

		/**
		 * @copydoc cla3p::dns::RdVector::random()
		 */
		static CdVector random(uint_t n);

		/**
		 * @copydoc cla3p::dns::RdVector::wrap(uint_t n, real_t *vals, bool bind)
		 */
		static CdVector wrap(uint_t n, complex_t *vals, bool bind);

		/**
		 * @copydoc cla3p::dns::RdVector::wrap(uint_t n, const real_t *vals)
		 */
		static CdVGuard wrap(uint_t n, const complex_t *vals);

		/** @} */
};

/*-------------------------------------------------*/

/**
 * @ingroup dense_guards
 * @brief The double precision complex dense vector guard.
 *
 * The vector guard class is a vector wrapper class. 
 * Useful for protecting immutable data from being exposed.
 */
class CdVGuard : private Guard<CdVector> {

	public:

		/**
		 * @copydoc cla3p::dns::RdVGuard::RdVGuard()
		 */
		CdVGuard();

		/**
		 * @copydoc cla3p::dns::RdVGuard::~RdVGuard()
		 */
		~CdVGuard();

		/**
		 * @copydoc cla3p::dns::RdVGuard::RdVGuard(const RdVGuard& other)
		 */
		CdVGuard(const CdVGuard& other);

		/**
		 * @copydoc cla3p::dns::RdVGuard::operator=(const RdVGuard& other);
		 */
		CdVGuard& operator=(const CdVGuard& other);

		/**
		 * @copydoc cla3p::dns::RdVGuard::vec()
		 */
		const CdVector& vec() const;

		friend class CdVector;
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup stream_operators
 * @brief Writes to os the contents of vec
 */
std::ostream& operator<<(std::ostream& os, const cla3p::dns::CdVector& vec);
/*-------------------------------------------------*/

#endif // CLA3P_DNS_CDVECTOR_HPP_
