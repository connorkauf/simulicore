#ifndef CLA3P_TYPES_HPP_
#define CLA3P_TYPES_HPP_

/** @file types.hpp
 * Basic datatypes and enumerations declaration
 */

#include <cstddef>
#include <ostream>
#include <string>
#include <mkl_types.h>

#if defined (CLA3P_I64)
#define _DFMT_ "lld"
#define _UFMT_ "llu"
#else
#define _DFMT_ "d"
#define _UFMT_ "u"
#endif

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

typedef int nint_t;
typedef MKL_INT int_t;
typedef MKL_UINT uint_t;
typedef double real_t;
typedef MKL_Complex16 complex_t;
typedef std::size_t bulk_t;

complex_t cval(real_t re, real_t im);
complex_t czero();

enum class ptype_t {
	NONE      = 0,
	GENERAL      ,
	SYMMETRIC    ,
	HERMITIAN    
};

class Property {
	public:
		Property();
		Property(ptype_t);
		Property(const Property&);
		Property& operator=(const Property&);
		~Property();

		ptype_t type() const;
		const std::string& name() const;
		bool is_valid() const;
		bool is_general() const;
		bool is_symmetric() const;
		bool is_hermitian() const;
	private:
		ptype_t m_type;
};

enum class TransOp {
	N = 0,
	T    ,
	C    
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

std::ostream& operator<<(std::ostream&, const cla3p::complex_t&);

cla3p::complex_t operator+(const cla3p::complex_t&, const cla3p::complex_t&);
cla3p::complex_t operator-(const cla3p::complex_t&, const cla3p::complex_t&);
cla3p::complex_t operator*(const cla3p::complex_t&, const cla3p::complex_t&);
cla3p::complex_t operator/(const cla3p::complex_t&, const cla3p::complex_t&);

/*-------------------------------------------------*/

#endif // CLA3P_TYPES_HPP_
