#ifndef CLA3P_DNS_DMAT_HPP_
#define CLA3P_DNS_DMAT_HPP_

#include <string>

#include "types.hpp"
#include "dns_generic.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/

class dMat : private GenericObject<real_t> {

	public:
		dMat();
		~dMat();
		dMat(const dMat&) = delete;
		dMat& operator=(const dMat&) = delete;
		dMat(dMat&&);
		dMat& operator=(dMat&&);

		void info(const std::string& msg = "") const;
		dMat copy() const;
		dMat move();
		void print() const;

		static dMat init(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld = defaultld);
    static dMat zero(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld = defaultld);
		static dMat random(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld = defaultld);

		cla3p::real_t& operator()(uint_t i, cla3p::uint_t j);
		const cla3p::real_t& operator()(uint_t i, uint_t j) const;

	private:
		dMat(GenericObject<real_t>&&);
		dMat& operator=(GenericObject<real_t>&&);
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_DMAT_HPP_
