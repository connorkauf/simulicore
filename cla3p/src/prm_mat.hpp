#ifndef CLA3P_PRM_MAT_HPP_
#define CLA3P_PRM_MAT_HPP_

/** @file
 * The permutation matrix definitions
 */

#include "types.hpp"
#include "generic/universal.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace prm {
/*-------------------------------------------------*/

class pMat : private UniversalMetaTypes, private UniversalMetaData {

	public:
		pMat();
		pMat(uint_t size);
		~pMat();

		// no copy
		pMat(const pMat&) = delete;
		pMat& operator=(const pMat&) = delete;

		// move
		pMat(pMat&&);
		pMat& operator=(pMat&&);

		// non inherited args
		uint_t        size  () const;
		uint_t*       values()      ;
		const uint_t* values() const;

		// callcable from empty
		void clear();
		pMat copy() const;
		pMat move();

		void info(const std::string& msg = "") const;
		void print() const;

		uint_t& operator()(uint_t i);
		const uint_t& operator()(uint_t i) const;

		// not callcable from empty
		// ...

		// static initializers (basic)
		static pMat init(uint_t size);
		static pMat random(uint_t size);

	private:
		uint_t *m_values;

		void setValues(uint_t *values);

		void defaults();
		void creator(uint_t size, uint_t *values, bool owner);
		void blankCreator(uint_t size);
		void randomCreator(uint_t size);
};

/*-------------------------------------------------*/
} // namespace prm
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_PRM_MAT_HPP_
