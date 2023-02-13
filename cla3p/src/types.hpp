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

/*-------------------------------------------------*/

/**
 * @class Operation
 * @brief The operation type class
 */
class Operation {

	public:

		/**
		 * @enum cla3p::Operation::op_t
		 * @brief The operation type
		 */
		enum class op_t {
			N = 0, /**< No operation */
			T    , /**< Transpose */
			C      /**< Conjugate transpose */
		};

		Operation();
		explicit Operation(op_t);
		~Operation();

		Operation(const Operation&);
		Operation& operator=(const Operation&);

		/**
		 * @brief The operation type
		 */
		op_t type() const;

	private:
		op_t m_type;
};
/** 
 * @typedef cla3p::Operation::op_t cla3p::op_t
 * For convinience purposes op_t is callable from outside the Operation class
 */
using op_t = cla3p::Operation::op_t;

/*-------------------------------------------------*/

/**
 * @class Property
 * @brief The property class
 */
class Property {

	public:

		/**
		 * @enum cla3p::Property::prop_t
		 * @brief The property type
		 */
		enum class prop_t {
			NONE      = 0, /**< No property */
			GENERAL      , /**< General (non-symmetric/non-hermitian matrix) */
			SYMMETRIC    , /**< Symmetric matrix */
			HERMITIAN      /**< Hermitian matrix */
		};

		Property();
		explicit Property(prop_t);
		~Property();

		Property(const Property&);
		Property& operator=(const Property&);

		/**
		 * @brief The property type
		 */
		prop_t type() const;

		/**
		 * @brief The property name
		 */
		const std::string& name() const;
		bool is_valid() const;
		bool is_general() const;
		bool is_symmetric() const;
		bool is_hermitian() const;
		bool is_lower() const;

	private:
		prop_t m_type;
};
/** 
 * @typedef cla3p::Property::prop_t cla3p::prop_t
 * For convinience purposes prop_t is callable from outside the Property class
 */
using prop_t = cla3p::Property::prop_t;

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

std::ostream& operator<<(std::ostream&, const cla3p::Property&);

/*-------------------------------------------------*/


#endif // CLA3P_TYPES_HPP_
