#ifndef CLA3P_PERM_MATRIX_HPP_
#define CLA3P_PERM_MATRIX_HPP_

/** @file
 * The permutation matrix definitions
 */

#include "types.hpp"
#include "generic/universal.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

class PermMatrix : private UniversalMetaTypes, private UniversalMetaData {

	public:
		PermMatrix();
		PermMatrix(uint_t size);
		~PermMatrix();

		// no copy
		PermMatrix(const PermMatrix&) = delete;
		PermMatrix& operator=(const PermMatrix&) = delete;

		// move
		PermMatrix(PermMatrix&&);
		PermMatrix& operator=(PermMatrix&&);

		// non inherited args
		uint_t        size  () const;
		uint_t*       values()      ;
		const uint_t* values() const;

		// callcable from empty
		void clear();
		PermMatrix copy() const;
		PermMatrix move();

		void info(const std::string& msg = "") const;
		void print() const;

		uint_t& operator()(uint_t i);
		const uint_t& operator()(uint_t i) const;

		// not callcable from empty
		// ...

		// static initializers (basic)
		static PermMatrix init(uint_t size);
		static PermMatrix random(uint_t size);

	private:
		uint_t *m_values;

		void setValues(uint_t *values);

		void defaults();
		void creator(uint_t size, uint_t *values, bool owner);
		void blankCreator(uint_t size);
		void randomCreator(uint_t size);
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_PERM_MATRIX_HPP_
