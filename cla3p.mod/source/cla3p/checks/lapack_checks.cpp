// this file inc
#include "cla3p/checks/lapack_checks.hpp"

// system

// 3rd

// cla3p
#include "cla3p/error/error.hpp"
#include "cla3p/error/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
void lapack_info_check(int_t info)
{
	if(info > 0) {

		// TODO: separate exception for numerical ???
		throw err::Exception(msg::LapackError() + " info: " + std::to_string(info));

	} else if(info < 0) {

		throw err::Exception(msg::LapackError() + " info: " + std::to_string(info));

	}
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
