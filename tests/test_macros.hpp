#ifndef CLA3P_TEST_MACROS_HPP_
#define CLA3P_TEST_MACROS_HPP_

#include "cla3p/src/error.hpp"
#include "cla3p/src/error_internal.hpp"

/*-------------------------------------------------*/
#define fatal_error() \
	do { \
		Error("Test " << __func__ << " failed"); \
		if(strict) { \
			throw Exception("Tests failed"); \
		} else { \
			return 1; \
		} \
	} while(0)
/*-------------------------------------------------*/
#define test_success() \
	std::cout << "Test " << __func__ << " passed\n";
/*-------------------------------------------------*/

#endif // CLA3P_TEST_MACROS_HPP_

