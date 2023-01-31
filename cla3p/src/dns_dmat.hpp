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

		bool isready() const;
		void clear();
		void unbind();

		dMat copy() const;
		dMat clone();
		dMat move();
		void info(const std::string& msg = "") const;
		void print() const;

		static dMat init(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld = 0);
		static dMat zero(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld = 0);
		static dMat random(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld = 0);
		static dMat map(const Property& prop, uint_t nrows, uint_t ncols, real_t *values, uint_t ld = 0);

		real_t& operator()(uint_t i, uint_t j);
		const real_t& operator()(uint_t i, uint_t j) const;

	private:
		dMat(GenericObject<real_t>&&);
		dMat& operator=(GenericObject<real_t>&&);
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_DMAT_HPP_
