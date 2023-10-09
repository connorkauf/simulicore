#ifndef CLA3P_ENUMS_HPP_
#define CLA3P_ENUMS_HPP_

/** 
 * @file
 * Enumerations
 */

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @ingroup basic_datatypes 
 * @enum prop_t
 * @brief The property type.
 */
enum class prop_t {
	Undefined   = 0, /**< No property */
	General        , /**< General matrix */
	Symmetric      , /**< Symmetric matrix */
	Hermitian      , /**< Hermitian matrix */
	Triangular     , /**< Triangular/trapezoidal matrix */
	Skew             /**< Skew matrix */
};

/**
 * @ingroup basic_datatypes 
 * @enum uplo_t
 * @brief The fill type.
 */
enum class uplo_t : char {
	F = 'F', /**< Both parts are filled */
	U = 'U', /**< The upper part is filled */
	L = 'L'  /**< The lower part is filled */
};

/**
 * @ingroup basic_datatypes 
 * @enum op_t
 * @brief The operation type.
 */
enum class op_t : char {
	N = 'N', /**< No operation: @f$ op(A) = A @f$ */
	T = 'T', /**< Transpose operation: @f$ op(A) = A^T @f$ */
	C = 'C'  /**< Conjugate transpose operation: @f$ op(A) = A^H @f$ */
};

enum class dup_t {
	Sum  = 0,
	Prod    ,
	Amax    ,
	Amin     
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ENUMS_HPP_
