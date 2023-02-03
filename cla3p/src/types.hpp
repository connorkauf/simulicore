#ifndef CLA3P_TYPES_HPP_
#define CLA3P_TYPES_HPP_

/** @file types.hpp
 * Basic datatypes and enumerations declaration
 */

#include <cstddef>
#include <ostream>
#include <string>
#include <complex>

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

#if defined (CLA3P_I64)
#define _DFMT_ "lld"
#define _UFMT_ "llu"
using  int_t =          long long int;
using uint_t = unsigned long long int;
#else
#define _DFMT_ "d"
#define _UFMT_ "u"
using  int_t =          int;
using uint_t = unsigned int;
#endif

using nint_t = int;
using real4_t = float;
using real_t = double;
using complex8_t = std::complex<real4_t>;
using complex_t = std::complex<real_t>;
using bulk_t = std::size_t;

// TODO: move to a math header ???
inline real_t conj(const real_t& d) { /*WarningNoReach*/ return d; }
inline real4_t conj(const real4_t& s) { /*WarningNoReach*/ return s; }
inline complex_t conj(const complex_t& z) { return std::conj(z); }
inline complex8_t conj(const complex8_t& c) { return std::conj(c); }
inline void setim(real_t&, real_t ) { /*WarningNoReach*/ }
inline void setim(real4_t&, real4_t) { /*WarningNoReach*/ }
inline void setim(complex_t& z, real_t d) { z.imag(d); }
inline void setim(complex8_t& c, real4_t s) { c.imag(s); }

enum class TransOp {
	N = 0,
	T    ,
	C    
};

enum class prop_t {
	NONE      = 0,
	GENERAL      ,
	SYMMETRIC    ,
	HERMITIAN    
};

class Property {
	public:
		Property();
		Property(prop_t);
		Property(const Property&);
		Property& operator=(const Property&);
		~Property();

		prop_t type() const;
		const std::string& name() const;
		bool is_valid() const;
		bool is_general() const;
		bool is_symmetric() const;
		bool is_hermitian() const;
		bool is_lower() const;
	private:
		prop_t m_type;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

std::ostream& operator<<(std::ostream&, const cla3p::Property&);

/*-------------------------------------------------*/


#endif // CLA3P_TYPES_HPP_
