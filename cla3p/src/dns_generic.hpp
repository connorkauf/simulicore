#ifndef CLA3P_DNS_GENERIC_HPP_
#define CLA3P_DNS_GENERIC_HPP_

#include <iostream>

#include "types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/

template <class T>
class GenericObject {

	public:

	//protected:
	
		GenericObject();
		~GenericObject();

		GenericObject(const GenericObject&) = delete;
		GenericObject& operator=(const GenericObject&) = delete;

		GenericObject(GenericObject&&);
		GenericObject& operator=(GenericObject&&);

		void set_nrows (uint_t   nrows );
		void set_ncols (uint_t   ncols );
		void set_ld    (uint_t   ld    );
		void set_values(T       *values);
		void set_prop  (Property prop  );
		void set_owner (bool     owner );

		uint_t    nrows () const;
		uint_t    ncols () const;
		uint_t    ld    () const;
		T       * values()      ;
		const T * values() const;
		Property  prop  () const;
		bool      owner () const;

		void clear();
		void info() const; 
		void data(uint_t nsd = 3) const;

	private:
		uint_t    m_nrows ;
		uint_t    m_ncols ;
		uint_t    m_ld    ;
		T       * m_values;
		Property  m_prop  ;
		bool      m_owner ;

		void defaults();
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_GENERIC_HPP_
