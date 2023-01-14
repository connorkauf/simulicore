/** \file test.hpp
 *
 * This file contains two function protos, one of which is documented, 
 * the other one is not, so that we can see how doxygen documents this 
 * piece of code.
 */

#ifndef CLA3P_TEST_HPP_
#define CLA3P_TEST_HPP_

namespace cla3p {

/**
 * \brief A sample function that returns 0
 *
 * This is the detailed description of a test function 
 * in order to test doxygen documentation. It returns zero.
 *
 * \param x An input param that does nothing
 * \return The number 0
 */
int return_zero(int x);

int return_one(int x);

/**
 * \brief A sample c++ class
 *
 * This is the detailed description of a sample c++ class
 */
class TestClass {

	public:

		/** 
		 * \brief Default constructor
		 */
		TestClass();

		/** 
		 * \brief Default destructor
		 */
		~TestClass();

		/** 
		 * \brief Access member
		 * \return The rvalue of x
		 */
		int& x();

		/** 
		 * \brief Add to class
		 * \param y The value to be added
		 * \return The value of x + y
		 */
		int add(int y); 

		/** 
		 * \static
		 * \brief create a zero class
		 * \return A zero test class
		 */
		static TestClass zero();

	private:
		int x_;
};

} // namespace cla3p

#endif // CLA3P_TEST_HPP_
