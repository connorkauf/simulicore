#ifndef CLA3P_TYPES_HPP_
#define CLA3P_TYPES_HPP_

/** @file
 * Basic datatypes and enumerations
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
using real4_t = float; /**< Single precision real. */
using real_t = double; /**< Double precision real. */
using complex8_t = std::complex<real4_t>; /**< Single precision complex. */
using complex_t = std::complex<real_t>; /**< Double precision complex. */
using bulk_t = std::size_t; /**< Standard indexing. */

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
 * @brief The operation class.
 */
class Operation {

	public:

		/**
		 * @enum op_t
		 * @brief The operation type.
		 */
		enum class op_t {
			N = 0, /**< No operation: \f$op(A) = A\f$ */
			T    , /**< Transpose operation: \f$op(A) = A^T\f$ */
			C      /**< Conjugate transpose operation: \f$op(A) = A^H\f$ */
		};

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty operation.
		 */
		Operation();

		/**
		 * @brief The member constructor.
		 *
		 * Constructs an operation with type otype.
		 */
		explicit Operation(op_t otype);

		/**
		 * @brief Destructs the operation.
		 */
		~Operation();

		/**
		 * @brief The copy constructor.
		 *
		 * Constructs an operation with the copy of the contents of other.
		 */
		Operation(const Operation& other);

		/**
		 * @brief The copy assignment operator.
		 *
		 * Replaces the contents of operation with a copy of the contents of other.
		 */
		Operation& operator=(const Operation& other);

		/**
		 * @brief The operation type.
		 */
		op_t type() const;

		/**
		 * @brief The operation name.
		 */
		const std::string& name() const;

	private:
		op_t m_type;
};
using op_t = cla3p::Operation::op_t; /**< Use directly cla3p::op_t to declare an operation type. */

/*-------------------------------------------------*/

/**
 * @class Property
 * @brief The property class.
 */
class Property {

	public:

		/**
		 * @enum prop_t
		 * @brief The property type.
		 */
		enum class prop_t {
			NONE      = 0, /**< No property */
			GENERAL      , /**< General (non-symmetric/non-hermitian matrix) */
			SYMMETRIC    , /**< Symmetric (lower) matrix */
			HERMITIAN      /**< Hermitian (lower) matrix */
		};

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty property.
		 */
		Property();

		/**
		 * @brief The member constructor.
		 *
		 * Constructs an property with type ptype.
		 */
		explicit Property(prop_t ptype);

		/**
		 * @brief Destructs the property.
		 */
		~Property();

		/**
		 * @brief The copy constructor.
		 *
		 * Constructs a property with the copy of the contents of other.
		 */
		Property(const Property& other);

		/**
		 * @brief The copy assignment operator.
		 *
		 * Replaces the contents of property with a copy of the contents of other.
		 */
		Property& operator=(const Property& other);

		/**
		 * @brief The property type.
		 */
		prop_t type() const;

		/**
		 * @brief The property name.
		 */
		const std::string& name() const;

		/**
		 * @brief Checks weather the property has a valid type.
		 */
		bool is_valid() const;

		/**
		 * @brief Checks weather the property type is general.
		 */
		bool is_general() const;

		/**
		 * @brief Checks weather the property type is symmetric.
		 */
		bool is_symmetric() const;

		/**
		 * @brief Checks weather the property type is hermitian.
		 */
		bool is_hermitian() const;

		/**
		 * @brief Checks weather the property type refers to the lower triangular part of a matrix.
		 */
		bool is_lower() const;

	private:
		prop_t m_type;
};
using prop_t = cla3p::Property::prop_t; /**< Use directly cla3p::prop_t to declare a property type. */

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @brief Writes to os the type of op.
 */
std::ostream& operator<<(std::ostream& os, const cla3p::Operation& op);

/**
 * @brief Writes to os the type of prop.
 */
std::ostream& operator<<(std::ostream& so, const cla3p::Property& prop);

/*-------------------------------------------------*/

#endif // CLA3P_TYPES_HPP_
