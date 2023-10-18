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
 *
 * List of matrix algebraic properties.@n
 * Used to construct a Property class that characterizes a matrix in order to take advantage of its properties.
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
 *
 * List of matrix structural properties.@n
 * Used to construct a Property class to determine where the values of a matrix are stored.
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
 *
 * List of operations (implicitly) applied on a matrix.@n
 * For efficiency purposes in matrix operations, this flag is used to designate a virtual operation that is not explicitly applied to the matrix.@n
 * For example in order for the operation Y = A<sup>T</sup> * X to be calculated we do not need to explicitly calculate A<sup>T</sup>.@n
 * Instead we can use the mult() function with the appropriate op_t value for the matrix A:
 @verbatim
 Y = cla3p::ops::mult(1, cla3p::op_t::T, A, X);
 @endverbatim
 to calculate the matrix product much more efficiently.
 */
enum class op_t : char {
	N = 'N', /**< No operation: op(A) = A */
	T = 'T', /**< Transpose operation: op(A) = A<sup>T</sup> */
	C = 'C'  /**< Conjugate transpose operation: op(A) = A<sup>H</sup> */
};

enum class side_t : char {
	Left  = 'L',
	Right = 'R' 
};

enum class diag_t : char {
	NonUnit = 'N',
	Unit    = 'U' 
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
