#ifndef CLA3P_TEST_MACROS_HPP_
#define CLA3P_TEST_MACROS_HPP_

#include <iostream>

#include "cla3p/src/error.hpp"
#include "cla3p/src/error_internal.hpp"

/*-------------------------------------------------*/
#define fatal_error() \
	do { \
		Error("  Test " << __func__ << " failed"); \
		if(strict) { \
			throw cla3p::Exception("Tests failed"); \
		} \
		return 1; \
	} while(0)
/*-------------------------------------------------*/
#if 0
#define test_success() \
	do{ \
		std::cout << "  Test " << __func__ << " passed\n"; \
		return 0; \
	}while(0)
#else
#define test_success() return 0;
#endif
/*-------------------------------------------------*/
#define print_summary() \
	do{ \
		if(!numfail){ \
			std::cout << "Test group: " << __func__ << ": " << numtests << "/" << numtests <<  " tests passed\n"; \
			return 0; \
		} else { \
			std::cout << "Test group: " << __func__ << ": " << numfail << "/" << numtests <<  " tests failed\n"; \
			return 1; \
		} \
	}while(0)
/*-------------------------------------------------*/

#endif // CLA3P_TEST_MACROS_HPP_

