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
typedef          long long int  int_t;
typedef unsigned long long int uint_t;
#else
#define _DFMT_ "d"
#define _UFMT_ "u"
typedef          int  int_t;
typedef unsigned int uint_t;
#endif

typedef int nint_t;
typedef float real4_t;
typedef double real_t;
typedef std::complex<real4_t> complex8_t;
typedef std::complex<real_t> complex_t;
typedef std::size_t bulk_t;

// TODO: move to a math header ???
inline real_t conj(const real_t& d) { /*WarningNoReach*/ return d; }
inline real4_t conj(const real4_t& s) { /*WarningNoReach*/ return s; }
inline complex_t conj(const complex_t& z) { return std::conj(z); }
inline complex8_t conj(const complex8_t& c) { return std::conj(c); }
#if 0
bool operator==(const complex_t & z1, const complex_t & z2) { return (z1.real() == z2.real() && z1.imag() == z2.imag()); }
bool operator==(const complex8_t& c1, const complex8_t& c2) { return (c1.real() == c2.real() && c1.imag() == c2.imag()); }
bool operator==(const complex_t & z , const real_t    & d ) { return (z.real() == d && z.imag() == 0.); }
bool operator==(const complex8_t& c , const real4_t   & s ) { return (c.real() == s && c.imag() == 0.); }
bool operator==(const real_t    & d , const complex_t & z ) { return (z == d); }
bool operator==(const real4_t   & s , const complex8_t& c ) { return (c == s); }
#endif

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
#endif // CLA3P_TYPES_HPP_
