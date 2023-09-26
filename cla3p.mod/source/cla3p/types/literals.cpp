// this file inc
#include "cla3p/types/literals.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
static const std::string literal_stringInteger           = "Integer";
static const std::string literal_stringUnsignedInteger   = "Unsigned Integer";
static const std::string literal_stringReal              = "Real";
static const std::string literal_stringComplex           = "Complex";
static const std::string literal_stringSingle            = "Single (32bit)";
static const std::string literal_stringDouble            = "Double (64bit)";
static const std::string literal_stringDense             = "Dense";
static const std::string literal_stringSparseCsc         = "Sparse (csc)";
static const std::string literal_stringVector            = "Vector";
static const std::string literal_stringMatrix            = "Matrix";
static const std::string literal_stringPermutationMatrix = "Permutation Matrix";
static const std::string literal_stringDenseVector       = "Dense Vector";
static const std::string literal_stringDenseMatrix       = "Dense Matrix";
/*-------------------------------------------------*/
#define LITERAL_FUN_BODY(literal_function_name) \
const std::string& literal_function_name() \
{ \
	return literal_##literal_function_name; \
}
/*-------------------------------------------------*/
LITERAL_FUN_BODY(stringInteger          )
LITERAL_FUN_BODY(stringUnsignedInteger  )
LITERAL_FUN_BODY(stringReal             )
LITERAL_FUN_BODY(stringComplex          )
LITERAL_FUN_BODY(stringSingle           )
LITERAL_FUN_BODY(stringDouble           )
LITERAL_FUN_BODY(stringDense            )
LITERAL_FUN_BODY(stringSparseCsc        )
LITERAL_FUN_BODY(stringVector           )
LITERAL_FUN_BODY(stringMatrix           )
LITERAL_FUN_BODY(stringPermutationMatrix)
LITERAL_FUN_BODY(stringDenseVector      )
LITERAL_FUN_BODY(stringDenseMatrix      )
/*-------------------------------------------------*/
#undef LITERAL_FUN_BODY
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
