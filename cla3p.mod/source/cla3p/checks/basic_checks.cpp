// this file inc
#include "cla3p/checks/basic_checks.hpp"

// system

// 3rd

// cla3p
#include "cla3p/error/error.hpp"
#include "cla3p/error/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
void square_check(uint_t m, uint_t n)
{
	if(m != n) {
		throw err::NoConsistency(msg::InvalidPropertyForSquare());
	}
}
/*-------------------------------------------------*/
void property_compatibility_check(const Property& prop, uint_t m, uint_t n)
{
	if(!prop.isValid()) {
		throw err::NoConsistency(msg::InvalidProperty());
	}

	if(prop.isSquare()) {
		square_check(m, n);
	}
}
/*-------------------------------------------------*/
void similarity_check(
		const Property& prop1, uint_t nrows1, uint_t ncols1, 
		const Property& prop2, uint_t nrows2, uint_t ncols2)
{
	if(nrows1 != nrows2 || ncols1 != ncols2) {
		throw err::NoConsistency(msg::InvalidDimensions());
	}

	if(prop1 != prop2) {
		throw err::NoConsistency(msg::InvalidProperty());
	}
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
