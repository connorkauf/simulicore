#ifndef CLA3P_PRM_MAT_HPP_
#define CLA3P_PRM_MAT_HPP_

#include "types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace prm {
/*-------------------------------------------------*/

class pMat {

	public:
		pMat();
		pMat(uint_t size);
		~pMat();

		pMat(const pMat&) = delete;
		pMat& operator=(const pMat&) = delete;

		pMat(pMat&&);
		pMat& operator=(pMat&&);

		static pMat init(uint_t size);
		static pMat random(uint_t size);

		uint_t        size  () const;
		uint_t*       values()      ;
		const uint_t* values() const;
		bool          owner () const;

		bool empty() const;
		void clear();
		pMat copy() const;
		pMat move();

		void info(const std::string& msg = "") const;
		void print() const;

		uint_t& operator()(uint_t i);
		const uint_t& operator()(uint_t i) const;

	private:
		uint_t  m_size  ;
		uint_t *m_values;
		bool    m_owner ;

		void setSize  (uint_t  size  );
		void setValues(uint_t *values);
		void setOwner (bool    owner );

		void defaults();
		void creator(uint_t size, uint_t *values, bool owner);
		void blankCreator(uint_t size);
		void randomCreator(uint_t size);
		void unbind();
};

/*-------------------------------------------------*/
} // namespace prm
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_PRM_MAT_HPP_
