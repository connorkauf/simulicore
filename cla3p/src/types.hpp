#ifndef CLA3P_TYPES_HPP_
#define CLA3P_TYPES_HPP_

/** 
 * @file
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
/** @ingroup basic_datatypes_group */ using real4_t = float;                    /**< Single precision real. */
/** @ingroup basic_datatypes_group */ using real_t = double;                    /**< Double precision real. */
/** @ingroup basic_datatypes_group */ using complex8_t = std::complex<real4_t>; /**< Single precision complex. */
/** @ingroup basic_datatypes_group */ using complex_t = std::complex<real_t>;   /**< Double precision complex. */
/** @ingroup basic_datatypes_group */ using bulk_t = std::size_t;               /**< Standard indexing. */

// TODO: move to a math header ???
inline int_t conj(const int_t& i) { return i; }
inline uint_t conj(const uint_t& u) { return u; }
inline real_t conj(const real_t& d) { return d; }
inline real4_t conj(const real4_t& s) { return s; }
inline complex_t conj(const complex_t& z) { return std::conj(z); }
inline complex8_t conj(const complex8_t& c) { return std::conj(c); }

inline void setim(int_t&, int_t) { }
inline void setim(uint_t&, uint_t) { }
inline void setim(real_t&, real_t) { }
inline void setim(real4_t&, real4_t) { }
inline void setim(complex_t& z, real_t d) { z.imag(d); }
inline void setim(complex8_t& c, real4_t s) { c.imag(s); }

/*-------------------------------------------------*/

/**
 * @ingroup basic_datatypes_group
 * @brief The operation class.
 */
class Operation {

	public:

		/**
		 * @enum op_t
		 * @brief The operation type.
		 */
		enum class op_t : char {
			N = 'N', /**< No operation: @f$ op(A) = A @f$ */
			T = 'T', /**< Transpose operation: @f$ op(A) = A^T @f$ */
			C = 'C'  /**< Conjugate transpose operation: @f$ op(A) = A^H @f$ */
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
		 * @brief The operation type as a char.
		 */
		char ctype() const;

		/**
		 * @brief The operation name.
		 */
		const std::string& name() const;

		/**
		 * @brief Checks weather the operation is (conjugate) transpose
		 */
		bool isTranspose() const;

	private:
		op_t m_type;
};

/** 
 * @ingroup basic_datatypes_group 
 */
using op_t = cla3p::Operation::op_t; /**< Use directly cla3p::op_t to declare an operation type. */

/*-------------------------------------------------*/

/**
 * @ingroup basic_datatypes_group
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
			GENERAL      , /**< General matrix */
			SYMMETRIC    , /**< Symmetric matrix */
			HERMITIAN    , /**< Hermitian matrix */
			TRIANGULAR   , /**< Triangular/trapezoidal matrix */
			SKEW           /**< Skew matrix */
		};

		/**
		 * @enum uplo_t
		 * @brief The fill type.
		 */
		enum class uplo_t : char {
			F = 'F', /**< Both parts are filled */
			U = 'U', /**< The upper part is filled */
			L = 'L'  /**< The lower part is filled */
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
		 * Constructs an property with type ptype and fill type ftype.
		 */
		explicit Property(prop_t ptype, uplo_t ftype);

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
		 * @brief The compare operator.
		 *
		 * Checks if two propertyies are equal
		 */
		bool operator==(const Property& other) const;

		/**
		 * @brief The compare operator.
		 *
		 * Checks if two propertyies are not equal
		 */
		bool operator!=(const Property& other) const;

		/**
		 * @brief The property type.
		 */
		prop_t type() const;

		/**
		 * @brief The property fill type.
		 */
		uplo_t uplo() const;

		/**
		 * @brief The property fill type as a char.
		 */
		char cuplo() const;

		/**
		 * @brief The property name.
		 */
		const std::string& name() const;

		/**
		 * @brief Checks weather the property has a valid type.
		 */
		bool isValid() const;

		/**
		 * @brief Checks weather the property requires matrix to be square.
		 */
		bool isSquare() const;

		/**
		 * @brief Checks weather the property type is general.
		 */
		bool isGeneral() const;

		/**
		 * @brief Checks weather the property type is symmetric.
		 */
		bool isSymmetric() const;

		/**
		 * @brief Checks weather the property type is hermitian.
		 */
		bool isHermitian() const;

		/**
		 * @brief Checks weather the property type is triangular/trapezoidal.
		 */
		bool isTriangular() const;

		/**
		 * @brief Checks weather the property type is skew.
		 */
		bool isSkew() const;

		/**
		 * @brief Checks weather the entire matrix is used.
		 */
		bool isFull() const;

		/**
		 * @brief Checks weather the upper part of the matrix is used.
		 */
		bool isUpper() const;

		/**
		 * @brief Checks weather the lower part of the matrix is used.
		 */
		bool isLower() const;

	private:
		prop_t m_type;
		uplo_t m_uplo;

		void check() const;
};

/** 
 * @ingroup basic_datatypes_group 
 */
using prop_t = cla3p::Property::prop_t; /**< Use directly cla3p::prop_t to declare a property type. */
/** 
 * @ingroup basic_datatypes_group 
 */
using uplo_t = cla3p::Property::uplo_t; /**< Use directly cla3p::uplo_t to declare a fill type. */

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup stream_operator_group
 * @brief Writes to os the type of op.
 */
std::ostream& operator<<(std::ostream& os, const cla3p::Operation& op);

/**
 * @ingroup stream_operator_group
 * @brief Writes to os the type of prop.
 */
std::ostream& operator<<(std::ostream& so, const cla3p::Property& prop);

/*-------------------------------------------------*/

#endif // CLA3P_TYPES_HPP_
