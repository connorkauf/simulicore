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
class dMMap;

class dMat : private UniversalMetaTypes, public GenericObject<real_t,real_t> {

	public:
		dMat();
		dMat(uint_t nrows, uint_t ncols);
		dMat(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld, bool wipe);
		~dMat();

		// no copy
		dMat(const dMat&) = delete;
		dMat& operator=(const dMat&) = delete;

		// move
		dMat(dMat&&);
		dMat& operator=(dMat&&);

		// non inherited args
		uint_t nrows() const;
		uint_t ncols() const;
		uint_t ld() const;
		const Property& prop() const;

		// callcable from empty
		dMat copy() const;
		dMat move();
		dMat clone();
		dMMap clone() const;

		void info(const std::string& msg = "") const;

		real_t normOne() const;
		real_t normInf() const;
		real_t normMax() const;
		real_t normFro() const;

		real_t& operator()(uint_t i, uint_t j);
		const real_t& operator()(uint_t i, uint_t j) const;

		// not callcable from empty
		dMat transpose() const;
		dMat permute(const prm::pMat& P, const prm::pMat& Q) const;
		dMat permuteLeft(const prm::pMat& P) const;
		dMat permuteRight(const prm::pMat& Q) const;
		dMat permute(const prm::pMat& P) const;

		void ipermute(const prm::pMat& P, const prm::pMat& Q);
		void ipermuteLeft(const prm::pMat& P);
		void ipermuteRight(const prm::pMat& Q);
		void ipermute(const prm::pMat& P);

		dMat block(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;
		dMat rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);
		dMMap rblock(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;

		void setBlock(uint_t ibgn, uint_t jbgn, const dMat& src);

		// static initializers (basic)
		static dMat init(uint_t nrows, uint_t ncols);
		static dMat zero(uint_t nrows, uint_t ncols);
		static dMat random(uint_t nrows, uint_t ncols);
		static dMat map(uint_t nrows, uint_t ncols, real_t *values);
		static dMMap map(uint_t nrows, uint_t ncols, const real_t *values);

		// static initializers (advanced)
		static dMat init(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld);
		static dMat zero(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld);
		static dMat random(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld);
		static dMat map(prop_t ptype, uint_t nrows, uint_t ncols, real_t *values, uint_t ld, bool bind);
		static dMMap map(prop_t ptype, uint_t nrows, uint_t ncols, const real_t *values, uint_t ld);
};

/*-------------------------------------------------*/

class dMMap : private GenericMap<dMat> {

	public:
		dMMap();
		~dMMap();
		dMMap(const dMMap&);
		dMMap& operator=(const dMMap&);

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
